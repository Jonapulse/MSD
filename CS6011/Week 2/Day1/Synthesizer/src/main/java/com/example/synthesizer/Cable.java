package com.example.synthesizer;
import javafx.scene.Node;
import javafx.scene.input.PickResult;
import javafx.scene.layout.Pane;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

/* On creation or modification, Cable will listen for a valid connection on the next
* click to connect itself to a target, else it will destroy itself.
 */
public class Cable extends Line implements MouseListener {
    Pane startAnchor_;
    Pane endAnchor_;
    AudioComponent sourceAudioComponent_;
    AudioComponent targetAudioComponent_;
    boolean attemptingConnection_ = false;

    Cable(Pane startAnchor, AudioComponent sourceAudioComponent){
        startAnchor_ = startAnchor;
        sourceAudioComponent_ = sourceAudioComponent;
        attemptingConnection_ = true;
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        System.out.println(e.getSource());
//        PickResult pick = (PickResult) e.get();
//        Node clickedNode = (Node)e.getPickResult().getIntersectedNode();
//        System.out.println(e.);
    }

    //Un-used interface methods
    @Override
    public void mousePressed(MouseEvent e) {}
    @Override
    public void mouseReleased(MouseEvent e) {}
    @Override
    public void mouseEntered(MouseEvent e) {}
    @Override
    public void mouseExited(MouseEvent e) {}
}
