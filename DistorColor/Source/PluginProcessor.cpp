/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistorColorAudioProcessor::DistorColorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), treeState(*this, nullptr, "Parameters", createParameterLayout()) 
                        , oversamplingModule(2, 3, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR), waveViewer(1)

#endif
{
    waveViewer.setRepaintRate(30);
    waveViewer.setBufferSize(256);

    treeState.addParameterListener("preampID", this);
    treeState.addParameterListener("driveID", this);
    treeState.addParameterListener("mixID", this);
    treeState.addParameterListener("outputID", this);
    treeState.addParameterListener("cutoffID", this);
  
    treeState.addParameterListener("bitc", this);
    treeState.addParameterListener("sqrt", this);
    treeState.addParameterListener("bitdepth", this);
    treeState.addParameterListener("ratedivide", this);
    treeState.addParameterListener("wet", this);

}

DistorColorAudioProcessor::~DistorColorAudioProcessor()
{
    treeState.removeParameterListener("preampID", this);
    treeState.removeParameterListener("driveID", this);
    treeState.removeParameterListener("mixID", this);
    treeState.removeParameterListener("outputID", this);
    treeState.removeParameterListener("cutoffID", this);
  
    treeState.removeParameterListener("bitc", this);
    treeState.removeParameterListener("sqrt", this);
    treeState.removeParameterListener("bitdepth", this);
    treeState.removeParameterListener("ratedivide", this);
    treeState.removeParameterListener("wet", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout DistorColorAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

    auto pBitCrusher = std::make_unique<juce::AudioParameterBool>("bitc", "Bitc", false);
    
    auto pCutoff = std::make_unique<juce::AudioParameterFloat>("cutoffID",
        "Cutoff", juce::NormalisableRange<float>(4000.0f, 6000.0f, 1.0f, 0.22), 4550.0);
    auto pPreamp = std::make_unique<juce::AudioParameterFloat>("preampID",
        "Preamp", 0.0f, 50.0f, 0.0f);
    auto pDrive = std::make_unique<juce::AudioParameterFloat>("driveID",
        "Drive", 0.0f, 50.0f, 0.0f);
    auto pMix = std::make_unique<juce::AudioParameterFloat>("mixID",
        "Mix", 0.0f, 100.0f, 0.0f);
    auto pOutput = std::make_unique<juce::AudioParameterFloat>("outputID",
        "Output", -30.0f, 30.0f, 0.0f);
    auto pSqrt = std::make_unique<juce::AudioParameterBool>("sqrt", "Sqrt", false);
    auto pbitDepth = std::make_unique<juce::AudioParameterInt>("bitdepth",
      "BitDepth", 8, 32, 8);
    auto prateDivide = std::make_unique<juce::AudioParameterFloat>("ratedivide",
        "RateDivide", 1.0f, 50.0f, 25.0f);
    auto pwet = std::make_unique<juce::AudioParameterFloat>("wet",
        "Wet", 0.0f, 1.0f, 0.5f);
       
    params.push_back(std::move(pPreamp));
    params.push_back(std::move(pDrive));
    params.push_back(std::move(pMix));
    params.push_back(std::move(pOutput));
    params.push_back(std::move(pCutoff));
    params.push_back(std::move(pBitCrusher));
    params.push_back(std::move(pSqrt));
    params.push_back(std::move(pbitDepth));
    params.push_back(std::move(prateDivide));
    params.push_back(std::move(pwet));


    return { params.begin(), params.end() };
}

void DistorColorAudioProcessor::addBit()
{
    if(bitDepth < 32)
        bitDepth += 4;
    DBG(bitDepth);
}

void DistorColorAudioProcessor::removeBit()
{
    if (bitDepth != 4)
        bitDepth -= 4;
    DBG(bitDepth);
}

void DistorColorAudioProcessor::addOut()
{
    if (outputDB < 60.0)
        outputDB += 1.0;
    
}

void DistorColorAudioProcessor::removeOut()
{
    if (outputDB > -60.0)
        outputDB -= 1.0;
    
}

void DistorColorAudioProcessor::bitOn()
{
    if (BitCrusher == false) 
        BitCrusher = true;
    else
        BitCrusher = false;
}

void DistorColorAudioProcessor::lightOn()
{
    if (Sqrt == false)
        Sqrt = true;
    else 
        Sqrt = false;
}

void DistorColorAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "preampID")
    {
        preampDB = newValue;
    }
    if (parameterID == "driveID")
    {
        driveDB = newValue;
    }
    if (parameterID == "mixID")
    {
        mix = static_cast<float>(newValue) / 100.0;
    }
    if (parameterID == "outputID")
    {
        outputDB = (newValue);
    }
    if (parameterID == "cutoffID")
    {
        cutoff = newValue;
        lowPassFilter.setCutoffFrequency(cutoff);
    }
    
    if (parameterID == "sqrt")
    {
        Sqrt = newValue;
    }
    if (parameterID == "bitdepth")
    {
        bitDepth = newValue;
    }
    if (parameterID == "ratedivide")
    {
        rateDivide = static_cast<int>(newValue);
    }
    if (parameterID == "wet")
    {
        wet = (newValue);
    }
    if (parameterID == "bitc")
    {
        BitCrusher = newValue;
    }

}

