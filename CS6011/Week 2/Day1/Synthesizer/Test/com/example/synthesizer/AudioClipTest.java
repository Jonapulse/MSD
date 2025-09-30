package com.example.synthesizer;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class AudioClipTest {

    @Test
    void testByteToIntNegative10() {
        byte leftByte = (byte) 0xff;
        byte rightByte = (byte) 0xf6;
        Assertions.assertEquals(-10,AudioClip.convertBytesToInteger(leftByte, rightByte));
    }

    @Test
    void testByteToIntNegative1000() {
        byte leftByte = (byte) 0xfc;
        byte rightByte = (byte) 0x18;
        Assertions.assertEquals(-1000,AudioClip.convertBytesToInteger(leftByte, rightByte));
    }

    @Test
    void testByteToIntZero() {
        byte leftByte = (byte) 0x00;
        byte rightByte = (byte) 0x00;
        Assertions.assertEquals(0,AudioClip.convertBytesToInteger(leftByte, rightByte));
    }

    @Test
    void testByteToIntPositive10() {
        byte leftByte = (byte) 0x00;
        byte rightByte = (byte) 0x0a;
        Assertions.assertEquals(10,AudioClip.convertBytesToInteger(leftByte, rightByte));
    }

    @Test
    void testByteToIntPositive1000() {
        byte leftByte = (byte) 0x03;
        byte rightByte = (byte) 0xe8;
        Assertions.assertEquals(1000,AudioClip.convertBytesToInteger(leftByte, rightByte));
    }

    @Test
    void testByteToIntMaxMins() {
        Assertions.assertEquals(-1,AudioClip.convertBytesToInteger((byte)0xff, (byte)0xff));
        Assertions.assertEquals(32767,AudioClip.convertBytesToInteger((byte)0x7f, (byte)0xff));
        Assertions.assertEquals(-32768,AudioClip.convertBytesToInteger((byte)0x80, (byte)0x00));
    }

    @Test
    void testGetSetSamples(){
        AudioClip test = new AudioClip();
        test.setSample(0, 1000);
        Assertions.assertEquals(1000, test.getSample(0));

        test.setSample(1, -1000);
        Assertions.assertEquals(-1000, test.getSample(1));
    }
}