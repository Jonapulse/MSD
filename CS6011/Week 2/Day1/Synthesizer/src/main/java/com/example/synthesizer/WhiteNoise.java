package com.example.synthesizer;
import java.util.Random;

public class WhiteNoise implements AudioComponent {
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

    // WhiteNoise
    //
    private AudioClip clip_;
    private static final short DEFAULT_VOLUME = 24575; //Short.MAX_VALUE * 0.75f, Some room to increase, more room to decrease

    WhiteNoise() {
        clip_ = new AudioClip();
        Random rand = new Random();
        for(int i = 0; i < (int)(AudioClip.SAMPLE_RATE * AudioClip.DURATION); i++)
        {
            double mult = rand.nextDouble();
            if(rand.nextDouble() < 0.5)
                mult *= -1;
            clip_.setSample(i, (int)(mult * DEFAULT_VOLUME));
        }
    }
}
