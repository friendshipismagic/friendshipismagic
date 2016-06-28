#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "json.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include "json.h"
#include <assert.h>
#include <exception>

#ifdef ANDROID_BUILD
    #include <SFML/System/NativeActivity.hpp>
    #include <android/native_activity.h>
    #include <android/asset_manager.h>
#endif

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
    Json::Value root;
    Json::Reader reader;

    #ifdef ANDROID_BUILD
        auto file = AAssetManager_open(sf::getNativeActivity()->assetManager, fileName.c_str(), AASSET_MODE_UNKNOWN);
        std::size_t size = AAsset_getLength(file);
        char buffer[size];
        AAsset_read(file,buffer,size);
        AAsset_close(file);

        if (!reader.parse(buffer, root, false))
        {
            throw std::runtime_error("Error while reading" + fileName + "file:\n" + reader.getFormattedErrorMessages());

        }

    #else
        std::ifstream file(fileName.c_str());
        if (!file)
        {
            throw std::runtime_error("ResourceHolder - can't open configuration file " + fileName);
        }

        if( !reader.parse(file, root, false) )
        {
            std::cout << "Error while reading" + fileName + "file:\n" << reader.getFormattedErrorMessages();
            return;
        }
    #endif

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
    if (found == mResourceMap.end())
        throw std::runtime_error("ResourceHolder::get - Failed to get " + id);
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
using SoundBufferHolder = ResourceHolder<sf::SoundBuffer>;
