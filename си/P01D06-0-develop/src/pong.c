#include <stdio.h>

int x_line = 82;  // размер поля ширина
int y_line = 27;  // размер поля высота
int rocket1_y = 13;  // стартовая позиция ракетки по y
int rocket2_y = 13;  // 2 стартовая позиция по y
int rocket1_x = 2;  // стартовая позиция ракетки по x
int rocket2_x = 79;  // 2 стартовая позиция по x
int ball_x = 41;  // стартовая позиция мяча по x
int ball_y = 13;  // стартовая позиция мяча по y

int win_balls = 21;  // неообходимое количесвтво для для победы
int TRUE = 1;
int FALSE = 0;

void move_rocket(int *rocket_1_Y, int *rocket_2_Y);
void moveBall(int *ball1_x, int *ball1_y,
                int *vector_X, int *vector_Y,
                const int *rocket_1_Y, const int *rocket_2_Y);  // обьявления функциии
void Rendering_screen(const int *rocket_1_Y, const int *rocket_2_Y,
                        const int *ball1_x, const int *ball1_y,
                        int *scPlayer1, int *scPlayer2);
int checkTablo(int *scPlayer1, int *scPlayer2, int *ball1_x, int *ball1_y);
void Screenclear(void);



void move_rocket(int *rocket_1_Y, int *rocket_2_Y) {
    char temp;
    switch (temp = getchar()) {
        case 'a' : ((*rocket_1_Y - 2) != 0) ? (*rocket_1_Y -= 1) : *rocket_1_Y; break;
        case 'z' : ((*rocket_1_Y + 2) != y_line - 1) ? (*rocket_1_Y += 1) : *rocket_1_Y; break;
        case 'k' : ((*rocket_2_Y - 2) != 0) ? (*rocket_2_Y -= 1) : *rocket_2_Y; break;
        case 'm' : ((*rocket_2_Y + 2) != y_line - 1) ? (*rocket_2_Y += 1) : *rocket_2_Y; break;
        case 'A' : ((*rocket_1_Y - 2) != 0) ? (*rocket_1_Y -= 1) : *rocket_1_Y; break;
        case 'Z' : ((*rocket_1_Y + 2) != y_line - 1) ? (*rocket_1_Y += 1) : *rocket_1_Y; break;
        case 'K' : ((*rocket_2_Y - 2) != 0) ? (*rocket_2_Y -= 1) : *rocket_2_Y; break;
        case 'M' : ((*rocket_2_Y + 2) != y_line - 1) ? (*rocket_2_Y += 1) : *rocket_2_Y; break;
    }
}
  // функция рендеринга экрана
void Rendering_screen(const int *rocket_1_Y, const int *rocket_2_Y,
                    const int *ball1_x, const int *ball1_y,
                    int *scPlayer1, int *scPlayer2) {
    for (int y = 0; y < y_line; ++y) {
        for (int x = 0; x < x_line; ++x) {
            if ((x == rocket1_x &&
                (y == *rocket_1_Y - 1 || y == *rocket_1_Y || y == *rocket_1_Y + 1)) ||
                (x == rocket2_x &&
                (y == *rocket_2_Y - 1 || y == *rocket_2_Y || y == *rocket_2_Y + 1))) {
                printf("*");
            } else if (x == *ball1_x && y == *ball1_y) {
                printf("o");
            } else if ((y == 0 && x != 0 && x != x_line - 1) ||
                        (y == y_line - 1 && x != 0 && x != x_line - 1)) {
                printf("~");
            } else if ((x == 0 && y != 0 && y != y_line - 1) ||
                        (x == x_line - 1 && y != 0 && y != y_line - 1) ||
                        (x == x_line / 2)) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
  // функция движения мяча
void moveBall(int *ball1_x, int *ball1_y, int *vector_X, int *vector_Y,
                const int *rocket_1_Y, const int *rocket_2_Y) {
    if (*ball1_y == 1 || *ball1_y == y_line - 2) {
        *vector_Y = -(*vector_Y);
    }
    if (*ball1_x == rocket1_x + 1 &&
        (*ball1_y == *rocket_1_Y - 1 ||*ball1_y == *rocket_1_Y  || *ball1_y == *rocket_1_Y + 1)) {
        *vector_X = -(*vector_X);
    }
    if (*ball1_x == rocket2_x - 1 &&
        (*ball1_y == *rocket_2_Y - 1 || *ball1_y == *rocket_2_Y  || *ball1_y == *rocket_2_Y + 1)) {
        *vector_X = -(*vector_X);
    }

    *ball1_y += *vector_Y;
    *ball1_x += *vector_X;
}
  // функция проверки строки и того кто победилбедил
int checkTablo(int *scPlayer1, int *scPlayer2, int *ball1_x, int *ball1_y) {
    if (*ball1_x < 2) {
        *scPlayer2 += 1;
        *ball1_x = ball_x;
        *ball1_y = ball_y;
    }
    if (*ball1_x > x_line - 3) {
        *scPlayer1 += 1;
        *ball1_x = ball_x;
        *ball1_y = ball_y;
    }
    if (*scPlayer1 == win_balls) {
        printf("\n\tПобедил первый игрок набрав %d второй игрок набрал %d.", *scPlayer1, *scPlayer2);
        return TRUE;
    } else if (*scPlayer2 == win_balls) {
        printf("\n\tПобедил второй игрок набрав %d первый игрок набрал %d.", *scPlayer2, *scPlayer1);
        return TRUE;
    }
    return FALSE;
}
// функция чистки экрана
void Screenclear(void) {
    printf("\33[0d\33[2J");
}

int main(void) {
    int rocket_1_Y = rocket1_y;
    int rocket_2_Y = rocket2_y;

    int ball_X = ball_x;
    int ball_Y = ball_y;
    int vector_X = -1;
    int vector_Y = 1;

    int score_Player_1 = 0;
    int score_Player_2 = 0;

    while (TRUE) {
        Rendering_screen(&rocket_1_Y, &rocket_2_Y, &ball_X, &ball_Y,
                                                        &score_Player_1, &score_Player_2);
        move_rocket(&rocket_1_Y, &rocket_2_Y);
        moveBall(&ball_X, &ball_Y,
                    &vector_X, &vector_Y,
                    &rocket_1_Y, &rocket_2_Y);
        Screenclear();

        if (checkTablo(&score_Player_1, &score_Player_2,
                                &ball_X, &ball_Y)) {
            break;
        }
    }
    return 0;
}
