#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "raylib.h"

enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

void InitAudioManager();
void UnloadAudioManager();

void PlayCoinSound();
void PlayPowerupAppearSound();
void PlayPowerupCollectSound();
void PlayJumpSound();
void PlayDeathSound();
void PlayKickSound(); // ✅ nueva función


void SetMusicState(GameState state);
void UpdateMusic();

#endif