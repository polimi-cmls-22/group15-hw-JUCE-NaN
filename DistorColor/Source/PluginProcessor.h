/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class DistorColorAudioProcessor  : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    DistorColorAudioProcessor();
    ~DistorColorAudioProcessor() override;
    juce::AudioVisualiserComponent waveViewer;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState& get_Apvts();

    juce::AudioProcessorValueTreeState treeState;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void addBit();
    void removeBit();

    void addOut();
    void removeOut();

    void bitOn();
    void lightOn();
private:

    juce::dsp::Oversampling<float> oversamplingModule;
    juce::dsp::LinkwitzRileyFilter<float> lowPassFilter, highPassFilter;
    
    bool BitCrusher{ false };
    bool Sqrt{ false };

    int bitDepth{ 16 };
    int rateDivide{25};
    float wet{ 0.5 };

    float preampDB{ 0.0 };
    float driveDB{ 0.0 };
    float mix{ 0 };
    float outputDB{ 0.0 };
    float lastSampleRate;
    float cutoff;
    float highcutoff;
    const float piDivisor = 2.0 / juce::MathConstants<float>::pi;

    // parameters
    void parameterChanged(const juce::String& parameterID, float newValue);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistorColorAudioProcessor)
};
