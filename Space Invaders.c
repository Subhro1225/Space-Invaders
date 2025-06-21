// header files used in the program
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define height 25
#define width 60
#define MAX_BULLETS 5

// global variables used in the games
char board[height][width];
int aliens[3][14];
int gameover = 0;
int player_x = width / 2, player_y = height - 2;
int score = 0;
int alien_direction = 1;
int alien_offset_x = 0;
int alien_offset_y = 0;
int frame_count = 0;

// bullet data (coordinates in x and y, and the bullet count)
int bullet_x[MAX_BULLETS]; 
int bullet_y[MAX_BULLETS];
int bullet_count = 0;

// global variables to run loops in the program
int i, j;

// function declarations or prototypes
void initAliens();
void initBoard();
void printBoard();
void input();
void moveBullets();
void moveAliens();
void checkCollision();
int checkWin();
void gotoxy(int x, int y);
void userinterface();
void usertext();
void rules();
void quitScreen();

// main function which contains the game loop
int main() {
    userinterface();
    usertext();
    rules();
    initAliens();

    while (!gameover) {
        initBoard();
        input();
        moveBullets();
        if (frame_count++ % 5 == 0) {
            moveAliens();
        }
        checkCollision();
        if (checkWin()) {
            gameover = 2;
        }
        printBoard();
        Sleep(50);
    }

    quitScreen();
    return 0;
}

// function defination

void userinterface() {
    system("cls");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || j == 0 || j == width - 1 || i == height - 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void usertext() {
    gotoxy(22, 9); printf("Welcome to");
    gotoxy(20, 11); printf("SPACE INVADERS");
    gotoxy(17, 13); printf("Enter any key to play the game");
    gotoxy(19, 15); printf("Press Q to Quit the game");
    char ch = getch();
    if (ch == 'q' || ch == 'Q') gameover = 1;
    system("cls");
}

void rules() {
    gotoxy(10, 5);  printf("RULES OF THE GAME:");
    gotoxy(10, 7);  printf("1. Use A and D to move the spaceship.");
    gotoxy(10, 9);  printf("2. Press SPACE to shoot bullets.");
    gotoxy(10, 11); printf("3. Destroy all aliens to win.");
    gotoxy(10, 13); printf("4. Avoid aliens reaching your spaceship.");
    gotoxy(10, 15); printf("Press any key to start the game.");
    getch();
    system("cls");
}

void initAliens() {
    // Clear all aliens
    for (i = 0; i < 3; i++)
        for (j = 0; j < 14; j++)
            aliens[i][j] = 0;

    srand(time(0)); // seed random

    int totalAliens = 10 + rand() % 6;
    int placed = 0;

    while (placed < totalAliens) {
        int row = rand() % 3;
        int col = rand() % 14;
        if (aliens[row][col] == 0) {
            aliens[row][col] = 1;
            placed++;
        }
    }

    // Reset bullets
    for (i = 0; i < MAX_BULLETS; i++) {
        bullet_y[i] = -1;
    }

    bullet_count = 0;
}

void initBoard() {
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            board[i][j] = (i == 0 || j == 0 || i == height - 1 || j == width - 1) ? '*' : ' ';

    // Draw player
    board[player_y][player_x] = '^';

    // Draw aliens
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 14; j++) {
            if (aliens[i][j] == 1) {
                int x = 2 + j * 4 + alien_offset_x;
                int y = 3 + i + alien_offset_y;
                if (x > 0 && x < width - 1 && y > 0 && y < height - 1)
                    board[y][x] = '0';
            }
        }
    }

    // Draw bullets
    for (i = 0; i < MAX_BULLETS; i++) {
        if (bullet_y[i] >= 1)
            board[bullet_y[i]][bullet_x[i]] = '|';
    }
}

void printBoard() {
    gotoxy(0, 0);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++)
            printf("%c", board[i][j]);
        printf("\n");
    }
    gotoxy(width - 15, 1); printf("SCORE: %d", score);
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 'a' && player_x > 1) player_x--;
        if (ch == 'd' && player_x < width - 2) player_x++;
        if (ch == ' ' && bullet_count < MAX_BULLETS) {
            for (i = 0; i < MAX_BULLETS; i++) {
                if (bullet_y[i] == -1) {
                    bullet_x[i] = player_x;
                    bullet_y[i] = player_y - 1;
                    bullet_count++;
                    break;
                }
            }
        }
        if (ch == 'q' || ch == 'Q') gameover = 1;
    }
}

void moveBullets() {
    for (i = 0; i < MAX_BULLETS; i++) {
        if (bullet_y[i] >= 1) {
            bullet_y[i]--;
        } else if (bullet_y[i] != -1) {
            bullet_y[i] = -1;
            bullet_count--;
        }
    }
}

void checkCollision() {
    for (i = 0; i < MAX_BULLETS; i++) {
        if (bullet_y[i] >= 0) {
            for (int ai = 0; ai < 3; ai++) {
                for (int aj = 0; aj < 14; aj++) {
                    if (aliens[ai][aj] == 1) {
                        int ax = 2 + aj * 4 + alien_offset_x;
                        int ay = 3 + ai + alien_offset_y;
                        if (bullet_x[i] == ax && bullet_y[i] == ay) {
                            aliens[ai][aj] = 0;
                            bullet_y[i] = -1;
                            bullet_count--;
                            score += 10;
                            return;
                        }
                    }
                }
            }
        }
    }
}

void moveAliens() {
    // Find leftmost and rightmost alien
    int leftMost = width, rightMost = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 14; j++) {
            if (aliens[i][j] == 1) {
                int x = 2 + j * 4 + alien_offset_x;
                if (x < leftMost) leftMost = x;
                if (x > rightMost) rightMost = x;
            }
        }
    }

    // reverses the direction of the aliens if the aliens touches the boundary
    if ((alien_direction == 1 && rightMost + 1 >= width - 1) ||
        (alien_direction == -1 && leftMost - 1 <= 0)) {
        alien_direction *= -1;
        alien_offset_y++;
        if (3 + 2 + alien_offset_y >= player_y) {
            gameover = 1; // the game ends when the aliens reach the player
        }
    } else {
        alien_offset_x += alien_direction;
    }
}

int checkWin() {
    for (i = 0; i < 3; i++)
        for (j = 0; j < 14; j++)
            if (aliens[i][j] == 1) return 0;
    return 1;
}

void quitScreen() {
    system("cls");
    gotoxy(width / 2 - 6, height / 2);
    if (gameover == 1)
        printf("GAME OVER");
    else
        printf("YOU WIN!");
    gotoxy(width / 2 - 10, height / 2 + 2);
    printf("Press any key to exit...");
    getch();
}

void gotoxy(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
