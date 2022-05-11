/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/FilmStripKnob.h"

//==============================================================================
/**
*/
class DistorColorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DistorColorAudioProcessorEditor (DistorColorAudioProcessor&);
    ~DistorColorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistorColorAudioProcessor& audioProcessor;
    //void sliderValueChanged(juce::Slider* slider) override;

    juce::Image GameBoyBody;

    //Preamp Knob
    juce::Image preampKnobImg = juce::ImageCache::getFromMemory(BinaryData::KnobStrip_png, BinaryData::KnobStrip_pngSize);
    FilmStripKnob preampKnob;

    //Drive knob
    juce::Image driveKnobImg = juce::ImageCache::getFromMemory(BinaryData::KnobStrip_png, BinaryData::KnobStrip_pngSize);
    FilmStripKnob driveKnob;

    //Mix knob
    juce::Image mixKnobImg = juce::ImageCache::getFromMemory(BinaryData::KnobStrip_png, BinaryData::KnobStrip_pngSize);
    FilmStripKnob mixKnob;

    //Tone knob
    juce::Image toneKnobImg = juce::ImageCache::getFromMemory(BinaryData::KnobStrip_png, BinaryData::KnobStrip_pngSize);
    FilmStripKnob toneKnob;

    //rate knob
    juce::Image rateKnobImg = juce::ImageCache::getFromMemory(BinaryData::KnobStrip_png, BinaryData::KnobStrip_pngSize);
    FilmStripKnob rateKnob;

    //wet knob
    juce::Image wetKnobImg = juce::ImageCache::getFromMemory(BinaryData::KnobStrip_png, BinaryData::KnobStrip_pngSize);
    FilmStripKnob wetKnob;


    //Down Button
    juce::Image downImg;
    juce::DrawableImage downDraw;
    juce::Image downPressImg;
    juce::DrawableImage downPressDraw;
    juce::DrawableButton downButton;

    //Up Button
    juce::Image upImg;
    juce::DrawableImage upDraw;
    juce::Image upPressImg;
    juce::DrawableImage upPressDraw;
    juce::DrawableButton upButton;

    //Right
    juce::Image rightImg;
    juce::DrawableImage rightDraw;
    juce::Image rightPressImg;
    juce::DrawableImage rightPressDraw;
    juce::DrawableButton rightButton;

    //Left
    juce::Image leftImg;
    juce::DrawableImage leftDraw;
    juce::Image leftPressImg;
    juce::DrawableImage leftPressDraw;
    juce::DrawableButton leftButton;

    //Light
    juce::Image lightImg;
    juce::DrawableImage lightDraw;
    juce::Image lightPressImg;
    juce::DrawableImage lightPressDraw;
    juce::DrawableButton lightButton;

    //Bitme
    juce::Image bitmeImg;
    juce::DrawableImage bitmeDraw;
    juce::Image bitmePressImg;
    juce::DrawableImage bitmePressDraw;
    juce::DrawableButton bitmeButton;

    //Buttons
   /* juce::Image LeftButton;
    juce::DrawableImage LBDraw;
    juce::DrawableButton LButton;

    juce::Image rightButton;
    juce::DrawableImage RBDraw;
    juce::DrawableButton RButton;

    juce::Image UpButtonImg;
    juce::DrawableImage UpDraw;
    juce::DrawableButton UpButton;

    juce::Image DownButtonImg;
    juce::DrawableImage DownDraw;
    juce::DrawableButton DownButton;*/

    //Attachments

    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> attachments;
    /*juce::AudioProcessorValueTreeState::ButtonAttachment LBAttachement;
    juce::AudioProcessorValueTreeState::ButtonAttachment RBAttachement;
    juce::AudioProcessorValueTreeState::ButtonAttachment upAttachement;
    juce::AudioProcessorValueTreeState::ButtonAttachment downAttachement;*/


   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistorColorAudioProcessorEditor)
};
