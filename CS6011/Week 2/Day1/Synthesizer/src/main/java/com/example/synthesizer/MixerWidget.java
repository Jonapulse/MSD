package com.example.synthesizer;

import javafx.scene.layout.Pane;

public class MixerWidget extends AudioComponentWidgetBase{

    MixerWidget(double x, double y, Pane parent) {
        AudioComponent mixer = new Mixer();
        super(x, y, "Mixer", mixer, parent, null);
    }
}
