package com.rusefi;

import com.rusefi.core.EngineState;
import com.rusefi.io.LinkManager;
import com.rusefi.waves.EngineChart;
import com.rusefi.waves.EngineReport;
import com.rusefi.waves.RevolutionLog;
import com.rusefi.waves.EngineChartParser;

import java.util.Arrays;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicReference;

import static com.rusefi.waves.EngineReport.isCloseEnough;

/**
 * @author Andrey Belomutskiy
 *         3/19/14.
 */
public class TestingUtils {
    static boolean isRealHardware;

    static void assertTrue(String msg, boolean b) {
        if (!b)
            fail("Not true: " + msg);
    }

    static void assertCloseEnough(String msg, double current, double ratio, double... expectations) {
        for (double expected : expectations) {
            if (isCloseEnough(fixAngle(expected), current, ratio))
                return;
        }
        if (expectations.length == 1)
            fail(msg + ": Got " + current + " while expecting " + Arrays.toString(expectations) + " ratio=" + Math.abs(1 - expectations[0] / current) + printRange(current, ratio));
        fail(msg + ": Got " + current + " while expecting " + Arrays.toString(expectations) + printRange(current, ratio));
    }

    private static String printRange(double current, double ratio) {
        return " expected range from " + current * (1 - ratio) + " to " + current * (1 + ratio) + " with ratio " + ratio;
    }

    private static double fixAngle(double angle) {
        while (angle >= 720)
            angle -= 720;
        return angle;
    }

    private static void fail(String message) {
        FileLog.MAIN.logLine("FAILURE: " + message);
        IllegalStateException exception = new IllegalStateException(message);
        FileLog.MAIN.log(exception);
        throw exception;
    }

    static void assertTrue(boolean b) {
        if (!b)
            fail("Not true");
    }

    static void assertWave(EngineChart chart, String key, double width, double... expectedAngles) {
        assertWave("", chart, key, width, expectedAngles);
    }

    static void assertWave(String msg, EngineChart chart, String key, double width, double... expectedAngles) {
        assertWave(true, msg, chart, key, width, EngineReport.RATIO, EngineReport.RATIO, expectedAngles);
    }

    static void assertWaveFall(EngineChart chart, String key, double width, double... expectedAngles) {
        assertWaveFall("", chart, key, width, expectedAngles);
    }

    static void assertWaveFall(String msg, EngineChart chart, String key, double width, double... expectedAngles) {
        assertWave(false, msg, chart, key, width, EngineReport.RATIO, EngineReport.RATIO, expectedAngles);
    }

    static void assertWave(boolean rise, String msg, EngineChart chart, String key, double expectedWidth, double angleRatio, double widthRatio, double... expectedAngles) {
        if (isRealHardware)
            return;
        RevolutionLog revolutionLog = chart.getRevolutionsLog();
        if (revolutionLog.getSize() < 2)
            throw new IllegalStateException(msg + " Not many revolutions in " + chart);

        StringBuilder events = chart.get(key);
        assertTrue(msg + " Events not null for " + key, events != null);
        List<EngineReport.UpDown> wr = EngineReport.parse(events.toString());
        assertTrue(msg + " waves for " + key, !wr.isEmpty());
        for (EngineReport.UpDown ud : wr) {
            int eventTime = rise ? ud.upTime : ud.downTime;
            double angleByTime = revolutionLog.getCrankAngleByTime(eventTime);
            assertCloseEnough(msg + " angle for " + key + "@" + eventTime, fixAngle(angleByTime), angleRatio, expectedAngles);

            double actualWidth = ud.getDutyCycle(revolutionLog);
            if (!isCloseEnough(fixAngle(actualWidth), expectedWidth, widthRatio)) {
                System.out.println("f " + revolutionLog.getCrankAngleByTime(ud.downTime));
                System.out.println("t " + revolutionLog.getCrankAngleByTime(ud.upTime));
            }
            assertCloseEnough(msg + " width for " + key, actualWidth, widthRatio, expectedWidth);
        }
    }

    static void assertNull(String msg, Object value) {
        assertTrue(msg, value == null);
    }

    static EngineChart nextChart() {
        getNextWaveChart();
        getNextWaveChart();
        return EngineChartParser.unpackToMap(getNextWaveChart());
    }

    static String getNextWaveChart() {
        IoUtil.sendCommand("reset_wave_chart");
        String result = getEngineChart();
        FileLog.MAIN.logLine("current chart: " + result);
        return result;
    }

    /**
     * This method is blocking and waits for the next wave chart to arrive
     *
     * @return next wave chart in the I/O pipeline
     */
    private static String getEngineChart() {
        final CountDownLatch engineChartLatch = new CountDownLatch(1);

        final AtomicReference<String> result = new AtomicReference<>();

        FileLog.MAIN.logLine("waiting for next chart");
        LinkManager.engineState.replaceStringValueAction(EngineReport.ENGINE_CHART, new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String value) {
                engineChartLatch.countDown();
                result.set(value);
            }
        });
        int timeout = 60;
        long waitStartTime = System.currentTimeMillis();
        IoUtil.wait(engineChartLatch, timeout);
        FileLog.MAIN.logLine("got next chart in " + (System.currentTimeMillis() - waitStartTime) + "ms for engine_type " + AutoTest.currentEngineType);
        LinkManager.engineState.replaceStringValueAction(EngineReport.ENGINE_CHART, (EngineState.ValueCallback<String>) EngineState.ValueCallback.VOID);
        if (result.get() == null)
            throw new IllegalStateException("Chart timeout: " + timeout);
        return result.get();
    }
}
