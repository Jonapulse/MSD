package com.example.synthesizer;

public class AudioClip {
    public static final float DURATION = 2.0f;
    public static final int SAMPLE_RATE = 44100;

    private byte[] clipRawBytes_;

    public AudioClip() {
        clipRawBytes_ = new byte[(int)(SAMPLE_RATE * DURATION)];
    }

    public int getSample(int index)
    {
        
        return -1;//DUMMY
    }

    public int setSample(int index, int value)
    {

        return -1;//DUMMY
    }

    public byte[] getData()
    {

        return null;//DUMMY
    }


}
