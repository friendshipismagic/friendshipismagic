/*
 * aiinterface.h
 *
 *  Created on: 22 juin 2016
 *      Author: admin
 */

#ifndef JNI_AI_AI_AIINTERFACE_H_
#define JNI_AI_AI_AIINTERFACE_H_

class Monster;
class PlayerAndStuff;
class Matrix;
class MonsterController;

#include <vector>
using namespace std;

class AiInterface {
public:
	enum Action {left, right, up, down, still};
	AiInterface();
	virtual ~AiInterface();
	void setPath(int mobID, float playerX, float playerY, Matrix& g);
	MonsterController* monsterController;
	Action giveOrder(int mobID,float playerX, float playerY, Matrix& g);
};

#endif /* JNI_AI_AI_AIINTERFACE_H_ */
