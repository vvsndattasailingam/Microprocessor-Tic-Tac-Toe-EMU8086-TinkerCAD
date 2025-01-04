// Arduino code for Tic Tac Toe in TinkerCAD

// Define pins for LEDs (representing the grid)
const int gridPins[3][3] = {
  {2, 3, 4},  // Row 1
  {5, 6, 7},  // Row 2
  {8, 9, 10}  // Row 3
};

// Define pins for push buttons
const int buttonPins[3][3] = {
  {11, 12, 13},  // Row 1
  {A0, A1, A2},  // Row 2
  {A3, A4, A5}   // Row 3
};

// Variables to track game state
char board[3][3] = {
  {' ', ' ', ' '},
  {' ', ' ', ' '},
  {' ', ' ', ' '}
};

int currentPlayer = 1;  // Player 1 starts

void setup() {
  // Initialize LED and button pins
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      pinMode(gridPins[i][j], OUTPUT);
      pinMode(buttonPins[i][j], INPUT_PULLUP);
    }
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (digitalRead(buttonPins[i][j]) == LOW) {  // Button pressed
        if (board[i][j] == ' ') {  // If cell is empty
          board[i][j] = (currentPlayer == 1) ? 'X' : 'O';
          digitalWrite(gridPins[i][j], HIGH);  // Light up LED
          delay(200);  // Debounce delay

          // Check for win or draw
          if (checkWin()) {
            resetGame();
            return;
          }

          currentPlayer = 3 - currentPlayer;  // Switch player
        }
      }
    }
  }
}

bool checkWin() {
  // Check rows, columns, and diagonals for a win
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return true;  // Row
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return true;  // Column
  }
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return true;  // Diagonal 1
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return true;  // Diagonal 2

  return false;
}

void resetGame() {
  // Reset the board and LEDs
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = ' ';
      digitalWrite(gridPins[i][j], LOW);
    }
  }
  currentPlayer = 1;  // Reset to player 1
}
