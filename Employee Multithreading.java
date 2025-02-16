/*
There is list of employees and every employee have 3-4 attributes like id, name, city. I have given city name. How many person living in the city. Please do it by using multithreading.
*/

class Employee {
    private int id;
    private String name;
    private String city;
    
    public Employee(int id, String name, String city) {
        this.id = id;
        this.name = name;
        this.city = city;
    }
    
    public String getCity() {
        return this.city;
    }
}

class CityCountTask implements Callable<Integer> {
    private List<Employee> employees;
    private String targetCity;
    int start, end;
    
    public CityCountTask(List<Employee> employees, String targetCity, int start, int end) {
        this.employees = employees;
        this.targetCity = targetCity;
        this.start = start;
        this.end = end;
    }
    
    @Override
    public Integer call() {
        int count = 0;
        for (int i = start; i < end; i++) {
            if (employees.get(i).getCity().equals(targetCity)) {
                count++;
            }
        }
        return count;
    }
}

public class CityPopulationCounter {
    
    private static final int NUM_THREADS = Runtime.getRuntime().availableProcessors();
    
    public static int countEmployeesInCity(List<Employee> employees, String targetCity) throws InterruptedException, ExecutionException {
         int n = employees.size();
         int chunkSize = (int) Math.ceil((double) n/NUM_THREADS);
         ExecutorService executor = Executors.newFixedThreadPool(NUM_THREADS);
         List<Future<Integer>> futures = new ArrayList<>();
         
         for (int i = 0; i < n; i += chunkSize) {
             int end = Math.min(i + chunkSize, n);
             futures.add(executor.submit(new CityCountTask(employees, targetCity, i, end)));
         }
         
         int total = 0;
         for (Future<Integer> future : futures) {
            total += future.get();
         }
         
         executor.shutdown();
         return total;
     }
    
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        List<Employee> employees = Arrays.asList(
            new Employee(1, "Alice", "New York"),
            new Employee(2, "Bob", "Los Angeles"),
            new Employee(3, "Charlie", "New York"),
            new Employee(4, "David", "New York"),
            new Employee(5, "Eve", "Los Angeles"),
            new Employee(6, "Frank", "New York")
        );
        
        String targetCity = "New York";
        int count = countEmployeesInCity(employees, targetCity);
        
        System.out.println("Number of employees in " + targetCity + ": " + count);

    }
}
