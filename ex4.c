/******************
Name:Maya Mattar
ID:213510407
Assignment:ex4
*******************/
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100 // Parenthesis Validator
#define MAX 20 // Maximum board size (Queens Battle)
#define MAX_GRID_SIZE 30 // Crossword Generator
#define MAX_SLOTS 100 // Crossword Generator
#define MAX_WORDS 100 // Crossword Generator
#define MAX_WORD_LENGTH 15 // Crossword Generator

// Slot structure to store store  details about each slot (Task 5)
 typedef struct {
   int row;
   int col;
   int length;
   char direction;  // 'H' for horizontal, 'V' for vertical
 }
Slot;

// Prototypes for all functions
void task1RobotPaths();
int calculatePaths(int column, int row);
void task2HumanPyramid();
float calculateWeight(int row, int column, float weights[]);
void task3ParenthesisValidator();
int validateParentheses(char input[], int index, int countRound, int countSquare, int countCurly, int countAngle);
void task4QueensBattle();
int isValidPosition(int row, int col, char area, char board[MAX][MAX], int rows[MAX], int cols[MAX], int areas[MAX], int boardSize);
int solveQueens(int row, int col, int queens, char board[MAX][MAX], int rows[MAX], int cols[MAX], int areas[MAX], int boardSize);
int absoluteValue(int value);
void task5CrosswordGenerator();
int canPlaceWord(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, char word[], int gridSize);
void placeWord(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, char word[], int place);
int solveCrossword(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slots[], char words[MAX_WORDS][MAX_WORD_LENGTH], int slotIndex, int totalSlots, int totalWords, int gridSize);
void printGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int gridSize);

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
                case 6:
                    printf("Goodbye!\n");
                break;
                case 1:
                    task1RobotPaths();
                break;
                case 2:
                    task2HumanPyramid();
                break;
                case 3:
                    task3ParenthesisValidator();
                break;
                case 4:
                    task4QueensBattle();
                break;
                case 5:
                    task5CrosswordGenerator();
                break;
                default:
                    printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

// Function for Task 1: Robot Paths
void task1RobotPaths() {
 int column, row;

 // Prompt user for input
 printf("Please enter the coordinates of the robot (column, row): \n");
 scanf("%d %d", &column, &row);

 // Validate input
 if (column < 0 || row < 0) {
   printf("The total number of paths the robot can take to reach home is: 0\n");
   return;
   }

   // Calculate and print the number of paths
   int totalPaths = calculatePaths(column, row);
   printf("The total number of paths the robot can take to reach home is: %d\n", totalPaths);
}
// Function to calculate the total number of unique paths using recursion
int calculatePaths(int column, int row) {
    // Base case: if either column or row is 0, there's only one path
    if (column == 0 || row == 0) {
        return 1;
    }
    return calculatePaths(column - 1, row) + calculatePaths(column, row - 1);
}

// Function for Task 2: The Human Pyramid
void task2HumanPyramid() {
  int levels = 5;
  float weights[15]; // Array to store weight of all cheerleaders (for 5 levels)
  printf("Please enter the weights of the cheerleaders:\n");

  // Input weights for all cheerleaders
  for (int i = 0; i < 15; i++) {
    scanf("%f", &weights[i]);

    // Validate input for negative weights
    if (weights[i] < 0) {
      printf("Negative weights are not supported.\n");
      return;
      }
    }
   printf("\nThe total weight on each cheerleader is:\n");
   // Display weights is a pyramid format
   for (int row = 0, index = 0; row < levels; row++) {
     for (int column = 0; column <= row; column++, index++) {
       float totalWeight = calculateWeight(row, column, weights);
       printf("%.2f ", totalWeight);
       }
       printf("\n");
       }
    }
// Recursive function to calculate the weight supported by a cheerleader
float calculateWeight(int row, int column, float weights[]) {
    // Calculate the index of cheerleader in the array
    int index = (row * (row + 1)) / 2 + column;

    // Base case: if at the top of the pyramid, return their own weight
    if (row == 0) {
        return weights[index];
    }

    // Recursive case: calculate the weight supported from above
    float leftWeight = (column > 0) ? calculateWeight(row - 1, column - 1, weights) / 2 : 0;
    float rightWeight = (column < row) ? calculateWeight(row - 1, column, weights) / 2 : 0;
    return weights[index] + leftWeight + rightWeight;
}

