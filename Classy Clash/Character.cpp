#include "Character.h"
#include "raylib.h"
#include "raymath.h"

Character::Character(int windowWidth, int windowHeight) {
    texture = LoadTexture("characters/knight_idle_spritesheet.png");
    idle = LoadTexture("characters/knight_idle_spritesheet.png");
    run = LoadTexture("characters/knight_run_spritesheet.png");
    width = texture.width / maxFrames;
    height = texture.height;
    screenPosition = {
        (float)windowWidth / 2.0f - scale * (0.5f * width),
        (float)windowHeight / 2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    if (!getAlive()) {
        return;
    }
    
    BaseCharacter::tick(deltaTime);

    worldPositionLastFrame = worldPosition;

    Vector2 direction{0.0, 0.0};
    if (IsKeyDown(KEY_A))
    {
        direction.x -= 1.0;
    }
    if (IsKeyDown(KEY_D))
    {
        direction.x += 1.0;
    }
    if (IsKeyDown(KEY_W))
    {
        direction.y -= 1.0;
    }
    if (IsKeyDown(KEY_S))
    {
        direction.y += 1.0;
    }

    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction
        direction = Vector2Scale(Vector2Normalize(direction), speed);
        worldPosition = Vector2Add(worldPosition, direction);
        rightLeft = direction.x < 0.0f ? -1.0f : 1.0f;
    }

    texture = Vector2Length(direction) == 0.0 ? idle : run;

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.0f) {
        origin = {0.0f, weapon.height * scale};
        offset = {35.0f, 55.0f};
        weaponCollisionRectangle = {
            getScreenPosition().x + offset.x,
            getScreenPosition().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.0f : 0.0f;
    } else {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.0f, 55.0f};
        weaponCollisionRectangle = {
            getScreenPosition().x + offset.x - weapon.width * scale,
            getScreenPosition().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.0f : 0.0f;
    }

    // Draw the sword
    Rectangle source{0.0f, 0.0f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPosition().x + offset.x, getScreenPosition().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    // DrawRectangleLines(
    //     weaponCollisionRectangle.x, weaponCollisionRectangle.y, weaponCollisionRectangle.width, weaponCollisionRectangle.height, RED
    // );
}

void Character::takeDamage(float damage) {
    health -= damage;
    if (health <= 0.0f) {
        setAlive(false);
    }
}