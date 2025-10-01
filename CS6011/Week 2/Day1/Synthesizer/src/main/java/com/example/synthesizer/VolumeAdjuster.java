package com.example.synthesizer;

public class VolumeAdjuster implements AudioComponent{

    // AudioComponent Implementations
    //
    @Override
    public AudioClip getClip() {
        if(input_ == null)
            return null;

        AudioClip original = input_.getClip();
        AudioClip scaledOriginal = new AudioClip();
        for(int i = 0; i < AudioClip.TOTAL_SAMPLES; i++)
            scaledOriginal.setSample(i, (int)(original.getSample(i) * scale_));
        return scaledOriginal;
    }

    @Override
    public boolean hasInput() {
        return input_ != null;
    }

    @Override
    public void connectInput(AudioComponent input) {
        input_ = input;
    }

    private AudioComponent input_;
    private float scale_;

    // VolumeAdjuster
    //
    public VolumeAdjuster(float volume) {
        scale_ = volume;
    }

    public void changeVolume(float volume){
        scale_ = volume;
    }
}
