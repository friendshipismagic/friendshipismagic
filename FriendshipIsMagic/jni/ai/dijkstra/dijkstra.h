/*
 * Dijkstra.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRA_DIJKSTRA_H_
#define DIJKSTRA_DIJKSTRA_H_

#include <memory>

class ASetInterface;
class GraphInterface;
class PiInterface;
class PreviousInterface;
class VertexInterface;

class Dijkstra {
public:
	Dijkstra();
	virtual ~Dijkstra();
	static std::unique_ptr<PreviousInterface> dijkstra(GraphInterface& g, VertexInterface& r);

private:
	static std::unique_ptr<PreviousInterface>& dijkstra(GraphInterface& g,VertexInterface& r, ASetInterface& a, PiInterface& pi, std::unique_ptr<PreviousInterface>& previous);

};

#endif /* DIJKSTRA_DIJKSTRA_H_ */
