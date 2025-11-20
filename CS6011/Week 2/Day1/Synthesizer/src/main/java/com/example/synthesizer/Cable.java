package com.example.synthesizer;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Line;

/* On creation or modification, Cable will listen for a valid connection on the next
* click to connect itself to a target, else it will destroy itself.
 */
public class Cable extends Line {
    Pane startAnchor_;
    Pane endAnchor_;
    AudioComponentWidgetBase sourceAudioComponent_;
    AudioComponentWidgetBase endAudioComponent_;

    Cable(Pane startAnchor, Pane endAnchor, AudioComponentWidgetBase sourceW, AudioComponentWidgetBase targetW) {
        startAnchor_ = startAnchor;
        endAnchor_ = endAnchor;
        sourceAudioComponent_ = sourceW;
        endAudioComponent_ = targetW;

        super(startAnchor.getLayoutX(), startAnchor.getLayoutY(), endAnchor.getLayoutX(), endAnchor.getLayoutY());
        targetW.connectAudioComponent(sourceW.getAudioComponent());

    }


}
