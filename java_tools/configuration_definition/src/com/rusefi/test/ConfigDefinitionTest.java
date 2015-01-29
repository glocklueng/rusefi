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
        assertEquals("", ConfigDefinition.packComment("", "\t"));
        assertEquals("\t * abc\r\n", ConfigDefinition.packComment("abc", "\t"));
        assertEquals("\t * abc\r\n" +
                "\t * vbn\r\n", ConfigDefinition.packComment("abc\\nvbn", "\t"));
    }

    @Test
    public void testParseLine() {
        assertNull(ConfigField.parse("int"));
        {
            ConfigField cf = ConfigField.parse("int field");
            assertEquals(cf.type, "int");
            assertEquals("Name", cf.name, "field");
        }
        {
            ConfigField cf = ConfigField.parse("int_4 fie4_ld");
            assertEquals(cf.type, "int_4");
            assertEquals(cf.name, "fie4_ld");
        }
        {
            ConfigField cf = ConfigField.parse("int_8 fi_eld;comm_;ts");
            assertEquals(cf.type, "int_8");
            assertEquals(cf.name, "fi_eld");
            assertEquals("Comment", cf.comment, "comm_");
            assertEquals(cf.tsInfo, "ts");
        }
        {
            ConfigField cf = ConfigField.parse("int[3] field");
            assertEquals(cf.type, "int");
            assertEquals(cf.arraySize, 3);
        }
        {
            ConfigField cf = ConfigField.parse("int16_t crankingRpm;This,. value controls what RPM values we consider 'cranking' (any RPM below 'crankingRpm')\\nAnything above 'crankingRpm' would be 'running'");
            assertEquals(cf.name, "crankingRpm");
            assertEquals(cf.arraySize, 1);
            assertEquals(cf.type, "int16_t");
        }
        {
            ConfigField cf = ConfigField.parse("MAP_sensor_config_s map");
            assertEquals(cf.name, "map");
            assertEquals(cf.arraySize, 1);
            assertEquals(cf.type, "MAP_sensor_config_s");
        }
        {
            ConfigField cf = ConfigField.parse("MAP_sensor_config_s map;@see hasMapSensor\\n@see isMapAveragingEnabled");
            assertEquals(cf.name, "map");
            assertEquals(cf.arraySize, 1);
            assertEquals(cf.type, "MAP_sensor_config_s");
            assertEquals(cf.comment, "@see hasMapSensor\\n@see isMapAveragingEnabled");
        }
    }
}
