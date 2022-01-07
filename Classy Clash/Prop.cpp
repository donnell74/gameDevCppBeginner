#include "Prop.h"
#include "raylib.h"
#include "raymath.h"

Prop::Prop(Vector2 position, Texture2D _texture) : 
    worldPosition(position), texture(_texture)
{

}

void Prop::render(Vector2 changeVector) {
    screenPosition = Vector2Subtract(worldPosition, changeVector);
    DrawTextureEx(texture, screenPosition, 0.0f, scale, WHITE);
}

Rectangle Prop::getCollisionRectangle(Vector2 changeVector) {
    screenPosition = Vector2Subtract(worldPosition, changeVector);
    return Rectangle{screenPosition.x, screenPosition.y, texture.width * scale, texture.height * scale};
}

void Prop::unloadTextures() {
    UnloadTexture(texture);
}