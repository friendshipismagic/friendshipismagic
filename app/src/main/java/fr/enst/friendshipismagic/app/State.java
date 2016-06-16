package fr.enst.friendshipismagic.app;

import org.jsfml.system.*;
import org.jsfml.window.event.*;


public abstract class State 
{
	//New states have to be registered in Application
	public enum ID 
	{ 
		Title
	};
	
	//======================================[ Attributs ]===========================================//

		protected StateStack mStack;
		protected Context mContext;
		
	//======================================[ Constructeur ]===========================================//
	
	public State(StateStack mystack, Context context)
	{
		mStack = mystack;
		mContext = context;
	}
	
	//======================================[ Fonctions ]===========================================//

	//Initialisation is called when the sate is pushed
	public abstract void init();

	public abstract boolean handleEvent(Event event);

	public abstract boolean update(Time dt);

	public abstract void render();

	
	//Push a State on the top of the stack
	protected void requestStackPush(State.ID stateID)
	{
		 mStack.pushState(stateID);
	}
	
	//Pop the state on the top of the stack
	protected void requestStackPop()
	{
		mStack.popState();
	}
	
	//Clear the stack
	protected void requestStateClear()
	{
		mStack.clearStates();
	}
	
	protected final Context getContext() 
	{
		return mContext;
	}
}
