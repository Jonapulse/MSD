package com.example.synthesizer;

public class SquareWave implements AudioComponent {
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

    @Override
    public void disconnectInput(AudioComponent input) {assert(false);}
    // SquareWave
    // NOTES: Are there conventions for how to organize implementations?
    //
    private AudioClip clip_;
    private static final short DEFAULT_VOLUME = 24575; //Short.MAX_VALUE * 0.75f, Some room to increase, more room to decrease

    SquareWave(int frequency) {
        clip_ = new AudioClip();
        for(int i = 0; i < (int)(AudioClip.SAMPLE_RATE * AudioClip.DURATION); i++)
        {
            int sample;
            if(  ( frequency * i / AudioClip.SAMPLE_RATE) % 1 > 0.5)
                sample = DEFAULT_VOLUME;
            else
                sample = -DEFAULT_VOLUME;
            clip_.setSample(i, sample);
        }
    }
}
