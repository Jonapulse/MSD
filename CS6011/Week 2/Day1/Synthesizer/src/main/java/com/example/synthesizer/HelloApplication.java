package com.example.synthesizer;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.text.Text;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {

        //todo: All these warnings - if they're causing problems might be the 25 version thing

        //In class stuff
        AnchorPane ap = new AnchorPane();

        VBox menu = new VBox(10);
        menu.setStyle("-fx-background-color: #f0f0f0;");
        Button swBtn = new Button("Create Sine Wave");
        Button vcBtn = new Button("Create Volume Control");
        menu.getChildren().addAll(swBtn, vcBtn);

        swBtn.setOnAction(e -> makeSineWave(ap));

        ap.getChildren().add(menu);

        Scene scene = new Scene(ap, 320, 240);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

    private int swcNumber = 0;
    private void makeSineWave(AnchorPane ap) {
        HBox swBox = new HBox(10);
        Text name = new Text("Sine Wave");
        swBox.getChildren().add(name);
        Button swBtn = new Button("Sine Wave");
        swBox.getChildren().add(swBtn);
        ap.getChildren().add(swBtn);
        swBox.setLayoutX(200 + swcNumber++ * 100);
        swBox.setLayoutY(200);
        //How do we get it to show up on the screen?
    }
}
