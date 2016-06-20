#pragma once

template<typename Data>
class SystemProvider
{
    public:

    SystemProvider(std::function<const Data&(int index)>& providerFunction);

    const Data& getData(int index);

    private:

    std::function<const Data&(int index)>& providerFunction;

};

template<typename Data>
const Data& SystemProvider<Data>::getData(int index)
{
    return providerFunction(index);
}
