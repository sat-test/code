/*
Description
Your task is to design the basic function of  Excel and implement the function of sum formula. Specifically, you need to implement the following functions:

Excel(int H, char W): This is the constructor. The inputs represents the height and width of the Excel form. H is a positive integer, range from 1 to 26. It represents the height. W is a character range from ‘A’ to ‘Z’. It represents that the width is the number of characters from ‘A’ to W. The Excel form content is represented by a height * width 2D integer array C, it should be initialized to zero. You should assume that the first row of C starts from 1, and the first column of C starts from ‘A’.

void Set(int row, char column, int val): Change the value at C(row, column) to be val.

int Get(int row, char column): Return the value at C(row, column).

int Sum(int row, char column, List of Strings : numbers): This function calculate and set the value at C(row, column), where the value should be the sum of cells represented by numbers. This function return the sum result at C(row, column). This sum formula should exist until this cell is overlapped by another value or another sum formula.

numbers is a list of strings that each string represent a cell or a range of cells. If the string represent a single cell, then it has the following format: ColRow. For example, “F7” represents the cell at (7, F).

If the string represent a range of cells, then it has the following format: ColRow1:ColRow2. The range will always be a rectangle, and ColRow1 represent the position of the top-left cell, and ColRow2 represents the position of the bottom-right cell.

https://leetcode.ca/2017-08-22-631-Design-Excel-Sum-Formula/
https://leetcode.com/problems/design-excel-sum-formula/description/
*/


#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <cctype>

using namespace std;

class Excel {
private:
    int rows, columns;
    vector<vector<int>> cells;
    unordered_map<string, unordered_map<string, int>> cellSumMap; // cell -> sumCells
    unordered_map<string, unordered_map<string, int>> sumCellMap; // sumCell -> cells

    string getCellName(char col, int row) {
        return string(1, col) + to_string(row);
    }

    void updateRelevantCells(const string& cellName, int difference) {
        queue<pair<string, int>> cellQueue;
        cellQueue.push({cellName, difference});
        
        while (!cellQueue.empty()) {
            auto [currentCell, curDifference] = cellQueue.front();
            cellQueue.pop();

            char col = currentCell[0];
            int row = stoi(currentCell.substr(1));
            cells[row][col - 'A'] += curDifference;

            if (cellSumMap.count(currentCell)) {
                for (auto& [dependentCell, count] : cellSumMap[currentCell]) {
                    cellQueue.push({dependentCell, curDifference * count});
                }
            }
        }
    }

public:
    Excel(int H, char W) {
        rows = H + 1;
        columns = W - 'A' + 1;
        cells.resize(rows, vector<int>(columns, 0));
    }

    void set(int r, char c, int v) {
        string cellName = getCellName(c, r);
        int prevValue = cells[r][c - 'A'];
        int difference = v - prevValue;

        // Clear previous sum relationships
        if (sumCellMap.count(cellName)) {
            for (const auto& [dependentCell, _] : sumCellMap[cellName]) {
                cellSumMap[dependentCell].erase(cellName);
            }
            sumCellMap.erase(cellName);
        }

        // Update value and propagate changes
        updateRelevantCells(cellName, difference);
    }

    int get(int r, char c) {
        return cells[r][c - 'A'];
    }

    int sum(int r, char c, const vector<string>& strs) {
        string sumCellName = getCellName(c, r);
        int prevValue = cells[r][c - 'A'];

        // Reset the cell and clear previous relationships
        set(r, c, prevValue);

        int sum = 0;
        for (const string& str : strs) {
            if (str.find(':') != string::npos) {
                // Handle range of cells
                size_t colonPos = str.find(':');
                string start = str.substr(0, colonPos);
                string end = str.substr(colonPos + 1);

                char startCol = start[0], endCol = end[0];
                int startRow = stoi(start.substr(1)), endRow = stoi(end.substr(1));

                for (int i = startRow; i <= endRow; i++) {
                    for (char j = startCol; j <= endCol; j++) {
                        string cellName = getCellName(j, i);
                        cellSumMap[cellName][sumCellName]++;
                        sumCellMap[sumCellName][cellName]++;
                        sum += cells[i][j - 'A'];
                    }
                }
            } else {
                // Handle single cell
                string cellName = str;
                char col = cellName[0];
                int row = stoi(cellName.substr(1));

                cellSumMap[cellName][sumCellName]++;
                sumCellMap[sumCellName][cellName]++;
                sum += cells[row][col - 'A'];
            }
        }

        int difference = sum - prevValue;
        updateRelevantCells(sumCellName, difference);

        return cells[r][c - 'A'];
    }
};


int main() {
    Excel excel(3, 'C'); // 3 rows, columns from A to C
    excel.set(1, 'A', 5);
    excel.set(2, 'B', 3);
    excel.sum(3, 'C', {"A1", "B2"});
    cout << excel.get(3, 'C') << endl; // Output: 8

    excel.set(1, 'A', 2);
    cout << excel.get(3, 'C') << endl; // Output: 5
    return 0;
}
