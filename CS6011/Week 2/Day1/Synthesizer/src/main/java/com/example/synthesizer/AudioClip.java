package com.example.synthesizer;

public class AudioClip {
    public static final float DURATION = 2.0f;
    public static final int SAMPLE_RATE = 44100;
    public static final int TOTAL_SAMPLES = (int)(SAMPLE_RATE * DURATION);

    private byte[] clipRawBytes_;

    public AudioClip() {
        clipRawBytes_ = new byte[TOTAL_SAMPLES * 2];
    }

    static int convertBytesToInteger(byte leftByte, byte rightByte) {
        int signByteAsInt = (leftByte >> 7 & 1) == 1 ? 0xffff8000 : 0x0; //Check left-most bit for negative
        int leftByteAsInt = (leftByte & 0x7f) << 8;
        return signByteAsInt | leftByteAsInt | Byte.toUnsignedInt(rightByte);
    }

    //Returns (as an int) the little endian signed short formed by bytes[index + 1], bytes[index]
    //
    public int getSample(int index)
    {
        return(convertBytesToInteger(clipRawBytes_[index * 2 + 1], clipRawBytes_[index * 2]));
    }

    public void setSample(int index, int value)
    {
        clipRawBytes_[index * 2] = (byte)value; //Set right short byte
        clipRawBytes_[index * 2 + 1] = (byte)(value >> 8); //Set left short byte
    }

    public byte[] getData()
    {
        return clipRawBytes_;
    }


}
