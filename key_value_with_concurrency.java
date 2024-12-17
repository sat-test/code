import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;

class VersionedValue {
    String value;
    long version;

    VersionedValue(String value, long version) {
        this.value = value;
        this.version = version;
    }
}

class Transaction {
    Map<String, VersionedValue> readSet = new HashMap<>();
    Map<String, String> writeSet = new HashMap<>();
    Set<String> deleteSet = new HashSet<>();
}

class KeyValueStore {
    private final Map<String, VersionedValue> data = new ConcurrentHashMap<>();
    private final ThreadLocal<Transaction> currentTransaction = new ThreadLocal<>();
    private final AtomicLong globalVersion = new AtomicLong(0);
    private final Lock commitLock = new ReentrantLock();

    public String get(String key) {
        Transaction transaction = currentTransaction.get();
        if (transaction != null) {
            if (transaction.deleteSet.contains(key)) return null;
            if (transaction.writeSet.containsKey(key)) return transaction.writeSet.get(key);
        }

        VersionedValue versionedValue = data.get(key);
        if (versionedValue == null) return null;

        if (transaction != null) {
            transaction.readSet.putIfAbsent(key, versionedValue);
        }

        return versionedValue.value;
    }

    public void set(String key, String value) {
        Transaction transaction = currentTransaction.get();
        if (transaction != null) {
            transaction.writeSet.put(key, value);
            transaction.deleteSet.remove(key);
        } else {
            data.put(key, new VersionedValue(value, globalVersion.incrementAndGet()));
        }
    }

    public void delete(String key) {
        Transaction transaction = currentTransaction.get();
        if (transaction != null) {
            transaction.deleteSet.add(key);
            transaction.writeSet.remove(key);
        } else {
            data.remove(key);
        }
    }

    public void begin() {
        if (currentTransaction.get() != null) {
            throw new IllegalStateException("Transaction already in progress");
        }
        currentTransaction.set(new Transaction());
    }

    public boolean commit() {
        Transaction transaction = currentTransaction.get();
        if (transaction == null) {
            throw new IllegalStateException("No active transaction");
        }

        commitLock.lock(); // Lock to ensure atomic commit
        try {
            // Validate reads
            for (Map.Entry<String, VersionedValue> entry : transaction.readSet.entrySet()) {
                VersionedValue currentVersionedValue = data.get(entry.getKey());
                if (currentVersionedValue == null || currentVersionedValue.version != entry.getValue().version) {
                    currentTransaction.remove();
                    return false; // Transaction conflict
                }
            }

            // Validate writes (write set conflict detection)
            for (String key : transaction.writeSet.keySet()) {
                VersionedValue currentVersionedValue = data.get(key);
                if (currentVersionedValue != null && !transaction.readSet.containsKey(key)) {
                    // Conflict: Another thread modified the key
                    currentTransaction.remove();
                    return false;
                }
            }
            
            // Apply writes and deletes
            for (String key : transaction.deleteSet) {
                data.remove(key);
            }
            for (Map.Entry<String, String> entry : transaction.writeSet.entrySet()) {
                data.put(entry.getKey(), new VersionedValue(entry.getValue(), globalVersion.incrementAndGet()));
            }

            currentTransaction.remove();
            return true;
        } finally {
            commitLock.unlock();
        }
    }


    public void rollback() {
        Transaction transaction = currentTransaction.get();
        if (transaction == null) {
            throw new IllegalStateException("No active transaction");
        }
        currentTransaction.remove();
    }
}

public class Main {
    public static void main(String[] args) {
        KeyValueStore kvStore = new KeyValueStore();

        // Simple operations
        kvStore.set("key1", "value1");
        System.out.println(kvStore.get("key1")); // Output: value1

        kvStore.delete("key1");
        System.out.println(kvStore.get("key1")); // Output: null

        // Transactions
        kvStore.begin();
        kvStore.set("key2", "value2");
        kvStore.set("key3", "value3");
        System.out.println(kvStore.get("key2")); // Output: value2
        kvStore.rollback();
        System.out.println(kvStore.get("key2")); // Output: null

        kvStore.begin();
        kvStore.set("key4", "value4");
        kvStore.commit();
        System.out.println(kvStore.get("key4")); // Output: value4
        
        kvStore.set("key5", "value1");
        
        // Thread 1: Perform transaction
        Thread t1 = new Thread(() -> {
            kvStore.begin();
            kvStore.set("key5", "value5");
            kvStore.commit();
            System.out.println("Thread 1 committed");
        });

        // Thread 2: Perform concurrent transaction
        Thread t2 = new Thread(() -> {
            kvStore.begin();
            kvStore.set("key6", "value6");
            if (kvStore.commit()) {
                System.out.println("Thread 2 committed");
            } else {
                System.out.println("Thread 2 rollback due to conflict");
            }
        });

        // Thread 3: Perform concurrent transaction
        Thread t3 = new Thread(() -> {
            kvStore.begin();
            kvStore.set("key5", "value6");
            if (kvStore.commit()) {
                System.out.println("Thread 3 committed");
            } else {
                System.out.println("Thread 3 rollback due to conflict");
            }
        });

        t1.start();
        t2.start();

        try {
            Thread.sleep(1500); // Delay execution of t3 by 1 second
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        t3.start();
        
    }
}
