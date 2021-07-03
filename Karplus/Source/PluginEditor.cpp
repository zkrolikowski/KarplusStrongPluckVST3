/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KarplusAudioProcessorEditor::KarplusAudioProcessorEditor (KarplusAudioProcessor& p)
    : AudioProcessorEditor (&p), 
	  audioProcessor (p), 
	  keyboardComponent(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{

	addAndMakeVisible(keyboardComponent);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 160);

   /* midiVolume.setSliderStyle(juce::Slider::LinearBarVertical);
    midiVolume.setRange(0.0, 127.0, 1.0);
    midiVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    midiVolume.setPopupDisplayEnabled(true, false, this);
    midiVolume.setTextValueSuffix(" Volume");
    midiVolume.setValue(1.0);

    addAndMakeVisible(&midiVolume);
    midiVolume.addListener(this);*/
}

KarplusAudioProcessorEditor::~KarplusAudioProcessorEditor()
{
}

//==============================================================================
void KarplusAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Midi Volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void KarplusAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //midiVolume.setBounds(40, 30, 20, getHeight() - 60);
	keyboardComponent.setBounds(10, 10, getWidth() - 20, getHeight() - 20);
}

void KarplusAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{

}
