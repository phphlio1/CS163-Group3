#include "EditDefinition.hpp"
#include "DefinitionFrame.hpp"
#include "Global.hpp"

using namespace Frontend;

EditDefinition::EditDefinition(int n_width, int n_height)
	: Component(n_width, n_height),
	  definition_frame_(nullptr),
	  keyword_(200, 45), definition_(800, 45),
	  done_(80, 45,
			sf::Color::Green,
			sf::Color(255, 255, 255, 160),
			sf::Color(255, 255, 255, 200)),
	  cancel_(80, 45,
			  sf::Color::Transparent,
			  sf::Color(255, 255, 255, 160),
			  sf::Color(255, 255, 255, 200))
{
	font_.loadFromFile("resources/font/JetBrainsMonoNL-Regular.ttf");
	
	done_.setText(font_, "Done", 20, sf::Color::Black);
	done_.setPosition(50, getHeight() - 100);
	done_.setContainer(this);
	
	cancel_.setText(font_, "Cancel", 20, sf::Color::Black);
	cancel_.setPosition(800, getHeight() - 100);
	cancel_.setContainer(this);
	
	keyword_.setFont(font_);
	keyword_.setPosition(50, 50);
	keyword_.setContainer(this);

	definition_.setFont(font_);
	definition_.setPosition(50, 200);
	definition_.setContainer(this);
	
	updateTexture();
}

void EditDefinition::processEvent(const sf::Event &event)
{
	keyword_.processEvent(event);
	definition_.processEvent(event);
	done_.processEvent(event);
	cancel_.processEvent(event);

	if (done_.isPressed())
	{
		definition_frame_->setKeyword(keyword_.getForegroundString());
		internalProcess();
		setVisibility(0);
		definition_frame_->setVisibility(1);
	}
	if (cancel_.isPressed())
	{
		setVisibility(0);
		definition_frame_->setVisibility(1);
	}
	
	updateTexture();
}

void EditDefinition::initialize(const std::string &n_keyword)
{
	keyword_.setForegroundString(n_keyword);
	keyword_.setBackgroundString("");

	definition_.setBackgroundString("");
	
	updateTexture();
}

void EditDefinition::setDefinitionFrame(DefinitionFrame *n_definition_frame)
{
	definition_frame_ = n_definition_frame;
}

std::string EditDefinition::getKeyword() const
{
	return keyword_.getForegroundString();
}

std::string EditDefinition::getDefinition() const
{
	return definition_.getForegroundString();
}

void EditDefinition::updateTexture()
{
	texture_.clear(sf::Color::White);
	
	texture_.draw(keyword_);
	texture_.draw(definition_);
	texture_.draw(done_);
	texture_.draw(cancel_);

	texture_.display();
}

void EditDefinition::internalProcess()
{
	std::string message;
	g_curr_trie->editExistedWordDefi(keyword_.getForegroundString(),
									 definition_.getForegroundString(),
									 message);
	
}
