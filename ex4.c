
        printf("The parentheses are not balanced correctly.\n");
    }
}

/**
 * Validates parentheses using a stack-based approach.
 * Ensures proper nesting and matching of parentheses.
 * Returns 1 if balanced, 0 otherwise.
 */
int validateParentheses(char input[]) {
    char stack[STACK_SIZE];
    int top = -1;

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];

        // Push opening brackets to the stack
        if (ch == '(' || ch == '[' || ch == '{' || ch == '<') {
            if (top < STACK_SIZE - 1) {
                stack[++top] = ch;
            } else {
                return 0;  // Stack overflow
            }
        }
        // Check for matching closing brackets
        else if (ch == ')' || ch == ']' || ch == '}' || ch == '>') {
            if (top == -1) {
                return 0;  // Unmatched closing bracket
            }
            char open = stack[top--];
            if ((ch == ')' && open != '(') ||
                (ch == ']' && open != '[') ||
                (ch == '}' && open != '{') ||
                (ch == '>' && open != '<')) {
                return 0;  // Mismatched pair
                }
        }
        // Ignore other characters
    }

    // If the stack is empty, all parentheses are balanced
    return top == -1;
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
