/*
 * DataManager.cpp
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#include "datacontroller.h"

#include <vector>
#include "monster.h"

using namespace std;

DataController::DataController() {
	// TODO Auto-generated constructor stub

}

DataController::~DataController() {
	// TODO Auto-generated destructor stub
}

vector<Monster*> DataController::getlistOfMonters(){
	return listOfMonsters;
}

vector<PlayerAndStuff*> DataController::getlistOfPlayersStuff(){
	return listOfPlayersStuff;
}
