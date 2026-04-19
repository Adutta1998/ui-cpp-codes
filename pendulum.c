#include<stdio.h>
#include<string.h>
#include<raylib.h>
#include<math.h>

#define WIDTH 600
#define HEIGHT 300
#define G 10
// #define MASS 5

void drawPendulum(const int length, Vector2 start, float theta){
    Vector2 end = (Vector2){
        start.x+length*cos(theta),
        start.y+length*sin(theta),
    };
    DrawLine(start.x,start.y,end.x,end.y,WHITE);
    DrawCircle(end.x,end.y,20, RED);
}

int main(int argc, char const *argv[])
{
    Vector2 startPosition = (Vector2){WIDTH/2,30};
    InitWindow(WIDTH,HEIGHT,"pendulum");
    int i=0;
    
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
        i++;
        drawPendulum(200, startPosition, 0*DEG2RAD);
        DrawText(TextFormat("%d",i),250,250,10,WHITE);
        EndDrawing();
        
    }
    
    return 0;
}
