#include "audioManager.h"

static Music menuMusic;
static Music gameMusic;

static Sound coinSound;
static Sound powerupAppearSound;
static Sound powerupCollectSound;
static Sound jumpSound;
static Sound deathSound;
static Sound kickSound;

static GameState currentMusicState = (GameState)(-1);
static bool audioReady = false;

void InitAudioManager() {
    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        TraceLog(LOG_WARNING, "Audio device not ready");
        return;
    }

    const char* baseEffects = "C:/Users/OTERLOK/Desktop/mario/assets/sounds/effects/";
    const char* baseMusic = "C:/Users/OTERLOK/Desktop/mario/assets/sounds/music/";

    jumpSound = LoadSound(TextFormat("%sjump.wav", baseEffects));
    coinSound = LoadSound(TextFormat("%scoin.wav", baseEffects));
    powerupAppearSound = LoadSound(TextFormat("%spowerupappear.wav", baseEffects));
    powerupCollectSound = LoadSound(TextFormat("%spowerupcollect.wav", baseEffects));
    deathSound = LoadSound(TextFormat("%sdeath.wav", baseEffects));
    kickSound = LoadSound(TextFormat("%skick.wav", baseEffects)); // ✅ nuevo sonido

    menuMusic = LoadMusicStream(TextFormat("%soverworld.wav", baseMusic));
    gameMusic = LoadMusicStream(TextFormat("%soverworld.wav", baseMusic));

    audioReady = true;
}

void UnloadAudioManager() {
    if (!audioReady) return;

    StopMusicStream(menuMusic);
    StopMusicStream(gameMusic);
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(gameMusic);

    UnloadSound(jumpSound);
    UnloadSound(coinSound);
    UnloadSound(powerupAppearSound);
    UnloadSound(powerupCollectSound);
    UnloadSound(deathSound);
    UnloadSound(kickSound); //  descarga el kick

    CloseAudioDevice();
    audioReady = false;
}

void PlayCoinSound() { if (audioReady) PlaySound(coinSound); }
void PlayPowerupAppearSound() { if (audioReady) PlaySound(powerupAppearSound); }
void PlayPowerupCollectSound() { if (audioReady) PlaySound(powerupCollectSound); }
void PlayJumpSound() { if (audioReady) PlaySound(jumpSound); }
void PlayDeathSound() { if (audioReady) PlaySound(deathSound); }
void PlayKickSound() { if (audioReady) PlaySound(kickSound); }

void SetMusicState(GameState newState) {
    if (!audioReady || newState == currentMusicState) return;

    if (currentMusicState == MENU)    StopMusicStream(menuMusic);
    if (currentMusicState == PLAYING) StopMusicStream(gameMusic);

    if (newState == MENU)    PlayMusicStream(menuMusic);
    if (newState == PLAYING) PlayMusicStream(gameMusic);

    currentMusicState = newState;
}

void UpdateMusic() {
    if (!audioReady) return;

    if (currentMusicState == MENU)    UpdateMusicStream(menuMusic);
    if (currentMusicState == PLAYING) UpdateMusicStream(gameMusic);
}