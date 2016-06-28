/*
 * Dijkstra.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRA_DIJKSTRA_H_
#define DIJKSTRA_DIJKSTRA_H_

#include <memory>
#include <vector>
#include "../matrix/matrix.h"

class ASetInterface;
class GraphInterface;
class PiInterface;
class PreviousInterface;
class VertexInterface;

class Dijkstra
{
public:

	Dijkstra(Matrix* matrix);
	virtual ~Dijkstra();
	std::vector<int> dijkstra(int player, int mob);

private:

    std::vector<bool> a;
    std::vector<int> pi;
    std::vector<int> previous;
    Matrix* mMatrix;
};

#endif /* DIJKSTRA_DIJKSTRA_H_ */
