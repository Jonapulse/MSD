package com.example.synthesizer;

import java.util.ArrayList;

public class Mixer implements AudioComponent {
    //Audio Componenent Implementation
    @Override
    public AudioClip getClip() {
        if(inputs.isEmpty())
            return null;
        AudioClip base = inputs.getFirst().getClip();
        for(int i = 1; i < inputs.size(); i++) {
            AudioClip add = inputs.get(i).getClip();
            for(int j = 0; j < AudioClip.TOTAL_SAMPLES; j++)
                base.setSample(j, base.getSample(j) + add.getSample(j));
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

    private ArrayList<AudioComponent> inputs;

    //Mixer
    //
    public Mixer()
    {
        inputs = new ArrayList<>();
    }
}
