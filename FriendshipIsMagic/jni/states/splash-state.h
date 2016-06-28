#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"

class SplashState : public State
{
private:
	
	sf::View mView;
	
	
	sf::Sprite mBackgroundSprite;
	sf::Sprite mSettingsSprite;
	
	void updateRatio();
	
public:
	
	SplashState(StateStack&, Context&);
	virtual void init();
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
};