//==============================================================================
const juce::String DistorColorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistorColorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistorColorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistorColorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistorColorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistorColorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistorColorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistorColorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DistorColorAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistorColorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DistorColorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    oversamplingModule.initProcessing(samplesPerBlock);

    lowPassFilter.reset();
    highPassFilter.reset();

    lastSampleRate = sampleRate;
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();

    // LinkWitzRiley FILTER
    lowPassFilter.prepare(spec);
    lowPassFilter.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    lowPassFilter.setCutoffFrequency(treeState.getRawParameterValue("cutoffID")->load());
    highPassFilter.prepare(spec);
    highPassFilter.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    highPassFilter.setCutoffFrequency(80);
    
    
}

void DistorColorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistorColorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistorColorAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
   

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::AudioBlock<float> upSampledBlock(buffer);
    

    if (BitCrusher) {
            for (int channel = 0; channel < buffer.getNumChannels(); channel++)
            {
                auto* channelData = buffer.getWritePointer(channel);
                auto* cleanData = buffer.getWritePointer(channel);

                for (int i = 0; i < buffer.getNumSamples(); i++)
                {
                    // REDUCE BIT DEPTH :::::
                    float totalQLevels = powf(2, bitDepth); 
                    float val = channelData[i];
                    float remainder = fmodf(val, 1 / totalQLevels);

                    // Quantize ...
                    channelData[i] = val - remainder;

                    if (rateDivide > 1)
                    {
                        if (i % rateDivide != 0)
                            channelData[i] = wet * (channelData[i - i % rateDivide]) + ((1 - wet) * cleanData[i]);
                    }
                }

            }
        
    }
    if (Sqrt) {
        upSampledBlock = oversamplingModule.processSamplesUp(block);
        for (int sample = 0; sample < upSampledBlock.getNumSamples(); sample++)
        {
            for (int channel = 0; channel < upSampledBlock.getNumChannels(); channel++)
            {
                auto* data = upSampledBlock.getChannelPointer(channel);
                const auto input = data[sample] * juce::Decibels::decibelsToGain(preampDB);
                auto softClip = piDivisor * std::atanf(input * juce::Decibels::decibelsToGain(driveDB));
                
                auto blend = (input * (1.0 - mix) + softClip * mix);
                blend *= juce::Decibels::decibelsToGain(outputDB);
                if (std::abs(outputDB) > 1)
                {
                    outputDB *= 1 / std::abs(outputDB);
                }
                data[sample] = blend; //replace what's in data[sample]
            }
        }
        oversamplingModule.processSamplesDown(block);
    }
    else {
        upSampledBlock = oversamplingModule.processSamplesUp(block);
        for (int sample = 0; sample < upSampledBlock.getNumSamples(); sample++)
        {
            for (int channel = 0; channel < upSampledBlock.getNumChannels(); channel++)
            {
                
                auto* data = upSampledBlock.getChannelPointer(channel);
                const auto input = data[sample] * juce::Decibels::decibelsToGain(preampDB);

                auto sqrt = std::sqrt(std::abs((input)*juce::Decibels::decibelsToGain(driveDB)));
                
                auto blend = (input * (1.0 - mix) + sqrt * mix);
                blend *= juce::Decibels::decibelsToGain(outputDB);
                if (std::abs(outputDB) > 1)
                {
                    outputDB *= 1 / std::abs(outputDB);
                }
                data[sample] = blend; //replace what's in data[sample]
            }
        }
        oversamplingModule.processSamplesDown(block);
    }

        lowPassFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
        highPassFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    

        //scope
        waveViewer.setBufferSize(buffer.getNumSamples());
        waveViewer.pushBuffer(buffer);
   
}


//==============================================================================
bool DistorColorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DistorColorAudioProcessor::createEditor()
{
    return new DistorColorAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void DistorColorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DistorColorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistorColorAudioProcessor();
}

juce::AudioProcessorValueTreeState& DistorColorAudioProcessor::get_Apvts()
{
    return treeState;
}
