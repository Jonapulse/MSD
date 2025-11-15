package com.example.synthesizer;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.ArrayList;

public class SynthesizeApplication extends Application {
    AudioComponentWidgetBase widgetAttemptingCable_ = null;

    @Override
    public void start(Stage stage) throws IOException {
        //In class stuff
        AnchorPane ap = new AnchorPane();

        VBox menu = new VBox(10);
        menu.setStyle("-fx-background-color: #f0f0f0;");
        Button swBtn = new Button("Create Sine Wave");
        //Button vcBtn = new Button("Create Volume Control");
        menu.getChildren().addAll(swBtn/*, vcBtn*/);

        swBtn.setOnAction(e -> makeSineWave(ap));

        ap.getChildren().add(menu);

        Scene scene = new Scene(ap,320, 240);
        stage.setTitle("Synthesizer");
        stage.setScene(scene);
        stage.show();
    }

    private int swcNumber = 0;
    private void makeSineWave(AnchorPane ap) {
        SineWaveWidget sineW = new SineWaveWidget(50, 50, ap);
        ap.getChildren().add(sineW);

        VolumeAdjusterWidget volumeW = new VolumeAdjusterWidget(100, 150, ap);
        ap.getChildren().add(volumeW);
        volumeW.getAudioComponent().connectInput(sineW.getAudioComponent());

        SpeakerWidget speakerW = new SpeakerWidget(200, 50, ap);
        speakerW.getAudioComponent().connectInput(volumeW.getAudioComponent());
        ap.getChildren().add(speakerW);
    }
}
