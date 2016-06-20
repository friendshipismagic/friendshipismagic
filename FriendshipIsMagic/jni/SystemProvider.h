#pragma once

template<typename Data>
class SystemProvider
{
    public:

    SystemProvider(std::function<const Data&(unsigned int index)>* pfunction)
    {
        providerFunction = pfunction;
    };

    const Data& getData(unsigned int index);

    private:

    std::function<const Data&(unsigned int index)>* providerFunction;

};

template<typename Data>
const Data& SystemProvider<Data>::getData(unsigned int index)
{
    return (*providerFunction)(index);
}

using PositionProvider = SystemProvider<sf::Vector2f> ;
