
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor &p) : AudioProcessorEditor(&p), audioProcessor(p)
{
	setSize(400, 300);
}


PluginEditor::~PluginEditor()
{
}


//==============================================================================
void PluginEditor::paint(Graphics &g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	g.setColour(Colours::white);
	g.setFont(FontOptions(15.0f));
	g.drawFittedText("Hello World!", getLocalBounds(), Justification::centred, 1);
}


void PluginEditor::resized()
{
}
