#pragma once
#include <SFML/System/Vector2.hpp>

class HorizontalLayout
{
	public:
		
		HorizontalLayout (const sf::Vector2f& size);
		
		VerticalMenu (const sf::Vector2f& position, const sf::Vector2f& size);
		
		enum VerticalAlignment {
			TOP,
			MIDDLE,
			BOTTOM,
			FIT
		};
		
		void
		setPosition(sf::Vector2f position);
		
		void
		setSize(const sf::Vector2f& size);
		
		/// @brief set the alignment policy for widgets
		void
		setVerticalAlignment (VerticalAlignment align);
		
		/// @brief append a widget to the bottom of the layout
		void
		append (Widget& widget);
		
		/// @brief remove a widget from the layout
		void
		remove (Widget& widget);
		
		virtual void
		onUpdate(Observable< Updatable >& source);
		
	protected:
		void
		recompute () override;
		
		
	private:
		std::vector<Widget*> mWidgets;
		sf::Vector2f         mPosition;
		sf::Vector2f         mSize;
		VerticalAlignment    mAlignPolicy = FIT;
};
