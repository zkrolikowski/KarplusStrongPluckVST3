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
	SynthAudioSource(/*juce::MidiKeyboardState& state*/);

	void prepareToPlay(int /*samplesPerBlackExpected*/, double sampleRate) override;
	void releaseResources() override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void getNextAudioBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);

	void setDecayRate(float newDecay);

private:

	juce::Synthesiser synth;
	//juce::MidiKeyboardState& state;
};

