package com.example.synthesizer;
import javax.sound.sampled.*;

public class Main {

    static void playSound(AudioClip clip) {
        // Get properties from the system about samples rates, etc.
        // AudioSystem is a class from the Java standard library.
        Clip c;
        try {
            c = AudioSystem.getClip(); // Note, this is different from our AudioClip class.

            // This is the format that we're following, 44.1 KHz mono audio, 16 bits per sample.
            AudioFormat format16 = new AudioFormat( 44100, 16, 1, true, false );

            c.open( format16, clip.getData(), 0, clip.getData().length ); // Reads data from our byte array to play it.

            System.out.println( "About to play..." );
            c.start(); // Plays it.
            c.loop( 2 ); // Plays it 2 more times if desired, so 6 seconds total
        }
        catch (LineUnavailableException e) {
            System.out.println("Aborting playSound - Line Unavailable");
            return;
        }

        // Makes sure the program doesn't quit before the sound plays.
        while( c.getFramePosition() < AudioClip.TOTAL_SAMPLES || c.isActive() || c.isRunning() ){
            // Do nothing while we wait for the note to play.
        }

        System.out.println( "Done." );
        c.close();
    }

    static void main(String[] args) throws LineUnavailableException {
        // SINE WAVE TEST
//        AudioComponent genSine = new SineWave(440); // Your code
//        playSound(genSine.getClip());

        // VOL ADJUST TEST
//        AudioComponent volAdjust = new VolumeAdjuster(0.1f);
//        volAdjust.connectInput(gen);
//        playSound(volAdjust.getClip());

        //MIXER TEST - A Minor/major
        AudioComponent mixer = new Mixer();
        AudioComponent sine_A = new SineWave(440);
        AudioComponent sine_C = new SineWave(262);
//AudioComponent sine_CSharp = new SineWave(277);
        AudioComponent sine_E = new SineWave(330);
        AudioComponent volDownA= new VolumeAdjuster(0.1f);
        AudioComponent volDownC= new VolumeAdjuster(0.1f);
        AudioComponent volDownE= new VolumeAdjuster(0.1f);
        volDownA.connectInput(sine_A);
        volDownC.connectInput(sine_C);
    //    volDownC.connectInput(sine_CSharp);
        volDownE.connectInput(sine_E);
        mixer.connectInput(volDownA);
        mixer.connectInput(volDownC);
        mixer.connectInput(volDownE);
        playSound(mixer.getClip());

        // SQUARE WAVE TEST
//        AudioComponent genSquare = new SquareWave(2);
//        playSound(genSquare.getClip());

        // WHITE NOISE TEST
//        AudioComponent genWhiteNoise = new WhiteNoise();
//        playSound(genWhiteNoise.getClip());
    }
}
