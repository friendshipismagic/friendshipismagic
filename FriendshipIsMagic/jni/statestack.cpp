#include "statestack.h"
#include <assert.h>

StateStack::StateStack(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{

}

State* StateStack::createState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    return found->second;
}

void StateStack::registerState(States::ID stateID, State* state)
{
    mFactories[stateID] = state;
}

void StateStack::handleEvent(const sf::Event& event)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->handleEvent(event))
            return;
    }
    applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->update(dt))
            return;
    }
    applyPendingChanges();
}

void StateStack::draw()
{
    for (auto itr = mStack.rend() - 1; itr != mStack.rbegin() - 1; --itr)
    {
        (*itr)->draw();
    }
}

void StateStack::applyPendingChanges()
{
    for(PendingChange change: mPendingList)
    {
        switch (change.action)
        {
            case Push:
                mStack.push_back(createState(change.stateID));
                break;
            case Pop:
                mStack.pop_back();
                break;
            case Clear:
                mStack.clear();
                break;
        }
    }
    mPendingList.clear();
}

void StateStack::pushState(States::ID stateID)
{
    struct PendingChange change;
    change.action = Push;
    change.stateID = stateID;
    mPendingList.push_back(change);
}

void StateStack::popState()
{
    if (isEmpty())
        return;
    struct PendingChange change;
    change.action = Pop;
    change.stateID = States::Title;
    mPendingList.push_back(change);
}

void StateStack::clearStates()
{
    struct PendingChange change;
    change.action = Clear;
    change.stateID = States::Title;
    mPendingList.push_back(change);
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

