package fr.enst.friendshipismagic.app;

import java.util.ArrayList;
import java.util.HashMap;
	
import org.jsfml.system.*;
import org.jsfml.window.event.*;

public class StateStack 
{
	public enum Action
    {
		Push,
        Pop,
        Clear,
    };
    
    //======================================[ Attributs ]===========================================//
    
    private ArrayList<State> mStack;
    private ArrayList<PendingChange> mPendingList;
    private HashMap<State.ID, State> mFactories;
    
    //======================================[ Constructeur ]===========================================//
    
    public StateStack()
    {
    	mStack = new ArrayList<State>();
    	mPendingList = new ArrayList<PendingChange>();
    	mFactories = new HashMap<State.ID, State>();
    }
    
    //======================================[ Fonctions ]===========================================//
    
    //Register a state in the dictionnary with the id stateID
    public void registerState(State.ID stateID, State state)
    {
    	mFactories.put(stateID, state);
    }
    
    public void handleEvent(Event event)
    {
    	for (int i = mStack.size() -1; i >= 0; --i)
        {
            if (!(mStack.get(i).handleEvent(event)))
                break;
        }
        applyPendingChanges();
    }
    
    public void update(Time dt)
    {
    	for (int i = mStack.size() -1; i >= 0; --i)
        {
            if (!(mStack.get(i).update(dt)))
                break;
        }
    	applyPendingChanges();
    }
    
    public void render()
    {
    	for (int i = 0; i < mStack.size(); ++i)
        {
    		mStack.get(i).render();
        }
    }
    
    public void pushState(State.ID stateID)
    {
    	PendingChange change = new PendingChange(Action.Push, stateID);
        mPendingList.add(change);
    }
    
    public void popState()
    {
    	 if (isEmpty())
    	    return;
    	 PendingChange change = new PendingChange(Action.Pop, State.ID.Title);
    	 mPendingList.add(change);
    }
    
    public void clearStates()
    {
    	PendingChange change = new PendingChange(Action.Clear, State.ID.Title);
        mPendingList.add(change);
    }
    
    public final boolean isEmpty()
    {
    	return mStack.isEmpty();
    }
    
    //Find the state with the id stateID
    private State createState(State.ID stateID)
    {
    	 State found = mFactories.get(stateID);
    	 //IMPORTANT: state initialisation
    	 found.init();
    	 return found;
    }
     
   //Applies the orders stored in mPendingList
    private void applyPendingChanges()
    {
    	for (PendingChange change: mPendingList)
        {
            switch (change.action)
            {
                case Push:
                    mStack.add(createState(change.stateID));
                    break;
                case Pop:
                    mStack.remove(mStack.size()-1);
                    break;
                case Clear:
                    mStack.clear();
                    break;
            }
        }
        mPendingList.clear();
    }
    
    //Stores the orders given by the states to the stack
    private class PendingChange
    {
		private Action action;
        private State.ID stateID;
        
        public PendingChange(Action act, State.ID id)
        {
        	action = act;
        	stateID = id;
        }
    };

}
