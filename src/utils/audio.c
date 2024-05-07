//
// audio.c
//

#include "audio.h"

static PlaydateAPI *pd = NULL;
static const struct playdate_sound *snd = NULL;

static AudioSample *clickSound = NULL;
static SamplePlayer *clickSoundPlayer = NULL;

// Public functions

void loadSounds(PlaydateAPI *p) {
	pd = p;
	snd = p->sound;

	clickSound = snd->sample->load("sounds/ui_click.wav");
	clickSoundPlayer = snd->sampleplayer->newPlayer();
	snd->sampleplayer->setSample(clickSoundPlayer, clickSound);
	snd->sampleplayer->setVolume(clickSoundPlayer, 0.5, 0.5);
}

PDSynth *createSynth(SoundWaveform waveform, float attack, float decay, float sustain, float release) {
	PDSynth *synth = snd->synth->newSynth();
	snd->synth->setWaveform(synth, waveform);
	snd->synth->setAttackTime(synth, attack);
	snd->synth->setDecayTime(synth, decay);
	snd->synth->setSustainLevel(synth, sustain);
	snd->synth->setReleaseTime(synth, release);

	return synth;
}

void playClickSound(void) { snd->sampleplayer->play(clickSoundPlayer, 1, 1.0); }

void playSample(SamplePlayer *player, AudioSample *sample) {
	pd->sound->sampleplayer->setSample(player, sample);
	pd->sound->sampleplayer->play(player, 1, 1.0);
}
