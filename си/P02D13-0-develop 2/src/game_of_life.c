#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#define SIZE_X 80
#define SIZE_Y 25
#define LAST_HASH 30

int input (char (*a)[SIZE_X]);
void output(char (*a)[SIZE_X], int speed);
void updatebord (char (*a)[SIZE_X]);
int save_hash (char (*a)[SIZE_X]);
int compare_hash (char (*a)[SIZE_X], int *hash_storage);
int is_live(char (*a)[SIZE_X], int i, int j);

int main() {
    char screen[SIZE_Y][SIZE_X];
    int hash_storage[LAST_HASH];
    int check = input(screen);
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    int speed = 80;
    if (check) {
        freopen("/dev/tty", "r", stdin);
        while (1) {
            updatebord(screen);
            output(screen, speed);
            char c = getch();
            if ((c == '+') && (speed > 10)) {
                speed = speed - 5;
            }
            if ((c == '-') && (speed < 100)) {
                speed = speed + 5;
            }
            napms(speed);
            if (compare_hash(screen, hash_storage) >= 2) {
                break;
            }
        }
    } else {
        printf("n/a");
    }
    endwin();
    return 0;
}


int compare_hash(char (*a)[SIZE_X], int *hash_storage) {
     int check_for_repeat = 0;
     for (int i = 0; i < LAST_HASH; i++) {
         hash_storage[i] = hash_storage[i+1];
     }
     hash_storage[LAST_HASH-1] = save_hash(a);
     for (int i = 0; i < LAST_HASH-1; i++) {
         if (hash_storage[i] == hash_storage[LAST_HASH-1])
             check_for_repeat++;
     }
     return check_for_repeat;
}

int save_hash (char (*a)[SIZE_X]) {
    char string_arr[SIZE_X*SIZE_Y];
    long int num1 = 378551;
    long int num2 = 63689;
    long int hash = 0;
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            string_arr[i*80+j] = a[i][j];
        }
    }
    for (int i = 0 ; i < SIZE_X*SIZE_Y ; i++) {
        hash = hash * num1 + string_arr[i];
        num1 *= num2;
    }
    return hash;
}


void updatebord (char (*a)[SIZE_X]) {
    int live = 0;
    clear();
    char b[SIZE_Y][SIZE_X];
    for (int i = 0 ; i < SIZE_Y ; i++) {
        for (int j = 0 ; j < SIZE_X ; j++) {
            live = is_live(a, i, j);
            b[i][j] = live;
        }
    }
    refresh();

    for (int i = 0 ; i <SIZE_Y ; i++) {
        for (int j = 0 ; j <SIZE_X ; j++) {
            if (b[i][j] == 3) {
                a[i][j] = '0';
            } else if (b[i][j] > 3 || b[i][j] < 2) {
                a[i][j] = '.';
                }
        }
    }
}

int is_live(char (*a)[SIZE_X], int i, int j) {
    int is_live = 0;
    int ni, nj;
    for (int xoff = -1; xoff <= 1; xoff++) {
        for (int yoff=-1; yoff <= 1; yoff++) {
            if (xoff != 0 || yoff != 0) {
                nj = j+xoff;
                ni = i+yoff;
                if (nj== -1) {
                    nj = SIZE_X-1;
                } else if (nj == SIZE_X) {
                 nj = 0;
                }
                if (ni == -1) {
                    ni = SIZE_Y-1;
                } else if (ni == SIZE_Y) {
                    ni = 0;
                }
                if (a[ni][nj] == '0') {
                    is_live++;
                }
            }
        }
    }
    return is_live;
}

int input (char (*a)[SIZE_X]) {
    int flag = 1;
    int check_EOL = 0;
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            scanf("%c", &a[i][j]);
            if (a[i][j] != '.' && a[i][j] != '0')
                flag = 0;
        }
        check_EOL = getchar();
        if (check_EOL != '\n')
            flag = 0;
    }
    return flag;
}


void output(char (*a)[SIZE_X], int speed) {
    clear();
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++)
            printw("%c", a[i][j]);
        printw("\n");
    }
    printw("speed up butn + | speed down butn - | %dms", speed);
    refresh();
}

// gcc -Wall -Werror -Wextra game_of_life.c -lncurses
// ./a.out < 1.txt
