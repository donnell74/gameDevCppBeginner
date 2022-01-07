#include <string>

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

const int WINDOW_WIDTH = 384;
const int WINDOW_HEIGHT = 384;
const float WORLD_MAP_SCALE = 4.0f;

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy Clash");
    SetTargetFPS(60);

    Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 worldMapPosition{0.0, 0.0};

    Character knight{WINDOW_WIDTH, WINDOW_HEIGHT};
    Enemy goblin{
        Vector2{600.0f, 250.0f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    Enemy slime1{
        Vector2{1000.0f, 250.0f}, 
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };
    Enemy slime2{
        Vector2{600.0f, 1250.0f}, 
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };
    Enemy* enemyArray[3]{
        &goblin,
        &slime1,
        &slime2
    };
    for (Enemy* eachEnemy : enemyArray) {
        eachEnemy->setTarget(&knight);
    }

    Prop props[2] {
        Prop{Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("nature_tileset/Log.png")}
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Begin Game Logic
        worldMapPosition = Vector2Scale(knight.getWorldPosition(), -1.0f);
        DrawTextureEx(worldMap, worldMapPosition, 0.0, WORLD_MAP_SCALE, WHITE);

        // Draw the props
        for (Prop eachProp : props) {
            eachProp.render(knight.getWorldPosition());
        }

        if (!knight.getAlive()) {
            DrawText("Game Over!", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        } else {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.0f, 45.0f, 40, RED);
        }

        knight.tick(GetFrameTime());

        // Check map bounds
        if (knight.getWorldPosition().x < 0.0f ||
            knight.getWorldPosition().y < 0.0f ||
            knight.getWorldPosition().x + WINDOW_WIDTH > worldMap.width * WORLD_MAP_SCALE ||
            knight.getWorldPosition().y + WINDOW_HEIGHT > worldMap.height * WORLD_MAP_SCALE) {
            
            knight.undoMovement();
        }

        // Check for prop collisions
        for (Prop eachProp : props) {
            if (CheckCollisionRecs(knight.getCollisionRectangle(), eachProp.getCollisionRectangle(knight.getWorldPosition()))) {
                knight.undoMovement();
            }
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (Enemy* eachEnemy : enemyArray) {
                if (CheckCollisionRecs(knight.getWeaponCollisionRectangle(), eachEnemy->getCollisionRectangle())) {
                    eachEnemy->setAlive(false);
                }
            }
        }

        for (Enemy* eachEnemy : enemyArray) {
            eachEnemy->tick(GetFrameTime());
        }
        // End Game Logic

        EndDrawing();
    }

    knight.unloadTextures();
    for (Prop eachProp : props) {
        eachProp.unloadTextures();
    }
    for (Enemy* eachEnemy : enemyArray) {
        eachEnemy->unloadTextures();
    }
    UnloadTexture(worldMap);
    CloseWindow();
}