package com.example.synthesizer;

import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.input.MouseDragEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Circle;
import javafx.scene.text.Text;
import javafx.scene.shape.Line;
import javafx.scene.input.MouseEvent;

public class AudioComponentWidgetBase extends VBox {
    AudioComponent audioComponent_;
    Pane parent_;

    //Cabling
    Line attemptLine_;
    Cable cableIn_;
    Cable cableOut_;

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
        setupWidgetBase(x, y, title, audioComponent, parent, custom, true);
    }
    // Constructor overload used to hide right panel
    AudioComponentWidgetBase(double x, double y, String title, AudioComponent audioComponent, Pane parent, Pane custom, boolean includeRightPanel) {
        setupWidgetBase(x, y, title, audioComponent, parent, custom, includeRightPanel);
    }

    void setupWidgetBase(double x, double y, String title, AudioComponent audioComponent, Pane parent, Pane custom, boolean includeRightPanel)
    {
        this.audioComponent_ = audioComponent;
        this.parent_ = parent;

        this.setPrefWidth(100);
        this.setStyle("-fx-background-color:gray; -fx-padding: 5px; -fx-border-color: blue; -fx-border-width: 2px;");

        Text titleWidget = new Text(title);
        titleWidget.setStyle("-fx-alignment: CENTER;");
        this.getChildren().add(titleWidget);
        HBox contentWidget = new HBox(10);
        this.getChildren().add(contentWidget);
        Circle cableInput = new Circle(10);

        cableInput.addEventHandler(MouseDragEvent.DRAG_DETECTED, (e) -> {
            System.out.println("we start full drag");
            startFullDrag();
            e.consume();
        });
        cableInput.addEventHandler(MouseDragEvent.MOUSE_DRAG_RELEASED, e -> {
            System.out.println("Drag released on target node! Input");
            e.consume();
        });

        contentWidget.getChildren().add(cableInput);
        contentWidget.getChildren().add(custom);
        VBox interactPanel = new VBox(10);
        contentWidget.getChildren().add(interactPanel);

        if(includeRightPanel){
            Button deleteButton = new Button("X");
            deleteButton.setOnAction(e -> {parent_.getChildren().remove(this);});
            interactPanel.getChildren().add(deleteButton);


            Button cableButton = new Button("C");

            interactPanel.getChildren().add(cableButton);
            cableButton.addEventHandler(MouseDragEvent.DRAG_DETECTED, e -> {
                startFullDrag();
                //beginCabling(e);
                attemptLine_ = new Line(e.getSceneX(), e.getSceneY(), e.getSceneX(), e.getSceneY());

                parent_.getChildren().add(attemptLine_);
                e.consume();
            });

            // Handle line update on parent pane
//            parent_.setOnMouseDragOver(e -> {
//                updateCableLine(e);
//                //Let event bubble
//            });
//            parent_.setOnMouseDragReleased(e -> {
//                if(attemptLine_ != null){
//                    cleanupCableLine();
//                }
//            });
        }

        this.setLayoutX(x);
        this.setLayoutY(y);
    }

    public AudioClip getAudioClip() {
        return audioComponent_.getClip();
    }

    public AudioComponent getAudioComponent() { return audioComponent_; }

    private void beginCabling(MouseEvent e) {
        System.out.println("beginCabling");
        attemptLine_ = new Line(e.getSceneX(), e.getSceneY(), e.getSceneX(), e.getSceneY());

        parent_.getChildren().add(attemptLine_);
        e.consume();
    }

    private void updateCableLine(MouseEvent e)
        {
            System.out.println("Hullo? " + (attemptLine_ == null));
            if(attemptLine_ != null)
            {
                System.out.println(e.getSceneX() + " and  " + e.getSceneY());
                attemptLine_.setEndX(e.getSceneX());
                attemptLine_.setEndY(e.getSceneY());
            }
        }

    private void cleanupCableLine()
        {
            parent_.getChildren().remove(attemptLine_);
            attemptLine_ = null;
        }

    private void endCabling(){
        AudioComponentWidgetBase attemptor = CablingHandlerS.getInstance().widgetAttemptingCable_;
        if(attemptor != null){

        }
    }



}
