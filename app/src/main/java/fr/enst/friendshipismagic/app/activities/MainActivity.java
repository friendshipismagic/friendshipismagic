package fr.enst.friendshipismagic.app.activities;

import android.app.Activity;
import android.app.NativeActivity;
import android.os.Bundle;
import org.jsfml.*;
import org.jsfml.graphics.RenderWindow;
import org.jsfml.window.VideoMode;
import org.jsfml.window.event.Event;

public class MainActivity extends Activity {


    @Override
    public void onCreate(Bundle state) {
        super.onCreate(state);
        RenderWindow window = new RenderWindow();//VideoMode.getDesktopMode(), "");

        while (window.isOpen()) {

            for(Event event : window.pollEvents()) {
                if (event.type == Event.Type.CLOSED)
                    window.close();
            }


            window.clear();

            window.display();

        }


        //setContentView(new TextView("It works"));
    }

}
