#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

void InitAudioManager();
void UnloadAudioManager();

void PlayJumpSound();
void PlayCoinSound();
void PlayPowerupAppearSound();
void PlayPowerupCollectSound();
void PlayDeathSound();

#endif