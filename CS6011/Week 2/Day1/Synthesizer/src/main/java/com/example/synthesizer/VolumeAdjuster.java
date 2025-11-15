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
            scaledOriginal.setSample(i, (int)Math.clamp(original.getSample(i) * scale_, AudioClip.MIN_CLIP_VALUE, AudioClip.MAX_CLIP_VALUE));
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

    // VolumeAdjuster
    //
    private AudioComponent input_;
    private double scale_;

    public VolumeAdjuster(double volume) {
        scale_ = volume;
    }

    public void changeVolume(double volume){
        scale_ = volume;
    }
}
