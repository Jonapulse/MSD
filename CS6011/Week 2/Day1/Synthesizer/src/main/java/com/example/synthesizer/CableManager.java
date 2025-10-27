package com.example.synthesizer;

import java.util.ArrayList;

public class CableManager {
    /*
    * Cable Manager
    *  - maintains a list of all Cables
    *  - handles Cable creation, connection, and removal
     */

    //Cable Candidate

    ArrayList<Cable> cables;

    CableManager(){
        cables = new ArrayList<>();
    }

    //Cable Connection can be attempted from a new cable or reusing an
    // previously created one.
     //
    public void StartCableConnection(AudioComponentWidgetBase startAWidget)
    {
        //Set it up there

        //While we're here, set up a listener to draw to the end of the mouse. Fun!
        System.out.println("Starting CableConnection");
    }

    public void CompleteCableConnection(AudioComponentWidgetBase endAWidget)
    {
        //If there's a candidate up, make that connection
        //
        System.out.println("Completing CableConnection");
    }

}
