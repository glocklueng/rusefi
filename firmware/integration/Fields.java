package com.rusefi.config;

/**
 * todo: make this file completely auto-generated
 */

public class Fields {
    public static final Field SENSOR_SNIFFER_FREQUENCY = new Field(@@sensorChartFrequency_offset@@, FieldType.INT);
    public static final Field SENSOR_SNIFFER_MODE = new Field(@@sensorChartMode_offset@@, FieldType.INT, @@sensor_chart_enum@@);
    public static final Field GLOBAL_FUEL_CORRECTION = new Field(@@globalFuelCorrection_offset@@, FieldType.FLOAT);
    public static final Field ENGINE_SNIFFER_SIZE = new Field(@@engineChartSize_offset@@, FieldType.INT);
    public static final Field isDigitalChartEnabled = new Field(@@isEngineChartEnabled_offset@@, FieldType.BIT, 5);
    public static final Field triggerType = new Field(@@trigger_type_offset@@, FieldType.INT, @@trigger_type_enum@@);
    public static final Field algorithm = new Field(@@algorithm_offset@@, FieldType.INT, @@algo_enum@@);
    
    public static final Field gloFuelCorr = new Field(@@globalFuelCorrection_offset@@, FieldType.FLOAT);
    public static final Field gloTriggerOffset = new Field(@@globalTriggerAngleOffset_offset@@, FieldType.FLOAT);
    
    public static final Field triggerInputPins1 = new Field(@@triggerInputPins1_offset@@, FieldType.INT, @@brain_input_pin_enum@@);
    public static final Field triggerInputPins2 = new Field(@@triggerInputPins2_offset@@, FieldType.INT, @@brain_input_pin_enum@@);
    public static final Field triggerInputPins3 = new Field(@@triggerInputPins3_offset@@, FieldType.INT, @@brain_input_pin_enum@@);
    public static final Field injector1 = new Field(@@injectionPins1_offset@@, FieldType.INT, @@brain_pin_enum@@);
}