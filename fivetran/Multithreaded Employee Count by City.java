/*
Problem: Count Employees by City Using Multithreading

You are given a list of Employee objects. Each employee has multiple attributes such as:

id
name
city
department

Given a city name, find the number of employees living in that city using multithreading.

Example
Employees:

1. Satyam    Bangalore    Engineering
2. Rahul     Delhi        Engineering
3. Amit      Bangalore    Finance
4. Priya     Mumbai       HR
5. Neha      Bangalore    Engineering
6. Rohit     Delhi        Finance
7. Ankit     Bangalore    HR

Input:

city = "Bangalore"

Output:

4

Because 4 employees live in Bangalore.

Constraints
1 <= number of employees <= 10^7
Employee attributes are strings/integers.
City comparison should be case-sensitive unless specified otherwise.
The employee list can be very large.
The solution should use multiple threads to process the employees concurrently.
The result must be accurate and deterministic.
Avoid unnecessary synchronization between worker threads.
*/

import java.util.*;
import java.util.concurrent.*;

class Employee {
    int id;
    String name;
    String city;
    String department;

    public Employee(int id, String name, String city, String department) {
        this.id = id;
        this.name = name;
        this.city = city;
        this.department = department;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getCity() {
        return city;
    }

    public String getDepartment() {
        return department;
    }
}

class EmployeeService {
    ArrayList<Employee> employees;

    public EmployeeService() {
        this.employees = new ArrayList<>();
    }

    public void addEmployee(Employee employee) {
        employees.add(employee);
    }

    public void deleteEmployee(Employee employee) {
        employees.remove(employee);
    }

    public Integer findEmployeeCountByCity(String city) throws Exception {

        int n = employees.size();

        if (n == 0) {
            return 0;
        }

        int numberOfThreads = 2;

        ExecutorService executor =
            Executors.newFixedThreadPool(numberOfThreads);

        List<Future<Integer>> futures = new ArrayList<>();

        int chunkSize =
            (n + numberOfThreads - 1) / numberOfThreads;

        for (int start = 0; start < n; start += chunkSize) {

            int chunkStart = start;
            int chunkEnd = Math.min(start + chunkSize, n);

            Future<Integer> future = executor.submit(() -> {

                int localCount = 0;

                for (int i = chunkStart; i < chunkEnd; i++) {

                    Employee employee = employees.get(i);

                    if (Objects.equals(employee.getCity(), city)) {
                        ++localCount;
                    }
                }

                return localCount;
            });

            futures.add(future);
        }

        int count = 0;

        for (Future<Integer> future : futures) {
            count += future.get();
        }

        executor.shutdown();

        return count;
    }
}

public class Main {

    public static void main(String[] args) throws Exception {

        EmployeeService service = new EmployeeService();

        service.addEmployee(
            new Employee(1, "Satyam", "Bangalore", "Engineering")
        );

        service.addEmployee(
            new Employee(2, "Rahul", "Delhi", "Engineering")
        );

        service.addEmployee(
            new Employee(3, "Amit", "Bangalore", "Finance")
        );

        service.addEmployee(
            new Employee(4, "Priya", "Mumbai", "HR")
        );

        service.addEmployee(
            new Employee(5, "Neha", "Bangalore", "Engineering")
        );

        service.addEmployee(
            new Employee(6, "Rohit", "Delhi", "Finance")
        );

        int count =
            service.findEmployeeCountByCity("Bangalore");

        System.out.println(
            "Employees in Bangalore = " + count
        );
    }
}
