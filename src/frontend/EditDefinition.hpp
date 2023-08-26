#ifndef EDIT_DEFINITION_HPP
#define EDIT_DEFINITION_HPP

#include <string>

#include "Component.hpp"
#include "TextBox.hpp"
#include "button.hpp"

namespace Frontend
{
	class DefinitionFrame;
	
	class EditDefinition : public Component
	{
	public:
		EditDefinition(int n_width = 950, int n_height = 650);

		virtual void processEvent(const sf::Event &event) override;

		void initialize(const std::string &n_keyword);

		void setDefinitionFrame(DefinitionFrame *n_definition_frame);
		std::string getKeyword() const;
		std::string getDefinition() const;

	protected:
		virtual void updateTexture() override;
		virtual void internalProcess();

	private:
		DefinitionFrame *definition_frame_;
		
		TextBox keyword_, definition_;
		Button done_, cancel_;
		sf::Font font_;
	};
}

#endif
