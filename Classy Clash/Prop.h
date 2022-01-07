#include "raylib.h"

class Prop {
public:
    Prop(Vector2 position, Texture2D _texture);
    void render(Vector2 changeVector);
    Rectangle getCollisionRectangle(Vector2 changeVector);
    void unloadTextures();

private:
    Texture2D texture{};
    Vector2 worldPosition{};
    Vector2 screenPosition{};
    float scale{4.0f};
};