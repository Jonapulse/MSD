package com.example.synthesizer;

import java.util.ArrayList;

public class Mixer implements AudioComponent {

    @Override
    public AudioClip getClip() {
        if(inputs.isEmpty())
            return null;
        AudioClip base = inputs.getFirst().getClip();
        for(int i = 1; i < inputs.size(); i++) {
            AudioClip add = inputs.get(i).getClip();
            for(int j = 0; j < AudioClip.TOTAL_SAMPLES; j++)
                base.setSample(j, (int)Math.clamp(base.getSample(j) + add.getSample(j), AudioClip.MIN_CLIP_VALUE, AudioClip.MAX_CLIP_VALUE));
        }
        return base;
    }

    @Override
    public boolean hasInput() {
        return !inputs.isEmpty();
    }

    @Override
    public void connectInput(AudioComponent input) {
        inputs.add(input);
    }
    @Override
    public void disconnectInput(AudioComponent input) {
        inputs.remove(input);
    }

    private ArrayList<AudioComponent> inputs;

    //Mixer
    //
    public Mixer()
    {
        inputs = new ArrayList<>();
    }
}
