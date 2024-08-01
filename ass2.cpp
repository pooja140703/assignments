
#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 9; // Update to 9x9 board

// Print the current state of the board
void printBoard(const vector<vector<char>> &board)
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if the castle is home and no soldiers remain
bool isHomeAndClear(const vector<vector<char>> &board, int cx, int cy)
{
    if (cx != 1 || cy != 0)
        return false; // Check if the castle is at position (0,1) in 0-indexed format
    // for (int i = 0; i < BOARD_SIZE; ++i) {
    //     for (int j = 0; j < BOARD_SIZE; ++j) {
    //         if (board[i][j] == 'S') return false; // Soldiers remain
    //     }
    // }
    return true;
}

// Recursive function to find all paths
int findPaths(vector<vector<char>> &board, int cx, int cy, int pathCount, int direction)
{
    if (isHomeAndClear(board, cx, cy))
    {
        pathCount++;
        return pathCount;
    }

    // Move forward
    if (direction == 0)
    {
        for (int i = cx + 1; i < BOARD_SIZE; ++i)
        {
            if (board[i][cy] == 'S' || board[i][cy] == 'C')
            {
                board[i][cy] = '.';                                // Remove the soldier
                pathCount = findPaths(board, i, cy, pathCount, 1); // Move left next
                board[i][cy] = 'S';                                // Restore the soldier
            }
        }
    }

    // Move left
    if (direction == 1)
    {
        for (int j = cy + 1; j < BOARD_SIZE; ++j)
        {
            if (board[cx][j] == 'S' || board[cx][j] == 'C')
            {
                board[cx][j] = '.';                                // Remove the soldier
                pathCount = findPaths(board, cx, j, pathCount, 3); // Move backward next
                board[cx][j] = 'S';                                // Restore the soldier
            }
        }
    }

    // Move right
    if (direction == 2)
    {
        for (int j = cy - 1; j >= 0; --j)
        {
            if (board[cx][j] == 'S' || board[cx][j] == 'C')
            {
                board[cx][j] = '.';                                // Remove the soldier
                pathCount = findPaths(board, cx, j, pathCount, 0); // Move forward next
                board[cx][j] = 'S';                                // Restore the soldier
            }
        }
    }

    // Move backward
    if (direction == 3)
    {
        for (int i = cx - 1; i >= 0; --i)
        {
            if (board[i][cy] == 'S' || board[i][cy] == 'C')
            {
                board[i][cy] = '.';                                // Remove the soldier
                pathCount = findPaths(board, i, cy, pathCount, 2); // Move right next
                board[i][cy] = 'S';                                // Restore the soldier
            }
        }
    }
    return pathCount;
}

int main()
{
    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));

    // Take soldier positions as input
    int numSoldiers;
    cout << "Enter the number of soldiers: ";
    cin >> numSoldiers;

    cout << "Enter coordinates for soldiers:" << endl;
    for (int i = 0; i < numSoldiers; ++i)
    {
        int x, y;
        cout << "Enter coordinates for soldier " << i + 1 << ": ";
        cin >> y >> x;
        // Adjust for 0-indexed array
        if (x < 1 || x > BOARD_SIZE || y < 1 || y > BOARD_SIZE)
        {
            cout << "Invalid coordinates. Please enter values between 1 and " << BOARD_SIZE << "." << endl;
            i--;
            continue;
        }
        board[x - 1][y - 1] = 'S';
    }

    // Take castle position as input
    int cx, cy;
    cout << "Enter the coordinates for your special castle: ";
    cin >> cy >> cx;
    // Adjust for 0-indexed array
    if (cx < 1 || cx > BOARD_SIZE || cy < 1 || cy > BOARD_SIZE)
    {
        cout << "Invalid coordinates. Please enter values between 1 and " << BOARD_SIZE << "." << endl;
        return 1;
    }
    cx -= 1;
    cy -= 1;
    board[cx][cy] = 'C';

    cout << "Initial Board:" << endl;
    printBoard(board);

    int pathCount = 0;
    pathCount = findPaths(board, cx + 1, cy, pathCount, 0); // Start by moving forward

    cout << "Number of unique paths: " << pathCount << endl;
    printBoard(board);

    return 0;
}
