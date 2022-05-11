/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistorColorAudioProcessorEditor::DistorColorAudioProcessorEditor(DistorColorAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),

    


    //gui elements

    //Knobs
    preampKnob(preampKnobImg, 270,false),
    driveKnob(driveKnobImg, 270, false),
    mixKnob(mixKnobImg, 270, false),
    toneKnob(toneKnobImg, 270, false),
    rateKnob(rateKnobImg, 270, false),
    wetKnob(wetKnobImg, 270, false),

    downButton("downButton", juce::DrawableButton::ButtonStyle::ImageFitted),
    upButton("upButton", juce::DrawableButton::ButtonStyle::ImageFitted),
    rightButton("rightButton", juce::DrawableButton::ButtonStyle::ImageFitted),
    leftButton("leftButton", juce::DrawableButton::ButtonStyle::ImageFitted),

    lightButton("lightButton", juce::DrawableButton::ButtonStyle::ImageFitted),
    bitmeButton("bitmeButton", juce::DrawableButton::ButtonStyle::ImageFitted)
    

    //Buttons draw
    //LButton("LButton", juce::DrawableButton::ButtonStyle::ImageFitted),
    //RButton("RButton", juce::DrawableButton::ButtonStyle::ImageFitted),
    //UpButton("UpButton", juce::DrawableButton::ButtonStyle::ImageFitted),
    //DownButton("DownButton", juce::DrawableButton::ButtonStyle::ImageFitted),

   /* ///Button attach
    LBAttachement(p.get_Apvts(), "outputID", leftButton),
    RBAttachement(p.get_Apvts(), "outputID", rightButton),
    upAttachement(p.get_Apvts(), "bitdepth", upButton),
    downAttachement(p.get_Apvts(), "bitdepth", downButton)*/

