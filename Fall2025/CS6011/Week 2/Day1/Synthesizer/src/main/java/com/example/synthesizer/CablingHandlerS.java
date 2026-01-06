package com.example.synthesizer;

public class CablingHandlerS {
    /**
     * Singleton for makeConnection to check for cables to connect to
     */

    public AudioComponentWidgetBase widgetAttemptingCable_ = null;

    private static CablingHandlerS instance_;

    private CablingHandlerS() {}

    public static CablingHandlerS getInstance() {
        if (instance_ == null) {
            instance_ = new CablingHandlerS();
        }
        return instance_;
    }
}
