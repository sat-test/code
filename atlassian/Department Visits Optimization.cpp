/*
## Department Visits Optimization

You are given a list of products, where each product belongs to a specific department.

For example:

```text
products = [
    ["Cheese", "Dairy"],
    ["Carrots", "Produce"],
    ["Potatoes", "Produce"],
    ["Milk", "Dairy"],
    ["Coffee", "Pantry"],
    ["Flour", "Pantry"],
    ["Blueberries", "Produce"]
]
```

You are also given an **ordered shopping list** representing the order in which a customer plans to pick up the products:

```text
shoppingList = [
    "Blueberries",
    "Milk",
    "Coffee",
    "Flour",
    "Cheese",
    "Carrots"
]
```

Each product belongs to exactly one department.

### Definition of a Department Visit

A **department visit** occurs whenever the customer moves from one department to another while following the shopping-list order.

For example, the above shopping list corresponds to:

```text
Blueberries → Produce
Milk        → Dairy
Coffee      → Pantry
Flour       → Pantry
Cheese      → Dairy
Carrots     → Produce
```

Therefore, the department sequence is:

```text
Produce → Dairy → Pantry → Pantry → Dairy → Produce
```

This requires **5 department visits** because the customer changes departments 5 times.

Now assume the customer is allowed to **reorder the shopping list by department**, so that products belonging to the same department are picked up together.

For example:

```text
Produce → Dairy → Pantry
```

This requires only **2 department changes**.

### Task

Return the **number of department visits saved** by grouping the shopping list by department compared with following the original order.

### Example

```text
Input:

products = [
    ["Cheese", "Dairy"],
    ["Carrots", "Produce"],
    ["Potatoes", "Produce"],
    ["Milk", "Dairy"],
    ["Coffee", "Pantry"],
    ["Flour", "Pantry"],
    ["Blueberries", "Produce"]
]

shoppingList = [
    "Blueberries",
    "Milk",
    "Coffee",
    "Flour",
    "Cheese",
    "Carrots"
]
```

Original department sequence:

```text
Produce → Dairy → Pantry → Pantry → Dairy → Produce
```

Original department transitions:

```text
Produce → Dairy      = 1
Dairy → Pantry       = 1
Pantry → Pantry      = 0
Pantry → Dairy       = 1
Dairy → Produce      = 1
```

Total:

```text
4 department changes
```

If the products are grouped by department:

```text
Produce → Dairy → Pantry
```

there are:

```text
2 department changes
```

Therefore:

```text
Department visits saved = 4 - 2 = 2
```

### Expected Output

```text
2
```

### Constraints

Assume:

- Each product belongs to exactly one department.
- Every product in `shoppingList` exists in `products`.
- A department may contain multiple products.
- The order of products within a department does not matter.

### Follow-up

How would you modify the solution if the customer **cannot arbitrarily reorder products**, but can only swap adjacent products?

*/

class Solution {
public:
    int departmentVisit(
        vector<vector<string>>& products,
        vector<string>& shoppingList
    ) {
        unordered_map<string, string> productToDepartment;

        for (auto& product : products) {
            productToDepartment[product[0]] = product[1];
        }

        int originalVisits = 0;

        for (int i = 1; i < shoppingList.size(); i++) {
            string prevDepartment =
                productToDepartment[shoppingList[i - 1]];

            string currDepartment =
                productToDepartment[shoppingList[i]];

            if (prevDepartment != currDepartment) {
                originalVisits++;
            }
        }

        unordered_set<string> departments;

        for (auto& product : shoppingList) {
            departments.insert(productToDepartment[product]);
        }

        int groupedVisits = max(0, (int)departments.size() - 1);

        return originalVisits - groupedVisits;
    }
};

int main() {
    Solution s;
    vector<vector<string>> products = {
        {"Cheese", "Dairy"},
        {"Carrots", "Produce"},
        {"Potatoes", "Produce"},
        {"Milk", "Dairy"},
        {"Coffee", "Pantry"},
        {"Flour", "Pantry"},
        {"Blueberries", "Produce"}
    };
    vector<string> shoppingList = {
        "Blueberries",
        "Milk",
        "Coffee",
        "Flour",
        "Cheese",
        "Carrots"
    };
    
    cout<<s.departmentVisit(products, shoppingList);
}
