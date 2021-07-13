/******************************************************************************/
/*!
\file   KarpusSynth.h
\author Zack Krolikowksi
\date   6/28/2021
*/
/******************************************************************************/

#pragma once

#define NUM_VOICES 4

#include <JuceHeader.h>

class SynthAudioSource : public juce::AudioSource
{
public:
	SynthAudioSource();

	void prepareToPlay(int /*samplesPerBlackExpected*/, double sampleRate) override;
	void releaseResources() override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void getNextAudioBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);

	void setAttack(float newAttack);
	void setDecay(float newDecay);
	void setSustain(float newSustain);
	void setRelease(float release);
	void setVolume(float newVolume);

private:

	void updateADSR();

	juce::Synthesiser synth;
	juce::ADSR::Parameters adsrParamerteres;
	float volume;

	//juce::MidiKeyboardState& state;
};

