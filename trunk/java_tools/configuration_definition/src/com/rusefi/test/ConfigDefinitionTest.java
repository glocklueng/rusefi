package com.rusefi.test;

import com.rusefi.ConfigDefinition;
import com.rusefi.ConfigField;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

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

    @Test
    public void testParseLine() {
        assertNull(ConfigField.parse("int"));
        {
            ConfigField cf = ConfigField.parse("int;field");
            assertEquals(cf.type, "int");
        }
        {
            ConfigField cf = ConfigField.parse("array int 3;field");
            assertEquals(cf.type, "int");
            assertEquals(cf.arraySize, 3);
        }
    }
}
