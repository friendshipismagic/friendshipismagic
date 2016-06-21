#pragma once
#include "State.h"
#include <SFML/System.hpp>
#include <map>
#include <vector>

class StateStack
{
    public:
        enum Action
        {
            Push,
            Pop,
            Clear,
        };

    public:
        StateStack(State::Context context);

        void registerState(States::ID stateID, State*);

        void update(sf::Time dt);
        void draw();
        void handleEvent(const sf::Event& event);
        void pushState(States::ID stateID);
        void popState();
        void clearStates();
        bool isEmpty() const;

    private:
        State* createState(States::ID stateID);
        void applyPendingChanges();

    private:
        struct PendingChange
        {
            Action action;
            States::ID stateID;
        };

    private:
        std::vector<State*> mStack;
        std::vector<PendingChange> mPendingList;
        State::Context mContext;
        std::map<States::ID, State*> mFactories;
};