{

    addAndMakeVisible(audioProcessor.waveViewer);
    audioProcessor.waveViewer.setOpaque(false);
    audioProcessor.waveViewer.setColours(juce::Colour(0xff95ab57), juce::Colours::black);
    //Layout
    GameBoyBody = juce::ImageCache::getFromMemory(BinaryData::GameBoyBody_png, BinaryData::GameBoyBody_pngSize);
    

    //For knobs

    //Preamp
    addAndMakeVisible(preampKnob);
    preampKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    preampKnob.setRange(0.0, 50.0, 0.0);
    attachments.add(new juce::AudioProcessorValueTreeState::SliderAttachment(p.get_Apvts(), "preampID", preampKnob));
    preampKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    preampKnob.onDragStart = [this]() {
        preampKnob.setMouseCursor(juce::MouseCursor::DraggingHandCursor);
    };
    preampKnob.onDragEnd = [this]() {
        preampKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    };

    //drive
    addAndMakeVisible(driveKnob);
    driveKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveKnob.setRange(0.0, 50.0, 0.0);
    attachments.add(new juce::AudioProcessorValueTreeState::SliderAttachment(p.get_Apvts(), "driveID", driveKnob));
    driveKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    driveKnob.onDragStart = [this]() {
        driveKnob.setMouseCursor(juce::MouseCursor::DraggingHandCursor);
    };
    driveKnob.onDragEnd = [this]() {
        driveKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    };

    //mix
    addAndMakeVisible(mixKnob);
    mixKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mixKnob.setRange(0.0, 1.0, 0.1);
    attachments.add(new juce::AudioProcessorValueTreeState::SliderAttachment(p.get_Apvts(), "mixID", mixKnob));
    mixKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    mixKnob.onDragStart = [this]() {
        mixKnob.setMouseCursor(juce::MouseCursor::DraggingHandCursor);
    };
    mixKnob.onDragEnd = [this]() {
        mixKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    };

    //Tone
    addAndMakeVisible(toneKnob);
    toneKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    toneKnob.setRange(4000.0, 6000.0, 1.0);
    attachments.add(new juce::AudioProcessorValueTreeState::SliderAttachment(p.get_Apvts(), "cutoffID", toneKnob));
    toneKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    toneKnob.onDragStart = [this]() {
        toneKnob.setMouseCursor(juce::MouseCursor::DraggingHandCursor);
    };
    toneKnob.onDragEnd = [this]() {
        toneKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    };

    //Rate
    addAndMakeVisible(rateKnob);
    rateKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateKnob.setRange(1.0, 50.0, 1.0);
    attachments.add(new juce::AudioProcessorValueTreeState::SliderAttachment(p.get_Apvts(), "ratedivide", rateKnob));
    rateKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    rateKnob.onDragStart = [this]() {
        rateKnob.setMouseCursor(juce::MouseCursor::DraggingHandCursor);
    };
    rateKnob.onDragEnd = [this]() {
        rateKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    };

    //wet
    addAndMakeVisible(wetKnob);
    wetKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetKnob.setRange(4000.0, 6000.0, 1.0);
    attachments.add(new juce::AudioProcessorValueTreeState::SliderAttachment(p.get_Apvts(), "wet", wetKnob));
    wetKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    wetKnob.onDragStart = [this]() {
        wetKnob.setMouseCursor(juce::MouseCursor::DraggingHandCursor);
    };
    wetKnob.onDragEnd = [this]() {
        wetKnob.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    };


    //down Button
    addAndMakeVisible(downButton);
    downImg = juce::ImageCache::getFromMemory(BinaryData::DownButton_png, BinaryData::DownButton_pngSize);
    downDraw.setImage(downImg);
    downPressImg = juce::ImageCache::getFromMemory(BinaryData::DownButtonPressed_png, BinaryData::DownButtonPressed_pngSize);
    downPressDraw.setImage(downPressImg);
    downButton.setImages(&downDraw, nullptr, &downPressDraw, nullptr, nullptr);
    downButton.setClickingTogglesState(false);
    downButton.setColour(juce::DrawableButton::backgroundOnColourId, juce::Colours::transparentWhite);
    downButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    downButton.onClick = [this] {
        audioProcessor.removeOut();
    };
    //downAttachement.add(new juce::AudioProcessorValueTreeState::ButtonAttachment(p.get_Apvts(), "outputID", downButton));

    //up Button
    addAndMakeVisible(upButton);
    upImg = juce::ImageCache::getFromMemory(BinaryData::UpButton_png, BinaryData::UpButton_pngSize);
    upDraw.setImage(upImg);
    upPressImg = juce::ImageCache::getFromMemory(BinaryData::UpButtonPressed_png, BinaryData::DownButtonPressed_pngSize);
    upPressDraw.setImage(upPressImg);
    upButton.setImages(&upDraw, nullptr, &upPressDraw, nullptr, nullptr);
    upButton.setClickingTogglesState(false);
    upButton.setColour(juce::DrawableButton::backgroundOnColourId, juce::Colours::transparentWhite);
    upButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    upButton.onClick = [this] {
        audioProcessor.addOut();
    };

    //Right Button
    addAndMakeVisible(rightButton);
    rightImg = juce::ImageCache::getFromMemory(BinaryData::RightButton_png, BinaryData::RightButton_pngSize);
    rightDraw.setImage(rightImg);
    rightPressImg = juce::ImageCache::getFromMemory(BinaryData::RightButtonPressed_png, BinaryData::RightButtonPressed_pngSize);
    rightPressDraw.setImage(rightPressImg);
    rightButton.setImages(&rightDraw, nullptr, &rightPressDraw, nullptr, nullptr);
    rightButton.setClickingTogglesState(false);
    rightButton.setColour(juce::DrawableButton::backgroundOnColourId, juce::Colours::transparentWhite);
    rightButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    rightButton.onClick = [this] {
        audioProcessor.addBit();
    };

    //Left Button
    addAndMakeVisible(leftButton);
    leftImg = juce::ImageCache::getFromMemory(BinaryData::LeftButton_png, BinaryData::LeftButton_pngSize);
    leftDraw.setImage(leftImg);
    leftPressImg = juce::ImageCache::getFromMemory(BinaryData::LeftButtonPressed_png, BinaryData::LeftButtonPressed_pngSize);
    leftPressDraw.setImage(leftPressImg);
    leftButton.setImages(&leftDraw, nullptr, &leftPressDraw, nullptr, nullptr);
    leftButton.setClickingTogglesState(false);
    leftButton.setColour(juce::DrawableButton::backgroundOnColourId, juce::Colours::transparentWhite);
    leftButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    leftButton.onClick = [this] {
        audioProcessor.removeBit();
    };

    //light Button
    addAndMakeVisible(lightButton);
    lightImg = juce::ImageCache::getFromMemory(BinaryData::StartButton_png, BinaryData::StartButton_pngSize);
    lightDraw.setImage(lightImg);
    lightPressImg = juce::ImageCache::getFromMemory(BinaryData::StartButtonPressed_png, BinaryData::StartButtonPressed_pngSize);
    lightPressDraw.setImage(lightPressImg);
    lightButton.setImages(&lightDraw, nullptr, nullptr, nullptr, &lightPressDraw);
    lightButton.setClickingTogglesState(true);
    lightButton.setColour(juce::DrawableButton::backgroundOnColourId, juce::Colours::transparentWhite);
    lightButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    lightButton.onClick = [this] {
       audioProcessor.lightOn();
    };

    //Bitme Button
    addAndMakeVisible(bitmeButton);
    bitmeImg = juce::ImageCache::getFromMemory(BinaryData::StartButton_png, BinaryData::StartButton_pngSize);
    bitmeDraw.setImage(bitmeImg);
    bitmePressImg = juce::ImageCache::getFromMemory(BinaryData::StartButtonPressed_png, BinaryData::StartButtonPressed_pngSize);
    bitmePressDraw.setImage(bitmePressImg);
    bitmeButton.setImages(&bitmeDraw, nullptr, nullptr, nullptr, &bitmePressDraw);
    bitmeButton.setClickingTogglesState(true);
    bitmeButton.setColour(juce::DrawableButton::backgroundOnColourId, juce::Colours::transparentWhite);
    bitmeButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    bitmeButton.onClick = [this] {
        audioProcessor.bitOn();
    };
     
    
    ////Buttons
    //addAndMakeVisible(LButton);
    //LeftButton = juce::ImageCache::getFromMemory(BinaryData::LeftButton_png, BinaryData::LeftButton_pngSize);
    //LBDraw.setImage(LeftButton);

    //HPFImg = juce::ImageCache::getFromMemory(BinaryData::HPFImg_png, BinaryData::HPFImg_pngSize);
    //HPFDraw.setImage(HPFImg);

    //filterButt.setImages(&LPFDraw, nullptr, nullptr, nullptr, &HPFDraw);
    //filterButt.setClickingTogglesState(true);
    //filterButt.setColour(juce::DrawableButton::backgroundOnColourId, juce::Colours::transparentWhite);
    //filterButt.setMouseCursor(juce::MouseCursor::PointingHandCursor);

    setSize(384, 608);
    setResizable(true, true);

}

