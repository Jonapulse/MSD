package com.example.synthesizer;

import javafx.scene.control.Slider;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class VolumeAdjusterWidget extends AudioComponentWidgetBase {
    private static final float MAX_VOLUME = 2.0f;
    private static final float DEFAULT_VOLUME = 1.0f;
    private static final float MIN_VOLUME = 0.0f;
    private Slider volumeSlider_;

    VolumeAdjusterWidget(double x, double y, Pane parent) {
        AudioComponent volumeAdj = new VolumeAdjuster(DEFAULT_VOLUME);
        VBox customPanel = new VBox(10);
        Slider newVolumeSlider = new Slider(MIN_VOLUME,MAX_VOLUME, DEFAULT_VOLUME); //Min/Max Freq Piano
        customPanel.getChildren().add(newVolumeSlider);
        Text volumeText = new Text("" + DEFAULT_VOLUME);
        customPanel.getChildren().add(volumeText);

        super(x, y, "Volume Control", volumeAdj, parent, customPanel);
        volumeSlider_ = newVolumeSlider;
        volumeSlider_.valueProperty().addListener((observable, oldValue, newValue) -> {
            float vol  = newValue.floatValue();
            ((VolumeAdjuster)super.audioComponent_).changeVolume(vol);
            volumeText.setText("" + vol);
        });
    }
}
