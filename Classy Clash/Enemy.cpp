#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"

Enemy::Enemy(Vector2 position, Texture2D idleTexture, Texture2D runTexture)
{
    worldPosition = position;
    texture = idleTexture;
    idle = idleTexture;
    run = runTexture;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.0f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive()) {
        return;
    }

    Vector2 direction = Vector2Subtract(target->getScreenPosition(), screenPosition);
    if (Vector2Length(direction) < radius)
    {
        direction = {0.0f, 0.0f};
    } else {
        // set worldPos = worldPos + direction
        direction = Vector2Scale(Vector2Normalize(direction), speed);
        worldPosition = Vector2Add(worldPosition, direction);
        rightLeft = direction.x < 0.0f ? -1.0f : 1.0f;
    }
    screenPosition = Vector2Subtract(worldPosition, target->getWorldPosition());

    BaseCharacter::tick(deltaTime);

    texture = Vector2Length(direction) == 0.0 ? idle : run;

    if (CheckCollisionRecs(target->getCollisionRectangle(), getCollisionRectangle())) {
        target->takeDamage(damagePerSecond * deltaTime);
    }
}