DistorColorAudioProcessorEditor::~DistorColorAudioProcessorEditor()
{
    attachments.clear();
}

//==============================================================================
void DistorColorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    juce::Rectangle<float> windowArea(0, 0, 384.0, 608.0);
    
    g.drawImage(GameBoyBody, windowArea);

    //Image::rescaled(30, 30, Graphics::highResamplingQuality);
    //preampKnobImg.rescaled(30, 30, enum juce::Graphics::ResamplingQuality highResamplingQuality);
    /*
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);*/
}

void DistorColorAudioProcessorEditor::resized()
{

    audioProcessor.waveViewer.setBounds(103,136,184,112);
    //knob
    preampKnob.setBounds(223, 333, 30, 30);
    driveKnob.setBounds(305, 328, 30, 30);
    mixKnob.setBounds(223, 393, 30, 30);
    toneKnob.setBounds(305, 375, 30, 30);
    rateKnob.setBounds(223, 450, 30, 30);
    wetKnob.setBounds(308, 428, 30, 30);

    //Button

    downButton.setBounds(90,400,30,30);
    upButton.setBounds(90,340,30,30);
    rightButton.setBounds(110, 370, 30, 30);
    leftButton.setBounds(70, 370, 30, 30);

    
    lightButton.setBounds(115, 537, 30, 30);
    bitmeButton.setBounds(186, 537, 30, 30);
}
