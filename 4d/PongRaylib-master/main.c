// Pong game written in C
// By Fakecrafter

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <raylib.h>
//#include "pong.h"       // include headerfile






int main(int argc, char *argv[])
{
    static int player_x = 30;
    int player_y = 1920/2;
    char input;

    if (argc == 1)
    {
        printf("Too few arguments!\n");
        return 0;
    }
    else
    {
        if (argv[1] == "2")
        {
            int mode = 2;
        }
        else if(argv[1] == "1")
        {
            int mode = 1;
        }
    }


    //Create Display
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Pong");

    int PaddleSpeed = 10;

    //Player 1: paddle
    Rectangle paddle1 = { 30, (float)GetScreenHeight()/2, 30, 120};
    int Score1 = 0;

    //Player 2: paddle
    Rectangle paddle2 = { GetScreenWidth()-60, (float)GetScreenHeight()/2, 30, 120};
    int Score2 = 0;


    //Ball
    Rectangle ball = { (float)GetScreenWidth()/2, (float)GetScreenHeight()/2, 30, 30};
    Vector2 ballSpeed = { (float)5.0, (float)5.0};

    SetTargetFPS(90);
    HideCursor();



    while(!WindowShouldClose())
    {

        if (IsKeyDown(KEY_D) && paddle1.y > 0)          paddle1.y -= 1.0f * PaddleSpeed;
        if (IsKeyDown(KEY_F) && paddle1.y < 1080 - 120) paddle1.y += 1.0f * PaddleSpeed;

        if (IsKeyDown(KEY_K) && paddle2.y > 0)          paddle2.y -= 1.0f * PaddleSpeed;
        if (IsKeyDown(KEY_J) && paddle2.y < 1080 - 120) paddle2.y += 1.0f * PaddleSpeed;

        ball.y += ballSpeed.y;
        ball.x += ballSpeed.x;
        if(ball.x <= -40)
        {
            Score2++;
            //reset;
            ball.x = (float)GetScreenWidth()/2;
            ball.y = (float)GetScreenHeight()/2;
            ballSpeed.x = -4.0f;
            ballSpeed.y =  4.0f;
            continue;
        }

        if(ball.x >= (GetScreenWidth() + 40))
        {
            Score1++;
            //reset;
            ball.x = (float)GetScreenWidth()/2;
            ball.y = (float)GetScreenHeight()/2;
            ballSpeed.x = 4.0f;
            ballSpeed.y = 4.0f;
            continue;
        }

        if(CheckCollisionRecs(paddle1, ball))
        {
            ball.x += 10.0f;
            ballSpeed.x -=  1.5f;
            ballSpeed.x *= -1.0f;
        }

        if(CheckCollisionRecs(paddle2, ball))
        {
            ball.x -= 10.0f;
            ballSpeed.x +=  1.5f;
            ballSpeed.x *= -1.0f;
        }


        if ((ball.y >= (GetScreenHeight() - ball.height)) || (ball.y <= 0)) ballSpeed.y *= -1.0f;


        //Drawing

        BeginDrawing();


            ClearBackground(BLACK);
            DrawFPS(10, 10);
            DrawText(TextFormat("%i", Score1), GetScreenWidth() / 2 - 100, 100, 50.0, GRAY);
            DrawText(TextFormat("%i", Score2), GetScreenWidth() / 2 + 100, 100, 50.0, GRAY);
            DrawRectangleRec(paddle1, WHITE);
            DrawRectangleRec(paddle2, WHITE);
            DrawRectangleRec(ball, WHITE);
            DrawFPS(10, 10);


        EndDrawing();
    }
    printf("Player_Left Score: %d\nPlayer_Right Score %d\n", Score1, Score2);
    // destroy everything and quit the program
    CloseWindow();
    return 0;
}







