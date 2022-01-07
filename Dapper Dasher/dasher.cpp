#include "raylib.h"

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 380;

struct AnimData {
    Rectangle rectangle;
    Vector2 position;
    int frame;
    int lastFrame;
    float updateRateTime;
    float runningTime;
};

bool isOnGround(AnimData animData, int windowHeight) {
    return animData.position.y >= windowHeight - animData.rectangle.width;
}

AnimData updateAnimData(AnimData animData, float deltaTime) {
    animData.runningTime += deltaTime;
    if (animData.runningTime >= animData.updateRateTime) {
        animData.runningTime = 0.0;

        // Update Scarfy
        animData.rectangle.x = animData.frame * animData.rectangle.width;
        animData.frame += 1;
        if (animData.frame > animData.lastFrame) {
            animData.frame = 0;
        }
    }

    return animData;
}

int main() {
    // Init window for drawing and loading assets
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");
    SetTargetFPS(60);

    int gravity = 1000; // acceleration due to gravity (pixels/s)/s

    // Scarfy variables
    const int scarfyJumpVelocity = -400; // jump velocity (pixels/second)
    int scarfyVelocity = 0;
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{
        {0, 0, scarfy.width / 6, scarfy.height}, // Rectangle rectangle
        {WINDOW_WIDTH / 2 - scarfyData.rectangle.width / 2, WINDOW_HEIGHT - scarfyData.rectangle.height}, // Vector2 position
        0, // int frame
        5, // int lastFrame
        1.0 / 12.0, // float updateRateTime
        0.0 // float runningTime
    };

    // Nebula variables
    const int nebulaVelocity = -400; // x velocity (pixels/s)/s
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfNebulaArray = 1;
    AnimData nebulaArray[sizeOfNebulaArray];
    for (int i = 0; i < sizeOfNebulaArray; i++ ) {
        AnimData nebulaData{ 
            {0, 0, nebula.width / 8, nebula.height / 8}, // Rectangle rectangle
            {WINDOW_WIDTH + (300 * i), WINDOW_HEIGHT - nebula.height / 8}, // Vector2 position
            0, // int frame
            7, // int lastFrame
            1.0 / 12.0, // float updateRateTime
            0.0 // runningTime
        };
        nebulaArray[i] = nebulaData;
    }

    float finishLine = nebulaArray[sizeOfNebulaArray - 1].position.x + 100;

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float backgroundX{};

    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float midgroundX{};

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float foregroundX{};

    bool collision;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // Begin game logic
        float deltaTime = GetFrameTime();
        
        backgroundX -= 20 * deltaTime;
        if (backgroundX <= -background.width * 2) {
            backgroundX = 0.0;
        }

        midgroundX -= 40 * deltaTime;
        if (midgroundX <= -midground.width * 2) {
            midgroundX = 0.0;
        }

        foregroundX -= 80 * deltaTime;
        if (foregroundX <= -foreground.width * 2) {
            foregroundX = 0.0;
        }

        // draw background
        Vector2 backgroundPosition{backgroundX, 0.0};
        Vector2 duplicateBackgroundPosition{backgroundX + background.width * 2, 0.0};
        DrawTextureEx(background, backgroundPosition, 0, 2.0, WHITE);
        DrawTextureEx(background, duplicateBackgroundPosition, 0, 2.0, WHITE);

        // draw midground
        Vector2 midgroundPosition{midgroundX, 0.0};
        Vector2 duplicateMidgroundPosition{midgroundX + midground.width * 2, 0.0};
        DrawTextureEx(midground, midgroundPosition, 0, 2.0, WHITE);
        DrawTextureEx(midground, duplicateMidgroundPosition, 0, 2.0, WHITE);

        // draw foreground
        Vector2 foregroundPosition{foregroundX, 0.0};
        Vector2 duplicateForegroundPosition{foregroundX + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, foregroundPosition, 0, 2.0, WHITE);
        DrawTextureEx(foreground, duplicateForegroundPosition, 0, 2.0, WHITE);

        if (isOnGround(scarfyData, WINDOW_HEIGHT)) {
            // Rectangle on ground
            scarfyVelocity = 0;
        } else {
            // Rectangle in air
            scarfyVelocity += gravity * deltaTime;
        } 

        if (IsKeyPressed(KEY_SPACE) && scarfyVelocity == 0) {
            scarfyVelocity = scarfyJumpVelocity;
        }

        // Update positions
        scarfyData.position.y += scarfyVelocity * deltaTime;
        for (int i = 0; i < sizeOfNebulaArray; i++) {
            nebulaArray[i].position.x += nebulaVelocity * deltaTime;
        }

        finishLine += nebulaVelocity * deltaTime;

        // Update animation frame
        scarfyData = updateAnimData(scarfyData, deltaTime);
        for (int i = 0; i < sizeOfNebulaArray; i++) {
            nebulaArray[i] = updateAnimData(nebulaArray[i], deltaTime);
        }

        // Check for collisions
        for (AnimData nebula : nebulaArray) {
            float pad = 50.0;
            Rectangle nebulaRectangle {
                nebula.position.x + pad,
                nebula.position.y + pad,
                nebula.rectangle.width - 2 * pad,
                nebula.rectangle.height - 2 * pad
            };

            Rectangle scarfyRectangle {
                scarfyData.position.x,
                scarfyData.position.y,
                scarfyData.rectangle.width,
                scarfyData.rectangle.height
            };

            if (CheckCollisionRecs(nebulaRectangle, scarfyRectangle)) {
                collision = true;
            }
        }

        if (collision) {
            // Lose the game
            DrawText("Game Over!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 20, RED);
        }
        else {
            if (finishLine <= 0) {
                DrawText("You Win!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 20, GREEN);
            } else {
                DrawTextureRec(scarfy, scarfyData.rectangle, scarfyData.position, WHITE);
                for (int i = 0; i < sizeOfNebulaArray; i++) {
                    DrawTextureRec(nebula, nebulaArray[i].rectangle, nebulaArray[i].position, WHITE);
                }
            }
        }
        // End game logic

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}

