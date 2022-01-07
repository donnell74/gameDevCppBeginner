#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter {
public:
    Enemy(Vector2 position, Texture2D idleTexture, Texture2D runTexture);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* _target) {
        target = _target;
    };
private:
    Character* target;
    float damagePerSecond{10.0f};
    float radius{25.0f};
};