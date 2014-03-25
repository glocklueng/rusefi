package com.rusefi;

import com.irnems.FileLog;

import java.util.Arrays;

import static com.rusefi.waves.WaveReport.isCloseEnough;

/**
 * @author Andrey Belomutskiy
 *         3/19/14.
 */
public class TestingUtils {
    static void assertTrue(String msg, boolean b) {
        if (!b)
            fail("Not true: " + msg);
    }

    static void assertCloseEnough(String msg, double current, double... expectations) {
        for (double expected : expectations) {
            if (isCloseEnough(expected, current))
                return;
        }
        fail(msg + ": Got " + current + " while expecting " + Arrays.toString(expectations));
    }

    private static void fail(String message) {
        FileLog.MAIN.logLine("FAILURE: " + message);
        throw new IllegalStateException(message);
    }

    static void assertTrue(boolean b) {
        if (!b)
            fail("Not true");
    }
}
