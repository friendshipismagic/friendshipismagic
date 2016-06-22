/*
 * DataManager.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DATAMANAGER_H_
#define DATAMANAGER_H_


#include <vector>

class Monster;
class PlayerAndStuff;

using namespace std;

class DataController {
public:
	vector<Monster*> listOfMonsters;
	//vector<Item> listOfItems;
	vector<PlayerAndStuff*> listOfPlayersStuff;
	DataController();
	virtual ~DataController();
	vector<Monster*> getlistOfMonters();
	vector<PlayerAndStuff*> getlistOfPlayersStuff();

};

#endif /* DATAMANAGER_H_ */
