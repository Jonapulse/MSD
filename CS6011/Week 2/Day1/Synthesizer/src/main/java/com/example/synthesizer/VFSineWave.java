package com.example.synthesizer;

public class VFSineWave implements AudioComponent {

    // AudioComponent Implementations
    //
    @Override
    public AudioClip getClip() {
        return clip_;
    }

    @Override
    public boolean hasInput() {
        return input_ != null;
    }

    @Override
    public void connectInput(AudioComponent input) {
        input_ = input;
        float phase = 0;
        AudioClip inputClip = input_.getClip();
        for(int i = 0; i < (int)(AudioClip.SAMPLE_RATE * AudioClip.DURATION); i++) {
            phase += 2 * Math.PI * inputClip.getSample(i) / AudioClip.SAMPLE_RATE;
            clip_.setSample(i, (int) (AudioClip.MAX_CLIP_VALUE * Math.sin(phase)));
        }
    }

    @Override
    public void disconnectInput(AudioComponent input) {
        input_ = null;
    }

    // VFSineWave
    //
    private AudioClip clip_;
    private AudioComponent input_;
    VFSineWave() {
        clip_ = new AudioClip(); //Stays empty until input connected
    }
}