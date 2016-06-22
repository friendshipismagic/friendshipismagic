/*
 * Player.cpp
 *
 *  Created on: 20 juin 2016
 *      Author: edwardvergara
 */

#include "Player.h"




Player::Player() {
	// TODO Auto-generated constructor stub
	//json test
	std::string fileName = "./data/player.txt";
	std::ifstream file;
	file.open(fileName.c_str());
	if(!file){
		std::cerr << "Error: can't open file";

	}
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( file, root ,true);
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::cout  << "Failed to parse configuration\n"
				   << reader.getFormattedErrorMessages();

	}

	// Get the value of the member of root named 'firstName', return 'noneFirst' if there is no
	// such member.
	mFirstName = root.get("firstName", "noneFirst" ).asString();
	mLastName = root.get("lastName", "noneLast" ).asString();
	mPosX = root["position"].get("posX", 0).asInt();
	mPosY = root["position"].get("posY", 0).asInt();

	/*const Json::Value inventory = root["inventory"];
	for ( int index = 0; index < inventory.size(); ++index )  // Iterates over the sequence elements.
	   {
		mInventory.push_back(inventory[index].asString() );
		mInventoryPrices.push_back(inventory[index].asInt() );

	   }*/
	// ...
	// At application shutdown to make the new configuration document:
	// Since Json::Value has implicit constructor for all value types, it is not
	// necessary to explicitly construct the Json::Value object:
	//root["encoding"] = getCurrentEncoding();
	//root["indent"]["length"] = getCurrentIndentLength();
	//root["indent"]["use_space"] = getCurrentIndentUseSpace();

	//Json::StyledWriter writer;
	// Make a new JSON document for the configuration. Preserve original comments.
	// std::string outputConfig = writer.write( root );

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::printInfo(){
	std::cout << mFirstName << " " << mLastName + "\n";
}

void Player::setFirstName(std::string newName){
	this->mFirstName = newName;
}
void Player::setLastName(std::string newName){
	this->mLastName =  newName;
}
/*
template <typename T>
sf::Packet& operator >>(sf::Packet& packet,  std::vector<T> output)
{
	int size;
	packet >> size;

	int index = output.size();
	output.resize(size+index-1);

	for (int i=0; i< size; ++i)
		packet >> output[index+i];

	return packet;
}

template <typename T>
sf::Packet& operator <<(sf::Packet& packet,  std::vector<T> input)
{

	packet << input.size();
	for (int i=0; i< input.size(); ++i)
		packet << input[index];
	return packet;
}*/

