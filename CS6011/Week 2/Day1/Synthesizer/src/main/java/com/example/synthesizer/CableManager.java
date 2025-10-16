package com.example.synthesizer;

import java.util.ArrayList;

public class CableManager {
    /*
    * Cable Manager
    *  - maintains a list of all Cables
    *  - handles Cable creation, connection, and removal
     */

    ArrayList<Cable> cables;

    CableManager(){
        cables = new ArrayList<>();
    }

    //Clicking a Cable button when no Cable exists will Create one
    //then attempt a connection.
     //
    public void CreateCable()
    {
        AttemptCableConnection();
    }

    //Cable Connection can be attempted from a new cable or reusing an
    // previously created one.
     //
    public void AttemptCableConnection()
    {
        //Set up a mouse click listener.

        //How should we do this? I want to know that a
        //valid object has been clicked. But I also
        //want to know if a click has gone off in the void,
        //in which cae we straight up abort.
    }

}
