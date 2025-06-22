#include "enemyLogic.h"
#include "audioManager.h"

void handleGoombaCollisions(Rectangle& playerRect, Vector2& velocity, bool& isBig,
    std::vector<Goomba>& goombas, float jumpForce,
    int& lives, bool& gameOver, bool& damageCooldownActive, float& damageTimer)
{
    if (gameOver) return;

    for (Goomba& g : goombas) {
        if (!g.active) continue;

        if (CheckCollisionRecs(playerRect, g.rect)) {
            // Si cae desde arriba lo aplasta
            if (velocity.y > 0 && playerRect.y + playerRect.height <= g.rect.y + 10) {
                velocity.y = jumpForce;
                g.active = false;
            }
            // Si choca de lado y no está en cooldown
            else if (!damageCooldownActive) {
                if (isBig) {
                    isBig = false;
                }
                else {
                    lives--;
                    if (lives == 0) PlayDeathSound();
                }
                damageCooldownActive = true;
                damageTimer = 0.0f; // reinicia el temporizador
            }
            break;
        }
    }
}