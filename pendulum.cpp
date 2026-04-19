#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include <math.h>

#define WIDTH 600
#define HEIGHT 300
#define G 10
#define MASS 50

class Pendulum
{
private:
    int length;
    Vector2 start, end;
    float theta;
    float omega = 0.0f; // angular velocity
    float alpha = 0.0f; // angular acceleration

public:
    Pendulum(int length, Vector2 start, float theta)
    {
        this->length = length;
        this->start = start;
        this->theta = theta;
        end = {start.x + length * sin(theta), start.y + length * cos(theta)};
    }
    void display()
    {
        DrawLine(this->start.x, this->start.y, this->end.x, this->end.y, WHITE);
        DrawCircle(this->end.x, this->end.y, 20, RED);
    }
    void update(float dt, float damping)
    {
        // Angular acceleration
        this->alpha = -MASS*(G / (float)length) * sin(this->theta);

        // Update velocity
        this->omega += this->alpha * dt;
        this->omega *= damping;

        // Update angle
        this->theta += this->omega * dt;

        // Update end point
        this->end.x = this->start.x + length * sin(this->theta);
        this->end.y = this->start.y + length * cos(this->theta);
    }
};

int main(int argc, char const *argv[])
{
    Vector2 startPosition = (Vector2){WIDTH / 2, 30};
    InitWindow(WIDTH, HEIGHT, "pendulum");
    Pendulum pendulum = Pendulum(200, startPosition, 90 * DEG2RAD);
    int i = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        int FPS = GetFPS();
        int rr = GetMonitorRefreshRate(0);
        ClearBackground(BLACK);
        BeginDrawing();
        i++;
        pendulum.display();
        pendulum.update(dt, 0.9995f);
        DrawText(
            TextFormat("FPS = %d\t Refresh Rate=%d", FPS,rr), 
            250, 280, 10, WHITE
        );
        EndDrawing();
    }

    return 0;
}
