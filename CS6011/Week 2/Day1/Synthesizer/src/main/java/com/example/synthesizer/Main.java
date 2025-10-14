package com.example.synthesizer;
import javax.sound.sampled.*;

public class Main {



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
        SoundHandler.playSound(mixer.getClip());

        // SQUARE WAVE TEST
//        AudioComponent genSquare = new SquareWave(2);
//        playSound(genSquare.getClip());

        // WHITE NOISE TEST
//        AudioComponent genWhiteNoise = new WhiteNoise();
//        playSound(genWhiteNoise.getClip());
    }
}
