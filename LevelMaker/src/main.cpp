#include <iostream>
#include <cmath>
#include <limits>
#include <fstream>
#include "tinyxml2.h"
#include <vector>
#include <string>
#include <string>
#include <SFML/Graphics.hpp>
#include <json.h>
#include <cstdio>

using namespace tinyxml2;

class GroupVisitor {

    public:


};



int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "Usage : LevelMaker <map.svg>" << std::endl;
        return -1;
    }


	XMLDocument doc;
	doc.LoadFile(argv[1]);

	if(doc.Error()) {
		std::cout << "can't load file" << std::endl;
		return -1;
	}


	auto root = doc.RootElement();

    if(root == nullptr || std::strcmp(root->Name(), "svg") != 0) {
	   std::cout << "Only support SVG files" << std::endl;
       return -1;
    }

	MapVisitor visitor;
	doc.Accept(&visitor);

    auto map = visitor.getMap();
    auto jmap = map.getJsonObject();

    std::cout << jmap.toStyledString() <<std::endl;

    Json::StyledWriter writer;
    std::ofstream stream("res/map.json");
    if(stream)
        stream << writer.write(jmap);

    else std::cout << "ERROR WRITING" << std::endl;

	return 0;
}
