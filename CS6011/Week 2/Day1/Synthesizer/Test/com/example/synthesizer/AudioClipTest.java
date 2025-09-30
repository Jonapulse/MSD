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

}