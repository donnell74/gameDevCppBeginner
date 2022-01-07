#include "BaseCharacter.h"

BaseCharacter::BaseCharacter() {

}

void BaseCharacter::unloadTextures() {
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}

void BaseCharacter::undoMovement() {
    worldPosition = worldPositionLastFrame;
}

Rectangle BaseCharacter::getCollisionRectangle() {
    return Rectangle{screenPosition.x, screenPosition.y, width * scale, height * scale};
}

void BaseCharacter::tick(float deltaTime) {
    worldPositionLastFrame = worldPosition;

    runningTime += GetFrameTime();
    if (runningTime >= updateTime)
    {
        runningTime = 0.0;
        frame += 1;
        if (frame > maxFrames)
        {
            frame = 0;
        }
    }

    // draw the enemy
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
    Rectangle destination{screenPosition.x, screenPosition.y, scale * width, scale * height};
    Vector2 origin{};
    DrawTexturePro(texture, source, destination, origin, 0.0, WHITE);    
}