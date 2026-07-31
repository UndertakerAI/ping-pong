#include <ncurses.h>
#include <stdio.h>

#define HEIGHT 25 // высота поля
#define WIDTH 80 // ширина поля
#define WINSCORE 21 // счет для выигрыша


int check_touch_arena(int BallPosX, int BallPosY); // функция для проверки столкновения мяча со стенками
int check_touch_rocket(int BallPosX, int BallPosY, int RocketPos); // функция для проверки столкновения мяча с ракеткой
void print_arena(int ScorePlayer1, int ScorePlayer2, int Rocket1PosY, int Rocket2PosY, int BallPosX,
                 int BallPosY); // функция для отрисовки поля

int main(void) {
    int Rocket1PosY = HEIGHT / 2 - 1;
    int Rocket2PosY = HEIGHT / 2 - 1;
    int BallPosX = WIDTH / 2;
    int BallPosY = HEIGHT / 2;
    int ScorePlayer1 = 0;
    int ScorePlayer2 = 0;
    int BallDirX = -1;
    int BallDirY = 0;
    chtype command = 0;
    initscr();
    cbreak(); // отключение буферизации ввода
    noecho(); // без вывода введенных символы
    nodelay(stdscr, TRUE);  // игра продолжается, если пользователь ничего не вводит
    print_arena(ScorePlayer1, ScorePlayer2, Rocket1PosY, Rocket2PosY, BallPosX, BallPosY);
    while (ScorePlayer1 < WINSCORE && ScorePlayer2 < WINSCORE && command != 'e') {
        int touch_result;
        command = getch();
        // обработка движения ракеток
        if (command == 'z' || command == 'Z') {
            if (Rocket1PosY < HEIGHT - 4) Rocket1PosY++;
        } else if (command == 'a' || command == 'A') {
            if (Rocket1PosY > 1) Rocket1PosY--;
        } else if (command == 'm' || command == 'M') {
            if (Rocket2PosY < HEIGHT - 4) Rocket2PosY++;
        } else if (command == 'k' || command == 'K') {
            if (Rocket2PosY > 1) Rocket2PosY--;
        }
        // движение мяча
        BallPosX += BallDirX;
        BallPosY += BallDirY;
        // проверка столкновения со стенками
        touch_result = check_touch_arena(BallPosX, BallPosY);
        // верхняя стенка
        if (touch_result == 2) {
            BallDirY = -1;
            BallPosY = HEIGHT - 2;
        } else if (touch_result == 3) {  // нижняя стенка
            BallDirY = 1;
            BallPosY = 1;
        }
        // проверка столкновения с первой ракеткой
        if (BallPosX == 2) {
            int touch_rocket = check_touch_rocket(BallPosX, BallPosY, Rocket1PosY);
            if (touch_rocket == 1) {
                BallDirX = 1;
                BallDirY = 1;
            } else if (touch_rocket == 2) {
                BallDirX = 1;
                BallDirY = 0;
            } else if (touch_rocket == 3) {
                BallDirX = 1;
                BallDirY = -1;
            }
        } else if (BallPosX == 0) {  // гол второму игроку
            ScorePlayer2++;
            BallPosX = WIDTH / 2;
            BallPosY = HEIGHT / 2;
            BallDirX = -1;
            BallDirY = 0;
            Rocket1PosY = HEIGHT / 2 - 1;
            Rocket2PosY = HEIGHT / 2 - 1;
        } else if (BallPosX == WIDTH - 3) {  // проверка столкновения со второй ракеткой
            int touch_rocket = check_touch_rocket(BallPosX, BallPosY, Rocket2PosY);
            if (touch_rocket == 1) {
                BallDirX = -1;
                BallDirY = 1;
            } else if (touch_rocket == 2) {
                BallDirX = -1;
                BallDirY = 0;
            } else if (touch_rocket == 3) {
                BallDirX = -1;
                BallDirY = -1;
            }
        } else if (BallPosX == WIDTH - 1) {  // гол первому игроку
            ScorePlayer1++;
            BallPosX = WIDTH / 2;
            BallPosY = HEIGHT / 2;
            BallDirX = 1;
            BallDirY = 0;
            Rocket1PosY = HEIGHT / 2 - 1;
            Rocket2PosY = HEIGHT / 2 - 1;
        }
        print_arena(ScorePlayer1, ScorePlayer2, Rocket1PosY, Rocket2PosY, BallPosX, BallPosY);
        delay_output(75);
    }
    if (ScorePlayer1 >= WINSCORE) {
        clear();
        printw("Player 1 Wins!");
    } else if (ScorePlayer2 >= WINSCORE) {
        clear();
        printw("Player 2 Wins!");
    } else {
        clear();
        printw("Game over!");
    }
    refresh();
    delay_output(2000);
    endwin();
    return 0;
}

int check_touch_arena(int BallPosX, int BallPosY) {
    int flag = 1;
    if (BallPosY == HEIGHT - 2) flag = 2;
    if (BallPosY == 1) flag = 3;
    if (BallPosX == 1) flag = 4;
    if (BallPosX == WIDTH - 2) flag = 5;
    return flag;
}

int check_touch_rocket(int BallPosX, int BallPosY, int RocketPos) {
    int flag = 0;
    if (BallPosX == 2 || BallPosX == WIDTH - 3) {
        if (BallPosY == RocketPos)
            flag = 3;
        else if (BallPosY == RocketPos + 1)
            flag = 2;
        else if (BallPosY == RocketPos + 2)
            flag = 1;
    }
    return flag;
}

void print_arena(int ScorePlayer1, int ScorePlayer2, int Rocket1PosY, int Rocket2PosY, int BallPosX,
                 int BallPosY) {
    clear();
    printw("Score first player = %d | Score second player = %d\n", ScorePlayer1, ScorePlayer2);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1) {
                printw("-");
            } else if (j == BallPosX && i == BallPosY) {
                printw("o");
            } else if (j == 0 || j == WIDTH - 1) {
                printw("|");
            } else if (j == WIDTH / 2) {
                printw("|");
            } else if (j == WIDTH / 2 + 1) {
                printw("|");
            } else if (j == 1 && i >= Rocket1PosY && i < Rocket1PosY + 3) {
                printw("|");
            } else if (j == WIDTH - 2 && i >= Rocket2PosY && i < Rocket2PosY + 3) {
                printw("|");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
    refresh();
}