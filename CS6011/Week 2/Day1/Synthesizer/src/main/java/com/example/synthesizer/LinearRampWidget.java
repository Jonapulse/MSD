package com.example.synthesizer;

import javafx.scene.control.Slider;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class LinearRampWidget extends AudioComponentWidgetBase{

    private static final int MIN_START = 10;
    private static final int MAX_START = 2000;
    private static final int MIN_END = MIN_START + 1;
    private static final int MAX_END = 4000;
    private static final int DEFAULT_START = 50;
    private static final int DEFAULT_END = 2000;

    private Slider startSlider_;
    private Slider endSlider_;

    public LinearRampWidget(double x, double y, Pane parent){
        AudioComponent linearRamp = new LinearRamp(DEFAULT_START, DEFAULT_END);
        VBox customPanel = new VBox(10);
        Text title = new Text("Start");
        customPanel.getChildren().add(title);
        Slider newStartSlider = new Slider(MIN_START,MAX_START, DEFAULT_START); //Min/Max Freq Piano
        customPanel.getChildren().add(newStartSlider);
        Text startText = new Text("Start: " + DEFAULT_START);
        customPanel.getChildren().add(startText);
        Slider newEndSlider = new Slider(MIN_END,MAX_END, DEFAULT_END); //Min/Max Freq Piano
        customPanel.getChildren().add(newEndSlider);
        Text endText = new Text("End: " + DEFAULT_START);
        customPanel.getChildren().add(endText);

        super(x, y, "Linear Ramp", linearRamp, parent, customPanel);

        startSlider_ = newStartSlider;
        startSlider_.valueProperty().addListener((observable, oldValue, newValue)->{
            int newVal = newValue.intValue();
            ((LinearRamp)super.audioComponent_).updateClip(newVal, (int)endSlider_.getValue());
            startText.setText("Start: " + newVal);
        });
        endSlider_ = newEndSlider;
        endSlider_.valueProperty().addListener((observable, oldValue, newValue)->{
            int newVal = newValue.intValue();
            ((LinearRamp)super.audioComponent_).updateClip((int)startSlider_.getValue(), newVal);
            endText.setText("End: " + newVal);
        });


    }
}
