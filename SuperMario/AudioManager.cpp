#include "raylib.h"
#include "audioManager.h"

static Sound jumpSound, coinSound, powerupAppearSound, powerupCollectSound, deathSound;
static bool audioReady = false;

void InitAudioManager() {
    InitAudioDevice();
    if (IsAudioDeviceReady()) {
        const char* base = "C:/Users/OTERLOK/Desktop/mario/assets/sounds/effects/";
        jumpSound = LoadSound(TextFormat("%sjump.wav", base));
        coinSound = LoadSound(TextFormat("%scoin.wav", base));
        powerupAppearSound = LoadSound(TextFormat("%spowerupappear.wav", base));
        powerupCollectSound = LoadSound(TextFormat("%spowerupcollect.wav", base)); 
        deathSound = LoadSound(TextFormat("%sdeath.wav", base));
        audioReady = true;
    }
}

void UnloadAudioManager() {
    if (audioReady) {
        UnloadSound(jumpSound);
        UnloadSound(coinSound);
        UnloadSound(powerupAppearSound);
        UnloadSound(powerupCollectSound);
        UnloadSound(deathSound);
        CloseAudioDevice();
        audioReady = false;
    }
}

void PlayJumpSound() { if (audioReady) PlaySound(jumpSound); }
void PlayCoinSound() { if (audioReady) PlaySound(coinSound); }
void PlayPowerupAppearSound() { if (audioReady) PlaySound(powerupAppearSound); }
void PlayPowerupCollectSound() { if (audioReady) PlaySound(powerupCollectSound); }
void PlayDeathSound() { if (audioReady) PlaySound(deathSound); }