/*
 * Matrix.h
 *
 *  Created on: 20 juin 2016
 *      Author: admin
 */

#ifndef MATRIX_MATRIX_H_
#define MATRIX_MATRIX_H_


#include <vector>

#include "../dijkstrainterface/graphinterface.h"

using namespace std;

class Matrix : public GraphInterface
{
    public:

        Matrix(vector<char> mCharG, unsigned int x);
        virtual ~Matrix();
        std::vector<VertexInterface*> getAllVertices() override;
        int getWeight(int src, int dst) override;
        std::pair<unsigned int, unsigned int> MatrixToCoordinates(unsigned int S);
        int coordinatesToMatrix(int x, int y);
        VertexInterface* getVertex(int index);
        int getLenghtX();
        int getLenghtT();
        vector<int> getSuccessors(int index);

    private:

        vector<char> mChar;
        vector<VertexInterface*> mVertices;

        unsigned int lengthX;
        unsigned int lengthT;
};

#endif /* MATRIX_MATRIX_H_ */
