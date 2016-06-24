/*
 * settings-state.cpp
 *
 *  Created on: 23 juin 2016
 *      Author: edwardvergara
 */

#include "settings-state.h"

void sayHello(){
	std::cout << "HEYYYYYYYYYYYYYYYY" << std::endl;
}

void SettingsState::printString(sf::Packet pkt){
	std::string str;
	pkt >>str;
	if (mAgent->getMode() == UDPAgent::Mode::Client){
		std::cout << "Client received string : " << str << std::endl;
		mText.setString("My client agent received : " + str);
	}
	else{
		std::cout << "Server received string : " << str << std::endl;
		mText.setString("my server agent received : " + str);
	}
}
SettingsState::SettingsState(StateStack& mystack, Context& context)
: State(mystack, context)
, mFont(nullptr)
, mTextEffectTime()
, mText()
, mShowText(true)
, mAgent(nullptr){
	// TODO Auto-generated constructor stub
	mFont = context.fonts->get("font");
	mText.setFont(*mFont);
	mText.setCharacterSize(50);
	using std::placeholders::_1;
	mCmd.setCommand(PrintStringCommand::id,std::bind(&SettingsState::printString, this, _1));

	mText.setPosition(250.,300.);
	mText.setColor(sf::Color::Black);
	mText.setString("press any button");
	mBackgroundSprite.setTexture(*getContext().textures->get("menu/settings/background"));
	sf::Vector2f targetSize = getContext().window->getView().getSize();
	mBackgroundSprite.setScale(
		targetSize.x / mBackgroundSprite.getLocalBounds().width,
		targetSize.y / mBackgroundSprite.getLocalBounds().height
	);



}

SettingsState::~SettingsState() {
	// TODO Auto-generated destructor stub
}
void SettingsState::init()
{
    mTextEffectTime = sf::Time::Zero;
    mSettingsSprite.setTexture(*getContext().textures->get("icons/settings"));

}

bool SettingsState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
    	sf::Packet pkt ;
    	switch(event.key.code){
			case sf::Keyboard::C: //CLIENT
				if(mAgent == nullptr){
					mAgent.reset(new UDPAgent(UDPAgent::DEFAULT_PORT+1,"137.194.56.81", UDPAgent::DEFAULT_PORT));
					mAgent->addObserver(this);
					mAgent->start();
					//std::cout << "client launched." << std::endl;
					mText.setString("client launched.");
				}
				break;
			case sf::Keyboard::S: //SERVER
				if(mAgent == nullptr){
					mAgent.reset(new UDPAgent(UDPAgent::DEFAULT_PORT));
					mAgent->addObserver(this);
					mAgent->start();
					//std::cout << "server launched." << std::endl;
					mText.setString("server launched.");
				}
				break;
			case sf::Keyboard::E: //ENVOYER
				//pkt = PrintStringCommand::make("Hey guys!!!");
				//mAgent->send(pkt);
				break;
			case sf::Keyboard::R: //RECEVEIVE
				if(emptyBuf() == false){
					auto pkt = popFrontBuf();
					mCmd.interpret(pkt);
				}
				break;
			case sf::Keyboard::Escape:
				requestStackPop();
				break;
			default:
				break;
    	}

        //requestStackPop();
        //requestStackPush(States::Game);
    }

    if(event.type == sf::Event::Closed)
        requestStackPop();

    return true;
}

bool SettingsState::update(sf::Time dt)
{
    mTextEffectTime += dt;
    if (mTextEffectTime >= sf::seconds(0.7f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }
    return true;
}

void SettingsState::draw()
{
    mContext.window->draw(mBackgroundSprite);
    mContext.window->draw(mSettingsSprite);
    getContext().window->draw(mText);
}

void SettingsState::notify(sf::Packet pkt){
	pushBuf(pkt);
}
