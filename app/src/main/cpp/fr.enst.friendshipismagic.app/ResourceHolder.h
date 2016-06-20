#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include "json.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include "json.h"
#include <assert.h>

template <typename Resource>
class ResourceHolder
{
    public:

        void loadFromFile(std::string filename);
        Resource* get(std::string id);
        void load(std::string id, std::string fileName);

    private:

        std::map<std::string, Resource*> mResourceMap;
};

template<typename Resource>
void ResourceHolder<Resource>::loadFromFile(std::string fileName)
{
    std::ifstream file(fileName.c_str());
    if (!file)
    {
        std::cerr << "Error: can't open file " << fileName << std::endl;
        return;
    }

    Json::Value root;
    Json::Reader reader;
    if( !reader.parse(file, root, false) )
    {
        std::cout << "Error while reading" + fileName + "file:\n" << reader.getFormattedErrorMessages();
        return;
    }

    Json::Value resources = root["resources"];

    for(unsigned int i = 0; i < resources.size(); i++)
    {
        Json::Value o = resources[i];
        Resource* t(new Resource());
        if (!t->loadFromFile(o["filename"].asString()))
            throw std::runtime_error("TextureHolder::load - Failed to load " + fileName);
        mResourceMap[o["name"].asString()] = t;

        std::cout << "Resource load: " + o["filename"].asString() << std::endl;
    }
}

template<typename Resource>
Resource* ResourceHolder<Resource>::get(std::string id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return found->second;
}

template<typename Resource>
void ResourceHolder<Resource>::load(std::string id, std::string filename)
{
    Resource* resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    auto inserted = mResourceMap.insert(std::make_pair(id, resource));
    assert(inserted.second);
}

using TextureHolder = ResourceHolder<sf::Texture>;
using FontHolder = ResourceHolder<sf::Font>;
