/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class KarplusAudioProcessorEditor  : public juce::AudioProcessorEditor/*,
                                     private juce::Slider::Listener*/
{
public:
    KarplusAudioProcessorEditor (KarplusAudioProcessor&);
    ~KarplusAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    void setUpSlider(juce::Slider& slider, double rangeLow, double rangeHigh, double start, const juce::String& suffex);

    //void sliderValueChanged(juce::Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KarplusAudioProcessor& audioProcessor;

    juce::Slider attackRate;   // attack rate in seconds of adsr
    juce::Slider decayRate;    // decay rate in seconds of adsr
    juce::Slider sustainLevel; // sustaion level in ? ? of adsr // TO DO either change mouse over text, or give in dB and transle to linear gain 
    juce::Slider relaseRate;   // relase rate in seconds of adsr
    juce::Slider volume;       // Max output volume

    // TODO
	juce::MidiKeyboardState keyboardState;
	juce::MidiKeyboardComponent keyboardComponent;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KarplusAudioProcessorEditor)
};
