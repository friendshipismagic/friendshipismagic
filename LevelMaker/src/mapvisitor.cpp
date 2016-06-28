#pragma once

#include <map>
#include <string>

class XMLElement;

Map&  MapVisitor::getMap() {
    return mMap;
}

void MapVisitor::ParsePhysicBox(MapElementData* elt, XMLElement* element) {
    if (std::strcmp(element->Name(),"rect")==0) {
        auto x = element->Attribute("x");
        auto y = element->Attribute("y");
        auto width = element->Attribute("width");
        auto height = element->Attribute("height");

        if(x == nullptr || y == nullptr || width == nullptr || height == nullptr) {
            std::cout << "## ERROR, can't parse rect" << std::endl;
            return;
        }

        elt->addRect(std::atoi(x),std::atoi(y),std::atoi(width),std::atoi(height));
    }
    else if (std::strcmp(element->Name(), "path")==0) {
        std::cout << "found path" << std::endl;
        std::vector<sf::Vector2f> points;

        auto cpath = element->Attribute("d");

        if (cpath == nullptr) {
            std::cout << "## ERROR, can't parse path" << std::endl;
            return;
        }

        std::string path(cpath);

        std::istringstream values (cpath);

        while(!values.eof())
        {
            sf::Vector2f pos;
            char comma;
            values >> pos.x;
            if (values.fail()) {
                values.clear();
                std::string mode;
                values >> mode;
                if (mode =="z") break;
                values >> pos.x >> comma >> pos.y;

            } else values >> comma >> pos.y;

            if (values.fail()) {
                std::cout << "Cant parse path" << std::endl;
                return;
            }

            std::cout << "x:" << pos.x << " y:" << pos.y << std::endl;
            points.push_back(pos);
        }
        elt->addPolygon(points);
    }
}

/*
 *   @brief delete extra svg code and interpret it
 */
void CleanupAddition(MapElementData* elt, XMLElement* element) {
    if(element == nullptr){
        return;
    }
    for(auto next=element; next!=nullptr; ) {

        std::cout << "parsing " << element->Name() << std::endl;

        auto phy = next->Attribute("fim:physics");

        if (phy != nullptr && std::strcmp(phy, "block")==0) {
            ParsePhysicBox(elt, next);
            auto previous = next;
            next=previous->NextSiblingElement();
            previous->Parent()->DeleteChild(previous);
            continue;
        } else {
            if (std::strcmp(next->Name(),"rect")==0) {
                auto x = next->Attribute("x");
                auto y = next->Attribute("y");
                if(x == nullptr || y == nullptr) return;
                sf::Vector2f pos = elt->getPosition();
                elt->setPosition({std::min<float>(pos.x,atof(x)), std::min<float>(pos.y,atof(y))});

            }
        }
        auto child = next->FirstChildElement();
        CleanupAddition(elt,child);
        next=next->NextSiblingElement();
    }
}

void MapVisitor::ExportSVG(const XMLElement* element) {

                XMLDocument document;
                auto decl = document.NewDeclaration("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>");
                auto root = document.NewElement("svg");
                    root->SetAttribute("xmlns:dc","http://purl.org/dc/elements/1.1/");
                    root->SetAttribute("xmlns:cc","http://creativecommons.org/ns#");
                    root->SetAttribute("xmlns:rdf","http://www.w3.org/1999/02/22-rdf-syntax-ns#");
                    root->SetAttribute("xmlns:svg","http://www.w3.org/2000/svg");
                    root->SetAttribute("xmlns", "http://www.w3.org/2000/svg");
                    root->SetAttribute("xmlns:xlink","http://www.w3.org/1999/xlink");
                    root->SetAttribute("xmlns:sodipodi","http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd");
                    root->SetAttribute("xmlns:inkscape","http://www.inkscape.org/namespaces/inkscape");
    //width="210mm"
    //height="297mm"
    //viewBox="0 0 744.09448819 1052.3622047"
    //id="svg2"
                    root->SetAttribute("version","1.1");
    //inkscape:version="0.91 r13725"
    //sodipodi:docname="dessin.svg"
                    document.InsertEndChild(root);
                    // etc

                root->InsertEndChild(deepCopy(&element, &document));

                CleanupAddition(mapElt, root);

                document.SaveFile(std::string("res/" + std::string(id) + ".svg").c_str());


}

bool MapVisitor::VisitEnter(const XMLElement& element, const XMLAttribute* attrs) {
    if(std::string(element.Name()) == "g") { // On a trouv� un groupe

        auto id = element.Attribute("id");
        auto mode = element.Attribute("inkscape:groupmode");
        auto label = element.Attribute("inkscape:label");

        if (id == nullptr) return true;
        if (mode != nullptr && label != nullptr && std::strcmp(mode, "layer") == 0 ) {
            if (mCurrentLayer != nullptr) {
                std::cout << "Layer in layer, can't handle it." << std::endl;
            }

            mCurrentLayer = mMap.addLayer(label);
            std::cout << "Open layer '" << label << "'" << std::endl;
            return true;
        } else {
            if (!id) return true;
            std::cout << "\tfound group id '" << id << "'" << std::endl;
            auto mapElt= new MapElementData(id);
            mCurrentLayer->addElement(mapElt);
            mIds[id] = mapElt;

            ExportSVG(&element, mapElt);
            return false;
        }
    }
    else if(std::string(element.Name()) == "use") {
        //groups.push_back()
        if(mCurrentLayer == nullptr) {
            std::cout << "### ELEMENT OUTSIDE, ignoring" << std::endl;
        }

        parseSvgUse(element);
    } else {
        std::cout << "### ELEMENT OUTSIDE GROUP, ignoring" << std::endl;
    }
    return true;
}

void MapVisitor::ParseSvgUse(const XMLElement& element) {
    auto href = element.Attribute("xlink:href");
    auto id = element.Attribute("id");
    auto x = element.FloatAttribute("x");
    auto y = element.FloatAttribute("y");
    auto xtr = element.Attribute("transform");

    if(href == nullptr) return true;
    if(xtr==nullptr) throw std::runtime_error("No transform in use element");

    auto transforms = split(xtr, ' ');

    for(auto t: transforms) {
        name = t.substr(0, t.find('('));
        std::cout << "Transform type is " << name << std::endl;

        if(name == "translate") {
            auto params = extract(name, '(', ')');
            auto  = transform.find(',');
            x += atof(transform.substr(first_parenthesis+1, comma_pos-first_parenthesis-2).c_str());
            y += atof(transform.substr(comma_pos+1, transform.size()-1-comma_pos).c_str());
        }

        else if (name == "matrix") {

        }

        else {
            throw std::runtime_error("Unsupported transform operation : " + name);
        }
    }

    std::string s_href = href;

    if (href[0] == '#')
        s_href = s_href.substr(1);

    auto ref = mIds[s_href];
    auto element = new MapElementRef(x, y);

    if (ref == nullptr) mIdsMissing.insert({element, href});
    else element->setReferee(ref);

    if(id != nullptr) mIds[id] = element;

    mCurrentLayer->addElement(element);

    std::cout << "\tusing use element " << s_href << std::endl;
    return true;

}

bool MapVisitor::VisitExit(const XMLElement& element) {
    if (std::strcmp(element.Name(), "g") == 0){
        std::cout << "<< quit group " << std::endl;
        auto mode = element.Attribute("inkscape:groupmode");
        auto label = element.Attribute("inkscape:label");

        if (mode != nullptr && label != nullptr) {
            mCurrentLayer = nullptr;

            std::cout << "Close layer '" << label << "'" << std::endl;
        }
    }

    return true;
}
