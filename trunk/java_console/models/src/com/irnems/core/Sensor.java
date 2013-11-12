package com.irnems.core;

import eu.hansolo.steelseries.tools.BackgroundColor;

/**
 * @author Andrey Belomutskiy
 *         2/11/13
 */
public enum Sensor {
    RPM("RPM"),
    MAP("MAP"),
    THROTTLE("throttle", "%", 100),
    COOLANT("coolant", "F", 300),
    COOLANT_WIDTH("c w", "", 30),

    INTAKE_AIR("air temp", "F", 150),
    INTAKE_AIR_WIDTH("air w", "", 30),

    TABLE_SPARK("table spark", "ms", -40, 40),
    VREF("VRef", "Volts", 6),
    VREF_WIDTH("VRef w", "", 1),
    MAF("MAF", "Volts", 4),
    DWELL0("Dwell0", "ms", 0, 30, BackgroundColor.BEIGE),
    DWELL1("Dwell1", "ms", 0, 30, BackgroundColor.BEIGE),
    ADVANCE0("Advance0", "dg", -40, 40, BackgroundColor.BROWN),
    ADVANCE1("Advance1", "dg", -40, 40, BackgroundColor.BROWN),
    PERIOD0("Period", "dg", 0, 400),
    DUTY0("Duty0", "%", 0, 100, BackgroundColor.RED),
    DUTY1("Duty1", "%", 0, 100, BackgroundColor.RED),
    TABLE_FUEL("table fuel", "ms", 0, 30),

    IDLE_SWITCH("idle switch"),

    DEFAULT_FUEL("map fuel", "ms", 0, 40),
    T_CHARGE("T Charge", "f", 0, 200),
    AFR("A/F ratio", "", 0, 20),

    CHARTSIZE("CHARTSIZE"),
    CHART_STATUS("CHART_STATUS"),
    ADC_STATUS("ADC_STATUS"),

    INJECTOR_0_STATUS("INJECTOR_0_STATUS"),
    INJECTOR_1_STATUS("INJECTOR_1_STATUS"),
    INJECTOR_2_STATUS("INJECTOR_2_STATUS"),
    INJECTOR_3_STATUS("INJECTOR_3_STATUS"),

    ADC_FAST("ADC_FAST", "b", 4000),
    ADC_FAST_AVG("ADC_FAST_AVG", "b", 4000);

    private final String name;
    private final String units;
    private final double minValue;
    private final double maxValue;
    private final BackgroundColor color;



    Sensor(String name) {
        this(name, "", 255);
    }

    Sensor(String name, String units, double maxValue) {
        this(name, units, 0, maxValue);
    }

    Sensor(String name, String units, double minValue, double maxValue) {
        this(name, units, minValue, maxValue, BackgroundColor.LIGHT_GRAY);
    }

    Sensor(String name, String units, double minValue, double maxValue, BackgroundColor color) {
        this.name = name;
        this.units = units;
        this.minValue = minValue;
        this.maxValue = maxValue;
        this.color = color;
    }

    public String getName() {
        return name;
    }

    public String getUnits() {
        return units;
    }

    public double getMinValue() {
        return minValue;
    }

    public double getMaxValue() {
        return maxValue;
    }

    public BackgroundColor getColor() {
        return color;
    }
}
