#include <iostream>
#include "tinyxml2.h"
#include <vector>
#include <string>

using namespace tinyxml2;

class MapVisitor : public XMLVisitor {

	std::vector<const XMLElement*> groups;

	bool VisitEnter(const XMLElement& element, const XMLAttribute* attrs) {
		if(std::string(element.Name()) == "g") { // On a trouvé un groupe
			while(attrs) {
				if(std::string(attrs->Name()) == "id") {
					std::string id = attrs->Value();
					std::cout << "found group id #" << id << std::endl;
					groups.push_back(&element);
					return true;
				}
				attrs = attrs->Next();
			}
			return true;
		}
		else if(std::string(element.Name()) == "use") {
			//groups.push_back()
			while(attrs) {
				if(std::string(attrs->Name()) == "xlink:href") {
					std::string id = attrs->Value();
					std::cout << "using element " << id << std::endl;
					return true;
				}
				attrs = attrs->Next();
			}
			return true;

		}
		else {
			//std::cout << "## found unknown tag : " << element.Name() << std::endl;
			return true;
		}
 	}


};

int main(int argc, char** argv) {

	XMLDocument doc;
	doc.LoadFile("map.svg");

	if(doc.Error()) {
		std::cout << "can't load file" << std::endl;
		return 0;
	}


	auto root = doc.RootElement();

	std::cout << "root is tag " << root->Name() << std::endl;

	MapVisitor visitor;
	doc.Accept(&visitor);


	return 0;
}
