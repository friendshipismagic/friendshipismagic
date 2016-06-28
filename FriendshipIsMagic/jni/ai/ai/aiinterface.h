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
#include <memory>
using namespace std;

class AiInterface {
public:
	enum Action {left, right, up, down, still};
	AiInterface();
	virtual ~AiInterface();
	void setPath(int mobID, float playerX, float playerY, float mobX, float mobY, Matrix& g);
	Action giveOrder(int mobID,float playerX, float playerY, float mobX, float mobY, Matrix& g);

private:
    std::unique_ptr<MonsterController> mMonsterController;
};

#endif /* JNI_AI_AI_AIINTERFACE_H_ */
