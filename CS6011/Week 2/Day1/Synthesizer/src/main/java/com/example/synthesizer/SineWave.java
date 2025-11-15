package com.example.synthesizer;

import javax.sound.sampled.LineEvent;
import javax.sound.sampled.LineListener;

public class SineWave implements AudioComponent {

    int frequency_ = 440;
    // AudioComponent Implementations
    //
    @Override
    public AudioClip getClip() {
        return clip_;
    }

    @Override
    public boolean hasInput() {
        return false;
    }

    @Override
    public void connectInput(AudioComponent input) {
        assert(false); //This Component does not accept input
    }

    /**
     * re-initializes the audioClip so audioComponents can update while maintaining connections to other audioComponents
     */
    public void updateClip(int frequency) {
        frequency_ = frequency;
        clip_ = new AudioClip();
        for(int i = 0; i < (int)(AudioClip.SAMPLE_RATE * AudioClip.DURATION); i++)
            clip_.setSample(i, (int)(DEFAULT_VOLUME * Math.sin(2 * Math.PI * frequency * i / AudioClip.SAMPLE_RATE)));
    }
    // SineWave
    // NOTES: Are there conventions for how to organize implementations?
    //
    private AudioClip clip_;
    private static final short DEFAULT_VOLUME = 24575; //Short.MAX_VALUE * 0.75f, Some room to increase, more room to decrease

    SineWave(int frequency) {
        updateClip(frequency);
    }
}
