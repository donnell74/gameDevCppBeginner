#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter {
public:
    BaseCharacter();
    void unloadTextures();
    void undoMovement();
    Rectangle getCollisionRectangle();
    virtual void tick(float deltaTime);

    Vector2 getWorldPosition()
    {
        return worldPosition;
    }
    bool getAlive() {
        return alive;
    }
    void setAlive(bool _alive) {
        alive = _alive;
    }
protected:
    Texture2D texture{};
    Texture2D run{};
    Texture2D idle{};
    Vector2 screenPosition{};
    Vector2 worldPosition{};
    Vector2 worldPositionLastFrame{};
    // Animation variables;
    // positive is facing right; negative is facing left
    float rightLeft{1.0f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.0 / 12.0f};
    float speed{4.0f};
    float width{};
    float height{};
    float scale{4.0f};
private:
    bool alive{true};
};

#endif