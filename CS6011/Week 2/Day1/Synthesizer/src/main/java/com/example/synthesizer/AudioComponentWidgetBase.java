package com.example.synthesizer;

import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class AudioComponentWidgetBase extends VBox {
    AudioComponent audioComponent_;
    Pane parent_;

    /*
    * The generic structure of AudioComponentWidget is VBox contains...
    * ___________________   Title and another HBox, which contains...
    * |____Title________|   Variable left side and another VBox, which contains...
    * |<Varies | Delete |   Delete button and Cable interface.
    * |  by    |--------|
    * |_Type>__|_Cable__|
    *
    * NOTE: 'parent' is sent in as a reference for self-deletion. Caller must handle
    * display themselves (e.g. by childing this object to parent).
     */
    AudioComponentWidgetBase(double x, double y, String title, AudioComponent audioComponent, Pane parent, Pane custom) {
        this.audioComponent_ = audioComponent;
        this.parent_ = parent;

        this.setPrefWidth(100);
        this.setStyle("-fx-background-color:gray; -fx-padding: 5px; -fx-border-color: blue; -fx-border-width: 2px;");

        Text titleWidget = new Text(title);
        titleWidget.setStyle("-fx-alignment: CENTER;");
        this.getChildren().add(titleWidget);
        HBox contentWidget = new HBox(10);
        this.getChildren().add(contentWidget);
        contentWidget.getChildren().add(custom);
        VBox interactPanel = new VBox(10);
        contentWidget.getChildren().add(interactPanel);
        Button deleteButton = new Button("X");
        deleteButton.setOnAction(e -> {parent_.getChildren().remove(this);});
        interactPanel.getChildren().add(deleteButton);

        //TODO: Implement whatever you want cabling to be.
//        Pane cable = new Pane();
//        interactPanel.getChildren().add(cable);
        Button cableButton = new Button("C");
        interactPanel.getChildren().add(cableButton);
        cableButton.setOnAction((e) -> {
            Cable c = new Cable(this, audioComponent_);
        });

//        //PLACEHOLDER: Temp play button (to be subsumed by Speaker)
//        Button playBtn = new Button("P");
//        playBtn.setOnAction(e -> SoundHandler.playSound(getAudioClip()));
//        interactPanel.getChildren().add(playBtn);

        this.setLayoutX(x);
        this.setLayoutY(y);
    }

    public AudioClip getAudioClip() {
        return audioComponent_.getClip();
    }

    public AudioComponent getAudioComponent() { return audioComponent_; }
}
