package com.example.synthesizer;

import javafx.scene.layout.Pane;

public class VFSineWaveWidget extends AudioComponentWidgetBase {
    public VFSineWaveWidget(double x, double y, Pane parent) {
        AudioComponent vfSineWave = new VFSineWave();
        super(x, y, "VFSineWave", vfSineWave, parent, null);
    }
}
