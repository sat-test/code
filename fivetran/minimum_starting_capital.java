/*
Becky Corp needs to produce n products. Each product has:
- expected[i] — the expected cost to produce product i.
- worst[i] — the minimum budget required before starting product i in the worst case.

After producing a product, only its expected cost is deducted from the available budget.

You can produce the products in any order.

Given two arrays expected and worst, return the minimum initial budget required to produce all products.

It is guaranteed that:
worst[i] >= expected[i]

Example
worst    = [9, 7, 6]
expected = [1, 2, 5]

An optimal order is:

(9, 1)
(7, 2)
(6, 5)

Starting with 9:

Start = 9

Product 1:
9 >= 9
9 - 1 = 8

Product 2:
8 >= 7
8 - 2 = 6

Product 3:
6 >= 6
6 - 5 = 1

Therefore:

Answer = 9

*/

class Product {
    int worst;
    int expected;
    
    Product(int worst, int expected) {
        this.worst = worst;
        this.expected = expected;
    }
    
    int getWorst() {
        return worst;
    }
    
    int getExpected() {
        return expected;
    }
}

class Solution {
    int minimumBudget(int[] worst, int[] expected) {
        int n = worst.length;
        Product[] products = new Product[n];
        
        for(int i=0; i<n; i++) {
            products[i] = new Product(worst[i], expected[i]);
        }
        
        Arrays.sort(products, (a, b) -> Integer.compare(b.worst - b.expected, a.worst - a.expected));
        
        int spent = 0;
        int budget = 0;
        
        for(Product product : products) {
            budget = Math.max(budget, spent + product.getWorst());
            spent += product.getExpected();
        }
        
        return budget;
    }
}

public class Main {
    
    static void test(
        Solution solution,
        int[] worst,
        int[] expected,
        int expectedAnswer
    ) {
        int actual = solution.minimumBudget(worst, expected);

        System.out.println(
            "Expected: " + expectedAnswer +
            ", Actual: " + actual +
            " -> " + (actual == expectedAnswer ? "PASS" : "FAIL")
        );
    }

    public static void main(String[] args) {

        Solution solution = new Solution();

        // Example 1
        test(
            solution,
            new int[]{9, 7, 6},
            new int[]{1, 2, 5},
            9
        );

        // Example 2
        test(
            solution,
            new int[]{4, 5, 6, 3, 10, 6, 7},
            new int[]{1, 2, 4, 1, 2, 2, 2},
            16
        );

        // Single product
        test(
            solution,
            new int[]{10},
            new int[]{5},
            10
        );

        // All products have same worst/expected
        test(
            solution,
            new int[]{5, 5, 5},
            new int[]{5, 5, 5},
            15
        );

        // Order matters
        test(
            solution,
            new int[]{10, 5},
            new int[]{1, 5},
            10
        );
    }
}
