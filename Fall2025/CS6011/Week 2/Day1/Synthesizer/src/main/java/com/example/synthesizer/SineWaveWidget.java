package com.example.synthesizer;

import javafx.scene.control.Slider;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class SineWaveWidget extends AudioComponentWidgetBase {
    //Frequency range of a standard piano
    //
    private static final int MIN_FREQUENCY = 28;
    private static final int MAX_FREQUENCY = 4185;
    private static final int A4 = 440;
    private Slider frequencySlider_;

    SineWaveWidget(double x, double y, Pane parent) {
        AudioComponent sineWave = new SineWave(A4);
        VBox customPanel = new VBox(10);
        Text title = new Text("Frequency");
        customPanel.getChildren().add(title);
        Slider newFrequencySlider = new Slider(MIN_FREQUENCY,MAX_FREQUENCY, A4); //Min/Max Freq Piano
        customPanel.getChildren().add(newFrequencySlider);
        Text frequencyText = new Text("Frequency: " + A4);
        customPanel.getChildren().add(frequencyText);

        super(x, y, "Sine Wave", sineWave, parent, customPanel);
        frequencySlider_ = newFrequencySlider;
        frequencySlider_.valueProperty().addListener((observable, oldValue, newValue) -> {
            int frequency  = newValue.intValue();
            ((SineWave)super.audioComponent_).updateClip(frequency);
            frequencyText.setText("Frequency: " + frequency);
        });
    }

    @Override
    public AudioClip getAudioClip() {
        ((SineWave)super.audioComponent_).updateClip((int)frequencySlider_.getValue());
        return super.audioComponent_.getClip();
    }
}
