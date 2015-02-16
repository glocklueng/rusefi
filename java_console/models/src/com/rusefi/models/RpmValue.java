package com.rusefi.models;

/**
 * @author Andrey Belomutskiy
 *         1/29/13
 */
public class RpmValue {
    private final int value;

    public RpmValue(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public static RpmValue valueOf(String value) {
        return new RpmValue(Integer.valueOf(value));
    }

    @Override
    public String toString() {
        return "Rpm{"
                + value +
                '}';
    }
}
