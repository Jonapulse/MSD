package com.example.synthesizer;

public class LinearRamp implements AudioComponent {
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

    private AudioClip clip_;
    public LinearRamp(int start, int stop){
        clip_ = new AudioClip();
        int numSamples = (int)(AudioClip.SAMPLE_RATE * AudioClip.DURATION);
        for(int i = 0; i < numSamples; i++) {
            clip_.setSample(i, (int) Math.clamp(((1f * start * (numSamples - i) + stop * i) / numSamples), Short.MIN_VALUE, Short.MAX_VALUE));
        }
    }
}
