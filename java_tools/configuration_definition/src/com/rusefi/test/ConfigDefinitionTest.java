package com.rusefi.test;

import com.rusefi.ConfigDefinition;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * (c) Andrey Belomutskiy
 * 1/15/15
 */
public class ConfigDefinitionTest {
    @Test
    public void testComment() {
        assertEquals("", ConfigDefinition.packComment(""));
        assertEquals("\t * abc\r\n", ConfigDefinition.packComment("abc"));
        assertEquals("\t * abc\r\n" +
                "\t * vbn\r\n", ConfigDefinition.packComment("abc\\nvbn"));
    }
}
