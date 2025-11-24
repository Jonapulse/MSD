package com.example.synthesizer;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;

public class SynthesizeApplication extends Application {
    AudioComponentWidgetBase widgetAttemptingCable_ = null;

    @Override
    public void start(Stage stage) throws IOException {
        //In class stuff
        AnchorPane ap = new AnchorPane();

        HBox menu = new HBox(10);
        menu.setStyle("-fx-background-color: #f0f0f0;");

        Button swBtn = new Button("Sine Wave");
        swBtn.setOnAction(e -> makeSineWave(ap));
        Button vcBtn = new Button("Volume Control");
        vcBtn.setOnAction(e -> makeVolumeAdjust(ap));
        Button lnRmpBtn = new Button("Linear Ramp");
        lnRmpBtn.setOnAction(e -> makeLinearRamp(ap));
        Button vfSineWaveBtn = new Button("VF Sine Wave");
        vfSineWaveBtn.setOnAction(e -> makeVFSineWave(ap));
        Button whiteNoiseBtn = new Button("White Noise");
        whiteNoiseBtn.setOnAction(e -> makeWhiteNoise(ap));
        Button mixerBtn = new Button("Mixer");
        mixerBtn.setOnAction(e -> makeMixer(ap));

        menu.getChildren().addAll(swBtn, vcBtn, lnRmpBtn, vfSineWaveBtn, whiteNoiseBtn, mixerBtn);

        ap.getChildren().add(menu);

        SpeakerWidget speakerW = new SpeakerWidget(450, 150, ap);
        ap.getChildren().add(speakerW);

        Scene scene = new Scene(ap,640, 480);
        stage.setTitle("Synthesizer");
        stage.setScene(scene);
        stage.show();
    }

    private int swcNumber = 0;
    private final int W_PER_ROW = 4;
    private final int W_ROWS = 3;
    private void makeSineWave(AnchorPane ap) {
        SineWaveWidget sineW = new SineWaveWidget(150 * (swcNumber % W_PER_ROW), 50 * (1 + swcNumber/W_PER_ROW), ap);
        ap.getChildren().add(sineW);
        swcNumber = (swcNumber + 1) % (W_PER_ROW * W_ROWS);
    }

    private void makeVolumeAdjust(AnchorPane ap) {
        VolumeAdjusterWidget volumeW = new VolumeAdjusterWidget(150 * (swcNumber % W_PER_ROW), 50 * (1 + swcNumber/W_PER_ROW), ap);
        ap.getChildren().add(volumeW);

        swcNumber = (swcNumber + 1) % (W_PER_ROW * W_ROWS);
    }

    private void makeLinearRamp(AnchorPane ap) {
        LinearRampWidget lrW = new LinearRampWidget(150 * (swcNumber % W_PER_ROW), 50 * (1 + swcNumber/W_PER_ROW), ap);
        ap.getChildren().add(lrW);
        swcNumber = (swcNumber + 1) % (W_PER_ROW * W_ROWS);
    }

    private void makeVFSineWave(AnchorPane ap) {

        VFSineWaveWidget vfSineWaveW = new VFSineWaveWidget(150 * (swcNumber % W_PER_ROW), 50 * (1 + swcNumber/W_PER_ROW), ap);
        ap.getChildren().add(vfSineWaveW);
        swcNumber = (swcNumber + 1) % (W_PER_ROW * W_ROWS);
    }

    private void makeWhiteNoise(AnchorPane ap) {

        swcNumber = (swcNumber + 1) % (W_PER_ROW * W_ROWS);
    }

    private void makeMixer(AnchorPane ap) {
        MixerWidget mixerW = new MixerWidget(150 * (swcNumber % W_PER_ROW), 50 * (1 + swcNumber/W_PER_ROW), ap);
        ap.getChildren().add(mixerW);
        swcNumber = (swcNumber + 1) % (W_PER_ROW * W_ROWS);
    }
}
