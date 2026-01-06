package com.example.synthesizer;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;

/* Cable adds and removes itself in the constructor/disconnectCable
 */
public class Cable extends Line {
    Pane parent_;
    Pane endAnchor_;
    AudioComponent startAudioComponent_;
    AudioComponent endAudioComponent_;

    Cable(Pane parent, Circle start, Circle end, AudioComponent sourceW, AudioComponent targetW) {
        parent_ = parent;
        startAudioComponent_ = sourceW;
        endAudioComponent_ = targetW;
        super(start.getLayoutX(), start.getLayoutY(), end.getLayoutX(), end.getLayoutY());
        parent_.getChildren().add(this);
    }

    public void disconnectCable(){
        parent_.getChildren().remove(this);
        endAudioComponent_.disconnectInput(startAudioComponent_);
    }
}
