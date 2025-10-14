package com.example.synthesizer;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.text.Text;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;

public class SynthesizeApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {

        //todo: All these warnings - if they're causing problems might be the 25 version thing

        //In class stuff
        AnchorPane ap = new AnchorPane();

        VBox menu = new VBox(10);
        menu.setStyle("-fx-background-color: #f0f0f0;");
        Button swBtn = new Button("Create Sine Wave");
        //Button vcBtn = new Button("Create Volume Control");
        menu.getChildren().addAll(swBtn/*, vcBtn*/);

        swBtn.setOnAction(e -> makeSineWave(ap));

        ap.getChildren().add(menu);

        Scene scene = new Scene(ap, 320, 240);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

    private int swcNumber = 0;
    private void makeSineWave(AnchorPane ap) {
        HBox swBox = new HBox();
        swBox.setPrefWidth(100);

        VBox leftPanel = new VBox(10);
        Text title = new Text("Sine Wave");
        leftPanel.getChildren().add(title);
        Slider frequencySlider = new Slider(28,4185, 440); //Min/Max Freq Piano
        leftPanel.getChildren().add(frequencySlider);
        swBox.getChildren().add(leftPanel);

        VBox rightPanel = new VBox(10);
        Button playBtn = new Button("Play");
        rightPanel.getChildren().add(playBtn);
        swBox.getChildren().add(rightPanel);
        ap.getChildren().add(swBox);
        swBox.setLayoutX(200 + swcNumber++ * 100);
        swBox.setLayoutY(200);

        playBtn.setOnAction(e -> playSineWave(frequencySlider));
    }

    private void playSineWave(Slider frequencySlider) {
        // SINE WAVE TEST
        AudioComponent genSine = new SineWave((int)frequencySlider.getValue()); // Your code
        AudioClip genClip = genSine.getClip();
        SoundHandler.playSound(genSine.getClip());
    }
}
