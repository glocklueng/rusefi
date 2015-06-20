package com.rusefi;

/**
 * (c) Andrey Belomutskiy
 * 3/7/2015
 */
public interface Logger {
    void trace(String msg);

    void info(String msg);

    void error(String msg);
}
