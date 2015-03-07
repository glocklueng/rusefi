package com.rusefi.binaryprotocol.test;

import com.rusefi.binaryprotocol.BinaryProtocolCmd;
import com.rusefi.binaryprotocol.CRC;
import org.junit.Test;

import java.util.Arrays;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

/**
 * (c) Andrey Belomutskiy
 * 3/6/2015
 */
public class CRCTest {
    @Test
    public void testCrc() {
        {
            byte[] a = {'A'};
            assertEquals(0xD3D99E8B, CRC.crc32(a, a.length));
        }
        {
            byte[] a = {'S'};
            assertEquals(0x2060EFC3, CRC.crc32(a, a.length));
        }
    }

    @Test
    public void testPackPacket() {
        byte[] command = {'S'};
        byte[] expected = {0, 1, 0x53, 0x20, 0x60, -17, -61};
        byte[] actual = BinaryProtocolCmd.makePacket(command);
        assertTrue(Arrays.toString(expected) + " vs " + Arrays.toString(actual),
                Arrays.equals(expected, actual));
    }
}
