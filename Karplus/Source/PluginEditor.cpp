/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define WINDOWWIDTH 620
#define WINDOWHEIGHT 480

#define INITATTACK 0.1f
#define INITDECAY 0.5f
#define INITSUSTAIN -1.9f
#define INITRELASE 0.2f
#define INITVOLUME 1.0f

//==============================================================================
KarplusAudioProcessorEditor::KarplusAudioProcessorEditor (KarplusAudioProcessor& p)
    : AudioProcessorEditor (&p), 
	  audioProcessor (p), 
	  keyboardComponent(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{

	//addAndMakeVisible(keyboardComponent);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(WINDOWWIDTH, WINDOWHEIGHT);

    const juce::String seconds(" seconds");
    
    // Skew to get more accurecy at lower values
    const float timeSkew = 0.5f;
    // Skew to get more accurecy closer to 0 dB
    const float dBSkew = 5;

    // Initalize the sliders
    setUpSlider(attackRate, 0.0, 5.0f, 0.1f, seconds);
    attackRate.setSkewFactor(timeSkew); 
    setUpSlider(decayRate, 0.0, 5.0, 0.5, seconds);
    decayRate.setSkewFactor(timeSkew); 
    setUpSlider(sustainLevel, -96.0f, 0.0f, -1.9f, " dB");
    sustainLevel.setSkewFactor(dBSkew);
    setUpSlider(relaseRate, 0.0f, 5.0f, 0.2f, seconds);
    relaseRate.setSkewFactor(timeSkew);
    setUpSlider(volume, -96.0f, 0.0f, 0.0f, " dB");
    volume.setSkewFactor(dBSkew);

    // Display the sliders
    addAndMakeVisible(&attackRate);
    addAndMakeVisible(&decayRate);
    addAndMakeVisible(&sustainLevel);
    addAndMakeVisible(&relaseRate);
    addAndMakeVisible(&volume);

    // Give sliders lamba call backs on change
    attackRate.onValueChange = [this] 
        { audioProcessor.getSynth().setAttack(static_cast<float>(attackRate.getValue())); };
    decayRate.onValueChange = [this] 
        { audioProcessor.getSynth().setDecay(static_cast<float>(decayRate.getValue())); };
    sustainLevel.onValueChange = [this] 
        { audioProcessor.getSynth().setSustain(static_cast<float>(std::pow(10.0, sustainLevel.getValue()/20))); };
    decayRate.onValueChange = [this] 
        { audioProcessor.getSynth().setRelease(static_cast<float>(relaseRate.getValue())); };
    volume.onValueChange = [this]
        { audioProcessor.getSynth().setVolume(static_cast<float>(volume.getValue()));  };

    // Set inital values
    attackRate.setValue(INITATTACK);
    decayRate.setValue(INITDECAY);
    sustainLevel.setValue(INITSUSTAIN);
    relaseRate.setValue(INITRELASE);
    volume.setValue(INITVOLUME);

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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Midi Volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void KarplusAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //midiVolume.setBounds(40, 30, 20, getHeight() - 60);
	//keyboardComponent.setBounds(10, 10, getWidth() - 20, getHeight() - 20);

    const int border = 20;
    const float scaleWidth = getWidth() / static_cast<float>(WINDOWWIDTH);
    const float scaleHeight = getHeight() / static_cast<float>(WINDOWHEIGHT);

    attackRate.setBounds(static_cast<int>(20 * scaleWidth),
                         static_cast<int>(80 * scaleHeight),
                         static_cast<int>(100 * scaleWidth),
                         static_cast<int>(100 * scaleHeight));

    decayRate.setBounds(static_cast<int>(140 * scaleWidth), 
                        static_cast<int>(80 * scaleHeight), 
                        static_cast<int>(100 * scaleWidth), 
                        static_cast<int>(100 * scaleHeight));

    sustainLevel.setBounds(static_cast<int>(260 * scaleWidth), 
                           static_cast<int>(80 * scaleHeight), 
                           static_cast<int>(100 * scaleWidth), 
                           static_cast<int>(100 * scaleHeight));

    relaseRate.setBounds(static_cast<int>(380 * scaleWidth), 
                         static_cast<int>(80 * scaleHeight), 
                         static_cast<int>(100 * scaleWidth), 
                         static_cast<int>(100 * scaleHeight));

    volume.setBounds(static_cast<int>(500 * scaleWidth), 
                     static_cast<int>(80 * scaleHeight), 
                     static_cast<int>(100 * scaleWidth), 
                     static_cast<int>(100 * scaleHeight));

}

//void KarplusAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
//{
//
//}

void KarplusAudioProcessorEditor::setUpSlider(juce::Slider& slider, double rangeLow, double rangeHigh, double start, const juce::String& suffix)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    slider.setRange(rangeLow, rangeHigh);
    slider.setValue(start);
    slider.setNumDecimalPlacesToDisplay(2);
    slider.setPopupDisplayEnabled(true, true, this);
    slider.setTextValueSuffix(suffix);
}