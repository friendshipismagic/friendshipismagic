#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

class DialogButton : public sf::Drawable
{
	public:
		using TriggerFun = std::function<void()>;
		
		DialogButton(sf::Font& font, TriggerFun callback=[]{});
		DialogButton(sf::Font& font, const sf::String& text, TriggerFun callback=[]{});
	
		void 
		setText (const sf::String& text);
		
		void 
		injectEvent (sf::Event event, const sf::Vector2f& mouse);
		
		void
		injectMouse (const sf::Vector2f& mouse);
		
		sf::Vector2f
		getNeededSize();
		
		
		
		
	protected:
		virtual void draw ( sf::RenderTarget& target, sf::RenderStates states ) const;
		
		void recompute();
		
		void 
		setPosition(const sf::Vector2f& position);
		
		void 
		setSize(const sf::Vector2f& size);
		
		sf::Vector2f
		getPosition() const;
		
		sf::Vector2f
		getSize() const;
		
	private:
		friend class DialogBox;
		
		sf::Text           mText;
		TriggerFun         mCallback;
		sf::RectangleShape mBox;
		sf::Vector2f       mPosition;
		sf::Vector2f       mSize;
		
};