// Function for Task 3: Parenthesis Validation

void task3ParenthesisValidator() {
    char input[MAX_INPUT_SIZE];
    printf("Please enter a term for validation:\n");

    // Reading input string using allowed scanf approach
    scanf("%99s", input);

    // Validate parentheses using the recursive function
    if (validateParentheses(input, 0, 0, 0, 0, 0)) {
        printf("The parentheses are balanced correctly.\n");
    } else {
        printf("The parentheses are not balanced correctly.\n");
    }
}

// Recursive function to validate parentheses
int validateParentheses(char input[], int index, int countRound, int countSquare, int countCurly, int countAngle) {
    // Base case: end of the string (null character)
    if (input[index] == '\0') {
        return countRound == 0 && countSquare == 0 && countCurly == 0 && countAngle == 0;
    }

    // Update counts based on the character
    switch (input[index]) {
        case '(':
            countRound++;
        break;
        case ')':
            countRound--;
        break;
        case '[':
            countSquare++;
        break;
        case ']':
            countSquare--;
        break;
        case '{':
            countCurly++;
        break;
        case '}':
            countCurly--;
        break;
        case '<':
            countAngle++;
        break;
        case '>':
            countAngle--;
        break;
        default:
            break; // Ignore non-parenthesis characters
    }

    // Check for imbalance (negative counts)
    if (countRound < 0 || countSquare < 0 || countCurly < 0 || countAngle < 0) {
        return 0; // Not balanced
    }

    // Recursive call to process the next character
    return validateParentheses(input, index + 1, countRound, countSquare, countCurly, countAngle);
}
/**
 * Solves the Queens Battle problem by prompting the user for input
 * and displaying the solution or a failure message.
 */
void task4QueensBattle() {
    char board[MAX][MAX];
    int rows[MAX] = {0}, cols[MAX] = {0}, areas[MAX] = {0};
    int boardSize;

    // Input board dimensions
    printf("Please enter the board dimensions: \n");
    scanf("%d", &boardSize);

    printf("Please enter a %d*%d puzzle board:\n", boardSize, boardSize);
    for (int i = 0; i < boardSize; i++) {
        scanf("%s", board[i]);
    }

    // Solve the puzzle
    if (solveQueens(0, 0, 0, board, rows, cols, areas, boardSize)) {
        printf("Solution:\n");
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("This puzzle cannot be solved.\n");
    }
}


