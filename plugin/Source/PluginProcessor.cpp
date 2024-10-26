
#include "PluginProcessor.h"
#include "PluginEditor.h"


PluginProcessor::PluginProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
						 .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
						 .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
						 ),
	  mValueTreeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
	mValueTreeState.addParameterListener(paramInput, this);
}


PluginProcessor::~PluginProcessor()
{
	mValueTreeState.removeParameterListener(paramInput, this);
}


const juce::String PluginProcessor::getName() const
{
	return PROJECT_NAME;
}

bool PluginProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}


bool PluginProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}


bool PluginProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}


double PluginProcessor::getTailLengthSeconds() const
{
	return 0.0;
}


int PluginProcessor::getNumPrograms()
{
	return 1;
}


int PluginProcessor::getCurrentProgram()
{
	return 0;
}


void PluginProcessor::setCurrentProgram(int index)
{
}


const juce::String PluginProcessor::getProgramName(int index)
{
	return {};
}


void PluginProcessor::changeProgramName(int index, const juce::String &newName)
{
}


void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
}


void PluginProcessor::releaseResources()
{
}


#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

#if !JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif


void PluginProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto					totalNumInputChannels  = getTotalNumInputChannels();
	auto					totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto *channelData = buffer.getWritePointer(channel);

		// ..do something to the data...
	}
}


bool PluginProcessor::hasEditor() const
{
	return true;
}


juce::AudioProcessorEditor *PluginProcessor::createEditor()
{
	// We create a generic audio processor editor here, so we can work with the processing
	// without concerning about the UI at first!

	return new juce::GenericAudioProcessorEditor(*this);
}


void PluginProcessor::getStateInformation(juce::MemoryBlock &destData)
{
}


void PluginProcessor::setStateInformation(const void *data, int sizeInBytes)
{
}


juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
	std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

	// add parameters here
	auto input = std::make_unique<juce::AudioParameterFloat>(paramInput, inputGainName, inputMinValue, inputMaxValue, inputDefaultValue);

	params.push_back(std::move(input));

	return {params.begin(), params.end()};
}


void PluginProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
}


juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
	return new PluginProcessor();
}
