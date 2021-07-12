/******************************************************************************/
/*!
\file   KarpusSynth.h
\author Zack Krolikowksi
\date   6/28/2021
*/
/******************************************************************************/

#pragma once

#include <JuceHeader.h>
#include "Pluck.h"

// number of starting samples
#define INIT_POW 100

class KarpusSynth : public juce::SynthesiserVoice
{
public:
	KarpusSynth();
	bool canPlaySound(juce::SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity,
		juce::SynthesiserSound*, int /*pitchWheelPosition*/)override;
	void stopNote(float velocity, bool allowTailOff) override;
	void renderNextBlock(juce::AudioSampleBuffer& buffer, int startSample, int numSamples) override;

	// TODO implement theses functions
	void pitchWheelMoved(int) override {}
	void controllerMoved(int, int) override {}

	void updateADSR(const juce::ADSR::Parameters& newParameters);

private:

	Pluck<float> pluck;           // Filter to generate samples
	float startOfPluck[INIT_POW]; // Inital burst of energy for pluck
	int sampleNumber;			  // Number of samples generated
	juce::ADSR adsr;              // ADSR to better contol the pluck filter
};

struct KarpusSound : public juce::SynthesiserSound
{
	KarpusSound() {}

	bool appliesToNote(int) override { return true; }
	bool appliesToChannel(int) override { return true; }
};