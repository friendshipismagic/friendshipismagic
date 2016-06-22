/*
 * playerandstuff.h
 *
 *  Created on: 22 juin 2016
 *      Author: admin
 */

#ifndef JNI_AI_AI_PLAYERANDSTUFF_H_
#define JNI_AI_AI_PLAYERANDSTUFF_H_

class Player;
class Stuff;
class AiInterface;

class PlayerAndStuff {
public:
	PlayerAndStuff();
	virtual ~PlayerAndStuff();
	Player* player;
	Stuff* stuff;
	Player getMostPowerfulPlayer(AiInterface ai);
};

#endif /* JNI_AI_AI_PLAYERANDSTUFF_H_ */
