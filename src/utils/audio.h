//
//  audio.h
//

#ifndef audio_h
#define audio_h

#define TARGET_EXTENSION 1
#include "pd_api.h"

void loadSounds(PlaydateAPI *p);

PDSynth *createSynth(SoundWaveform waveform, float attack, float decay, float sustain, float release);
void playClickSound(void);
void playSample(SamplePlayer *player, AudioSample *sample);

#endif /* audio_h */