// Checks if placing a queen at the given position is valid.
int isValidPosition(int row, int col, char area, char board[MAX][MAX], int rows[MAX], int cols[MAX], int areas[MAX], int boardSize) {
    // Check row, column, and area constraints
    if (rows[row] || cols[col] || areas[area - 'A']) {
        return 0;
    }
    // Check diagonal conflicts by iterating over the board
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == 'X') {
                // Check both left and right diagonals
                if ((i - row) == (j - col) || (i - row) == -(j - col)) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
// Solves the Queens Battle problem using backtracking.
int solveQueens(int row, int col, int queens, char board[MAX][MAX], int rows[MAX], int cols[MAX], int areas[MAX], int boardSize) {
    if (queens == boardSize) {
        return 1; // All queens placed successfully
    }
    if (col == boardSize) { // Move to the next row
        row++;
        col = 0;
    }
    if (row == boardSize) {
        return 0; // No solution
    }
    // Try placing a queen
    if (board[row][col] != '*' && isValidPosition(row, col, board[row][col], board, rows, cols, areas, boardSize)) {
        // Place the queen
        board[row][col] = 'X';
        rows[row] = 1;
        cols[col] = 1;
        areas[board[row][col] - 'A'] = 1;
        // Recur to place the next queen
        if (solveQueens(row, col + 1, queens + 1, board, rows, cols, areas, boardSize)) {
            return 1;
        }
        // Backtrack
        board[row][col] = '*';
        rows[row] = 0;
        cols[col] = 0;
        areas[board[row][col] - 'A'] = 0;
    }
    // Skip the current cell and try the next
    return solveQueens(row, col + 1, queens, board, rows, cols, areas,boardSize);
}
// Custom implementation of absolute value.
int absoluteValue(int value) {
    return value < 0 ? -value : value;
}

// Function for Task 5: Crossword Generator
void task5CrosswordGenerator() {
    int gridSize, totalSlots, totalWords;
    char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
    Slot slots[MAX_SLOTS];
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    // Input grid size
    printf("Please enter the dimensions of the crossword grid: \n");
    scanf("%d", &gridSize);
    // Intialize the grid with '#'
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = '#';
        }
    }
    // Input number of slots
    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d", &totalSlots);
    // Input slot details
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < totalSlots; i++) {
        scanf("%d %d %d %c", &slots[i].row, &slots[i].col, &slots[i].length, &slots[i].direction);
    }
    // Input number of words and validate
    printf("Please enter the number of words in the dictionary:\n");
    scanf("%d", &totalWords);
    // Validate the number of words against number of slots
    while (totalWords < totalSlots) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", totalSlots);
        scanf("%d", &totalWords);
    }
    // Input words
    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < totalWords; i++) {
        scanf("%s", words[i]);
    }
    // Solve the crossword puzzle
    if (solveCrossword(grid, slots, words, 0, totalSlots, totalWords, gridSize)) {
        printGrid(grid, gridSize);
    }
    else {
        printf("This crossword cannot be solved.\n");
    }
}
 // Recursive function to check if a word can be placed in a slot
  int canPlaceWord(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, char word[], int gridSize) {
    int r = slot.row, c = slot.col;
    for (int i = 0; i < slot.length; i++) {
      if ( r >= gridSize || c >= gridSize) {
        return 0;
      }
      if (grid[r][c] != '#' && grid[r][c] != word[i]) {
        return 0; // Conflict with existing letters
      }
      if (slot.direction == 'H') {
        c++; // Move right for horizontal slot
      } else if (slot.direction == 'V') {
        r++; // Move down for vertical slot
      }
    }
    return 1; // Word can be placed
  }
  // Recursive function to place a word in a slot
  void placeWord(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slot, char word[], int place) {
    int r = slot.row, c = slot.col;
    for (int i = 0; i < slot.length; i++) {
      if (place) {
        grid[r][c] = word[i]; // Place the letter
      }
      else {
        grid[r][c] = '#'; // Reset the cell if backtracking
      }
      if (slot.direction == 'H') {
        c++; // Move right for horizontal slot
      }
      else {
        r++;
      }
    }
  }
  // Recursive function to solve the crossword
  int solveCrossword(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], Slot slots[], char words[MAX_WORDS][MAX_WORD_LENGTH], int slotIndex, int totalSlots, int totalWords, int gridSize) {
    if (slotIndex == totalSlots) {
      return 1; // All slots filled successfully
    }
    Slot currentSlot = slots[slotIndex];
    for (int i = 0; i < totalWords; i++) {
      if (words[i][0] != '\0' && (int)strlen(words[i]) == currentSlot.length && canPlaceWord(grid, currentSlot, words[i], gridSize)) {
        char tempWord[MAX_WORD_LENGTH];
        strcpy(tempWord, words[i]);
        words[i][0] = '\0'; // Mark word as used
        placeWord(grid, currentSlot, tempWord, 1); // Place the word
        if (solveCrossword(grid, slots, words, slotIndex + 1, totalSlots, totalWords, gridSize)) {
          return 1; // Puzzle solved
        }
        // Backtrack, Restore word
        placeWord(grid, currentSlot, tempWord, 0);
        strcpy(words[i], tempWord);
      }
    }
    return 0;
  }
  // Function to print the crossword grid
  void printGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int gridSize) {
    for (int i = 0; i < gridSize; i++) {
      printf("|");
      for (int j = 0; j < gridSize; j++) {
        printf(" %c |", grid[i][j]);
      }
      printf("\n");
    }
  }
