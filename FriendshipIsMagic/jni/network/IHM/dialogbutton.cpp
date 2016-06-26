#include "dialogbutton.hpp"

DialogButton::DialogButton ( sf::Font& font, const sf::String& text, TriggerFun callback ) :
	mText(text, font),
	mCallback(callback)
{
	recompute();
}

DialogButton::DialogButton ( sf::Font& font, TriggerFun callback ) :
	DialogButton(font, "", callback)
{}

void DialogButton::injectEvent ( sf::Event event, const sf::Vector2f& mouse )
{
	auto area = sf::FloatRect(getPosition(), getSize());
	switch(event.type)
	{
		case sf::Event::MouseButtonPressed:
			if (area.contains(mouse))
				mCallback();
			
			break;
			
		//case sf::Event::
		default:
			break;
	}
}

void DialogButton::injectMouse ( const sf::Vector2f& mouse )
{
	auto area = sf::FloatRect(getPosition(), getSize());
	if (area.contains(mouse))
	{
		mBox.setFillColor(sf::Color::Blue);
		mBox.setOutlineThickness(3.f);
		mBox.setOutlineColor(sf::Color::Black);
		mText.setColor(sf::Color::Red);
	}
	else
	{
		mBox.setFillColor(sf::Color::Green);
		mBox.setOutlineThickness(3.f);
		mBox.setOutlineColor(sf::Color::Black);
		mText.setColor(sf::Color::White);
	}
}


void DialogButton::draw ( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform.translate(getPosition());
	target.draw(mBox, states);
	target.draw(mText, states);
}

void DialogButton::setText ( const sf::String& text )
{
	mText.setString(text);
	recompute();
}

void DialogButton::recompute()
{
	mBox.setSize(getSize());
	mBox.setFillColor(sf::Color::Green);
	
	sf::Vector2f t_pos;
	t_pos.x += getSize().x/2 - mText.getLocalBounds().width/2;
	mText.setPosition(t_pos);
}

sf::Vector2f DialogButton::getNeededSize()
{
	auto area = mText.getLocalBounds();
	return {area.width+2*5.f, area.height+2*5.f};
}

sf::Vector2f DialogButton::getPosition() const {return mPosition; }

sf::Vector2f DialogButton::getSize() const { return mSize; }

void DialogButton::setPosition ( const sf::Vector2f& position ) { mPosition = position; recompute(); }

void DialogButton::setSize ( const sf::Vector2f& size ) { mSize = size; recompute();}

