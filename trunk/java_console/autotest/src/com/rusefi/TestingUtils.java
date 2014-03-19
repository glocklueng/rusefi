package com.rusefi;

import static com.rusefi.waves.WaveReport.isCloseEnough;

/**
 * @author Andrey Belomutskiy
 *         3/19/14.
 */
public class TestingUtils {
    static void assertTrue(String msg, boolean b) {
        if (!b)
            throw new IllegalStateException("Not true: " + msg);
    }

    static void assertCloseEnough(double expected, double current) {
        if (!isCloseEnough(expected, current))
            throw new IllegalStateException("Got " + current + " while expecting " + expected);
    }

    static void assertTrue(boolean b) {
        if (!b)
            throw new IllegalStateException("Not true");
    }
}
