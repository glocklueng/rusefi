package com.rusefi;

/**
 * (c) Andrey Belomutskiy
 * 3/6/2015
 */
public class ConfigurationImage {
    private final int size;
    private byte content[];

    public ConfigurationImage(int size) {
        this.size = size;
        content = new byte[size];
    }

    public int getSize() {
        return size;
    }
}
