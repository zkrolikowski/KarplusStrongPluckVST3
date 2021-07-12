#include "SynthAudioSource.h"
#include "KarpusSynth.h"

SynthAudioSource::SynthAudioSource() : adsrParamerteres()
{
	for (int i = 0; i < NUM_VOICES; ++i)
		synth.addVoice(new KarpusSynth());

	synth.addSound(new KarpusSound());
	
	adsrParamerteres.attack = 3.0f;
	adsrParamerteres.decay = 3.2f;
	adsrParamerteres.sustain = 0.3f;
	adsrParamerteres.release = 3.0f;
	updateADSR();
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

	const int numSamples = buffer.getNumSamples();

	// Get the next block of data from synth
	synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
	
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

void SynthAudioSource::setAttack(float newAttack)
{
	adsrParamerteres.attack = newAttack;
	updateADSR();
}

void SynthAudioSource::setDecay(float newDecay)
{
	adsrParamerteres.decay = newDecay;
	updateADSR();
}

void SynthAudioSource::setSustain(float newSustain)
{
	adsrParamerteres.sustain = newSustain;
	updateADSR();
}

void SynthAudioSource::setRelease(float newRelease)
{
	adsrParamerteres.release = newRelease;
	updateADSR();
}

void SynthAudioSource::updateADSR()
{
	for (int i = synth.getNumSounds(); --i >= 0;)
	{
		if (KarpusSynth* voice = dynamic_cast<KarpusSynth*>(synth.getVoice(i)))
		{
			voice->updateADSR(adsrParamerteres);
		}
	}
}