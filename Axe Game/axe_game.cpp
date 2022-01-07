#include "raylib.h"

int main() {
    // Circle Constants
    int circleCenterX = 175;
    int circleCenterY = 100;
    int circleRadius = 25;

    // Axe Constants
    int axeTopLeftX = 300;
    int axeTopLeftY = 0;
    int axeVelocity = 10;
    int axeLength = 50;

    // Screen Constants
    int screenWidth = 800;
    int screenHeight = 450;

    // Collision variables
    bool collisionWithAxe = false;
    
    // Init steps
    InitWindow(screenWidth, screenHeight, "Axe Game");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        // Circle edges
        int leftCircleX = circleCenterX - circleRadius;
        int rightCircleX = circleCenterX + circleRadius;
        int topCircleY = circleCenterY - circleRadius;
        int bottomCircleY = circleCenterY + circleRadius;

        // Axe edges
        int leftAxeX = axeTopLeftX;
        int rightAxeX = axeTopLeftX + axeLength;
        int topAxeY = axeTopLeftY;
        int bottomAxeY = axeTopLeftY + axeLength;

        BeginDrawing();
        ClearBackground(WHITE);

        // Are the two objects in collision
        collisionWithAxe = bottomAxeY >= topCircleY;
        collisionWithAxe &= topAxeY <= bottomCircleY;
        collisionWithAxe &= leftAxeX <= rightCircleX;
        collisionWithAxe &= rightAxeX >= leftCircleX;

        if (collisionWithAxe) {
            DrawText("Game Over!", 400, 200, 20, RED);
        } else {
            // Game logic begins
            DrawCircle(circleCenterX, circleCenterY, circleRadius, BLUE);
            DrawRectangle(axeTopLeftX, axeTopLeftY, axeLength, axeLength, RED);

            // Move the axe
            axeTopLeftY += axeVelocity;
            if (axeTopLeftY > screenHeight || axeTopLeftY <= 0) {
                axeVelocity = -axeVelocity;
            }

            // Give player ability to move circle
            if (IsKeyDown(KEY_D) && rightCircleX < screenWidth) {
                circleCenterX += 10;
            }

            if (IsKeyDown(KEY_A) && leftCircleX > 0) {
                circleCenterX -= 10;
            }

            if (IsKeyDown(KEY_S) && bottomCircleY < screenHeight) {
                circleCenterY += 10;
            }

            if (IsKeyDown(KEY_W) && topCircleY > 0) {
                circleCenterY -= 10;
            }
            // Game logic ends
        }

        EndDrawing();
    }
}