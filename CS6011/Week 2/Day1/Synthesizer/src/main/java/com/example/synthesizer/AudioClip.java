package com.example.synthesizer;

public class AudioClip {
    public static final float DURATION = 2.0f;
    public static final int SAMPLE_RATE = 44100;

    private byte[] clipRawBytes_;

    public AudioClip() {
        clipRawBytes_ = new byte[(int)(SAMPLE_RATE * DURATION)];
    }

    static int convertBytesToInteger(byte leftByte, byte rightByte) {
        int signBytes = (((int)leftByte) << 3 * 8);
        //For -, fill with zeroes up to the 15th bit
        if(signBytes < 0)
            signBytes = signBytes & 0xffff7000;

        //Trim the sign, then shift into the leftByte space
        int leftInt = ((int)leftByte & 0x0000007f) << 8;

        //Return or of all
        return signBytes | leftInt | (int)rightByte;
    }

    //Returns (as an int) a little endian signed short bytes stored at index + 1 and index
    //
    public int getSample(int index)
    {
        return(convertBytesToInteger(clipRawBytes_[index * 2 + 1], clipRawBytes_[index * 2]));
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
