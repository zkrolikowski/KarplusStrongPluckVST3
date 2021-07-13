/******************************************************************************/
/*!
\file   KarpusSynth.cpp
\author Zack Krolikowksi
\date   6/28/2021
\brief  Retives samples from teh filter
*/
/******************************************************************************/
#include "KarpusSynth.h"

constexpr float decay = 0.99999f;

KarpusSynth::KarpusSynth() : pluck(static_cast<float>(getSampleRate())), sampleNumber(101)
{
	adsr.setSampleRate(getSampleRate());
}

bool KarpusSynth::canPlaySound(juce::SynthesiserSound* sound)
{
	return dynamic_cast<KarpusSound*>(sound) != nullptr;
}

void KarpusSynth::startNote(int midiNoteNumber, float velocity,
	juce::SynthesiserSound*, int pitchWheelPosition)
{
	// TODO learn move sematices
	// Create new pluck componet for give midi note value
	pluck.StartNote(static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)), decay);

	// Generate inial "engery burst/string pluck" 
	for (int i = 0; i < INIT_POW; ++i)
	{							
		startOfPluck[i] = (rand() / static_cast<float>(RAND_MAX)) * velocity;
	}
	
	adsr.noteOn();
	sampleNumber = 0;
}


void KarpusSynth::stopNote(float velocity, bool allowTailOff)
{
	adsr.noteOff();
	// TODO rewrite to allow tails
	clearCurrentNote();
}

void KarpusSynth::renderNextBlock(juce::AudioSampleBuffer& buffer, int startSample, int numSamples)
{
	while (--numSamples >= 0)
	{
		float currentSample;
		// Is at start of pluck or ringing phase
		if (sampleNumber < INIT_POW)
			currentSample = pluck(startOfPluck[sampleNumber]);
		else
			currentSample = pluck(0);

		currentSample *= adsr.getNextSample();
		currentSample *= volume;

		for (int i = buffer.getNumChannels() - 1; i >= 0; --i)
			buffer.addSample(i, startSample, currentSample);
		
		++startSample;
		++sampleNumber;
	}

	//adsr.applyEnvelopeToBuffer(buffer, startSample, numSamples);

	//	if (angleDelta != 0.0)
//	{
//		if (tailOff > 0.0) // [7]
//		{
//			while (--numSamples >= 0)
//			{
//				auto currentSample = (float)(std::sin(currentAngle) * level * tailOff);
//
//				for (auto i = buffer.getNumChannels(); --i >= 0;)
//					buffer.addSample(i, startSample, currentSample);
//
//				currentAngle += angleDelta;
//				++startSample;
//
//				tailOff *= 0.99; // [8]
//
//				if (tailOff <= 0.005)
//				{
//					clearCurrentNote(); // [9]
//
//					angleDelta = 0.0;
//					break;
//				}
//			}
//		}
//		else
//		{
//			while (--numSamples >= 0) // [6]
//			{
//				auto currentSample = (float)(std::sin(currentAngle) * level);
//
//				for (auto i = buffer.getNumChannels(); --i >= 0;)
//					buffer.addSample(i, startSample, currentSample);
//
//				currentAngle += angleDelta;
//				++startSample;
//			}
//		}
//	}
}

void KarpusSynth::updateADSR(const juce::ADSR::Parameters& newParameters)
{
	adsr.setParameters(newParameters);
}

void KarpusSynth::setVolume(float newVolume)
{
	volume = newVolume;
}