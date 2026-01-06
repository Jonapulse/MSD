package com.example.synthesizer;

import javax.sound.sampled.*;

public class SoundHandler {

    static void playSound(AudioClip clip) {
        // Get properties from the system about samples rates, etc.
        // AudioSystem is a class from the Java standard library.
        Clip myClip;
        try {
            myClip = AudioSystem.getClip(); // Note, this is different from our AudioClip class.

            // This is the format that we're following, 44.1 KHz mono audio, 16 bits per sample.
            AudioFormat format16 = new AudioFormat( 44100, 16, 1, true, false );

            myClip.open( format16, clip.getData(), 0, clip.getData().length ); // Reads data from our byte array to play it.

            System.out.println( "About to play..." );
            myClip.start(); // Plays it.
            myClip.loop( 2 ); // Plays it 2 more times if desired, so 6 seconds total
        }
        catch (LineUnavailableException e) {
            System.out.println("Aborting playSound - Line Unavailable");
            return;
        }

        myClip.addLineListener(new LineListener() {
            @Override
            public void update(LineEvent event) {
                if (event.getType() == LineEvent.Type.CLOSE) {
                    myClip.close();
                }
            }
        });
    }
}
