module com.example.synthesizer {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.synthesizer to javafx.fxml;
    exports com.example.synthesizer;
}