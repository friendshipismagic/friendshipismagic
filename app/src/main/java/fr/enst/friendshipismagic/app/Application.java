package fr.enst.friendshipismagic.app;

import org.jsfml.graphics.*;
import org.jsfml.system.*;
import org.jsfml.window.event.*;
   
public class Application 
{
	//======================================[ Attributs ]===========================================//
	private StateStack mStateStack;
    private RenderWindow mWindow;
    private Context mContext;
    
    //======================================[ Constructeur ]===========================================//
	public Application(Context context)
	{
		mStateStack = new StateStack();
		mWindow = context.window;
		mContext = context;
		
		registerState();
		
		//We start with the TitleState
	    mStateStack.pushState(State.ID.Title);
	    
	    Event event = new Event(0);
	    mStateStack.handleEvent(event);
	}
	
	//======================================[ Fonctions ]===========================================//
	
	//Register new State here
	public void registerState()
	{
		//Example here:
		/*TitleState tstate = new TitleState(mStateStack, mContext);
		mStateStack.registerState(State.ID.Title, tstate);*/

	}

	
	public void processInput()
	{
	    Event event = mWindow.pollEvent();
	    while(event != null)
	    {
	        mStateStack.handleEvent(event);
	        event = mWindow.pollEvent();
	    }
	}

	public void update(Time dt)
	{
	    mStateStack.update(dt);
	}

	public void render()
	{
		mWindow.clear();
	    mStateStack.render();
	    mWindow.display();
	}
	
	//Main loop, an empty stack triggers the end of the loop, therefore the end of the game
	public void run()
	{
	    Clock clock = new Clock();
	    Time dt = clock.restart();
	    while(!mStateStack.isEmpty())
	    {
	        dt = clock.restart();
	        processInput();
	        update(dt);
	        render();
	    }
	    mWindow.close();
	}
}
