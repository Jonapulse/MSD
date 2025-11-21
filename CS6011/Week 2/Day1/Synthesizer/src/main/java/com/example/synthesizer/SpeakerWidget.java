package com.example.synthesizer;

import javafx.scene.control.Button;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.text.Text;

public class SpeakerWidget extends AudioComponentWidgetBase {

    SpeakerWidget(double x, double y, Pane parent){

        AudioComponent mixer = new Mixer();
        HBox customPanel = new HBox(10);
        Text title = new Text("Speaker");
        customPanel.getChildren().add(title);
        Button speakerButton = new Button("Speaker");
        customPanel.getChildren().add(speakerButton);
        super(x, y, "Speaker", mixer, parent, customPanel, false);

        speakerButton.setOnAction(e -> {
            AudioClip playMe = getAudioClip();
            if(playMe != null)
                SoundHandler.playSound(playMe);
        });
    }

    @Override
    public AudioClip getAudioClip() {
        return super.audioComponent_.getClip();
    }
}
