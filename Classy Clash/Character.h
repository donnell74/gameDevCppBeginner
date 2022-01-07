#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
  public:
    Character(int windowWidth, int windowHeight);
    virtual void tick(float deltaTime) override;
    void takeDamage(float damage);

    Vector2 getScreenPosition() { 
      return screenPosition;
    }
    Rectangle getWeaponCollisionRectangle() {
      return weaponCollisionRectangle;
    }
    float getHealth() const {
      return health;
    }
  private:
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRectangle{};
    float health{100.0f};
};

#endif