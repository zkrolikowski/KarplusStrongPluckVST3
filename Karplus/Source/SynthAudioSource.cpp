#include "SynthAudioSource.h"
#include "KarpusSynth.h"

SynthAudioSource::SynthAudioSource(/*juce::MidiKeyboardState& state) : state(state)*/)
{
	for (int i = 0; i < NUM_VOICES; ++i)
		synth.addVoice(new KarpusSynth());

	synth.addSound(new KarpusSound());
}

void SynthAudioSource::prepareToPlay(int /*samplesPerBlackExpected*/, double sampleRate) 
{
	synth.setCurrentPlaybackSampleRate(sampleRate);
}

void SynthAudioSource::releaseResources()
{

}

void SynthAudioSource::getNextAudioBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	buffer.clear();

	synth.renderNextBlock(buffer, midiMessages,
		0, buffer.getNumSamples());
}

void SynthAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	//bufferToFill.clearActiveBufferRegion();

	juce::MidiBuffer incomingMidi;
	//keyboardState.processNextMidiBuffer(incomingMidi, bufferToFill.startSample, bufferToFill.numSamples, true);    
	//synth.renderNextBlock(*bufferToFill.buffer, incomingMidi,
		//bufferToFill.startSample, bufferToFill.numSamples);

	getNextAudioBlock(*bufferToFill.buffer, incomingMidi);
}

void SynthAudioSource::setDecayRate(float newDecay)
{
	for (int i = synth.getNumVoices(); --i >= 0;)
	{
		if (KarpusSynth* voice = dynamic_cast<KarpusSynth*>(synth.getVoice(i)))
		{
			voice->setDecayRate(newDecay);
		}
	}

}