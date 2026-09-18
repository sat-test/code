import java.util.*;
// "static void main" must be defined in a public class.
class Coordinate {
    private int X;
    private int Y;
    
    Coordinate(int X, int Y) {
        this.X = X;
        this.Y = Y;
    }
    
    int getX() {
        return X;
    }
    
    int getY() {
        return Y;
    }
}

class Solution {
    int minimumFuelCost(Coordinate[] coordinate) {
        int n = coordinate.length;
        int[] y = new int[n];
        
        for(int i=0; i<n; i++) {
            y[i] = coordinate[i].getY();
        }
        
        Arrays.sort(y);
        
        int medianY = y[n/2];
        
        int cost = 0;
        
        for(int i=0; i<n; i++) {
            cost += Math.abs(y[i] - medianY);
        }
        
        Arrays.sort(coordinate, (a, b) -> a.getX() - b.getX());
        
        int[] x = new int[n];
        
        for(int i=0; i<n; i++) {
            x[i] = coordinate[i].getX() - i;
        }
        
        int medianX = x[n/2];
        
        for(int i=0; i<n; i++) {
            cost += Math.abs(x[i] - medianX);
        }
        
        return cost;
    }
}

public class Main {
    
    public static void main(String[] args) {
        Coordinate[] coordinates = {
            new Coordinate(2, 6),
            new Coordinate(4, 6),
            new Coordinate(1, 1),
            new Coordinate(3, 2),
            new Coordinate(6, 4)
        };
        
        Solution s = new Solution();
        
        System.out.println(s.minimumFuelCost(coordinates));
    }
}
