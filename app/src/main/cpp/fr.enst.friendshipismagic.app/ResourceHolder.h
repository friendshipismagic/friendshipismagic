#pragma once

template <typename Resource>
class ResourceHolder
{
    public:

        void loadFromFile(std::string filename);
        Resource& get(std::string id);

    private:
        std::map<std::string, std::unique_ptr<Resource>> mResourceMap;
};

template<typename Resource>
void ResourceHolder<Resource>::loadFromFile(std::string filename)
{
    JSONTokener reader = new JSONTokener(filename);
    JSONObject value = (JSONObject)reader.nextValue();
    JSONArray sounds = value.getJSONArray("ressources");
    for(int i = 0; i < sounds.length(); i++)
    {
        JSONObject o = sounds.getJSONObject(i);
        if (!t->loadFromFile(o.getString("filename")))
            throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
        auto inserted = mResourceMap.insert(std::make_pair(id,std::move(t)));
        assert(inserted.second);

        //std::cout << "Ressource load: " + o.getString("filename") << std::endl;
    }
}

template<typename Resource>
Resource& RessourceManager<Resource>::get(std::string id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *found->second;
}

