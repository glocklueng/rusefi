package com.rusefi;


import com.irnems.FileLog;
import com.irnems.core.EngineState;
import com.irnems.core.Sensor;
import com.irnems.core.SensorCentral;
import com.rusefi.io.CommandQueue;
import com.rusefi.io.InvocationConfirmationListener;
import com.rusefi.io.LinkManager;
import com.rusefi.io.tcp.TcpConnector;
import com.rusefi.waves.RevolutionLog;
import com.rusefi.waves.WaveChart;
import com.rusefi.waves.WaveChartParser;
import com.rusefi.waves.WaveReport;

import java.util.List;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;

import static com.rusefi.waves.WaveReport.isCloseEnough;

/**
 * rusEfi firmware simulator functional test suite
 * <p/>
 * java -cp rusefi_console.jar com.rusefi.AutoTest
 *
 * @author Andrey Belomutskiy
 *         3/5/14
 */
public class AutoTest {
    public static void main(String[] args) throws InterruptedException {
        FileLog.SIMULATOR_CONSOLE.start();
        FileLog.MAIN.start();

        try {
            runTest();
        } finally {
            ExecHelper.destroy();
        }
        FileLog.MAIN.logLine("*******************************************************************************");
        FileLog.MAIN.logLine("************************************  Looks good! *****************************");
        FileLog.MAIN.logLine("*******************************************************************************");
        System.exit(0);
    }

    private static void runTest() throws InterruptedException {
        if (!TcpConnector.getAvailablePorts().isEmpty())
            throw new IllegalStateException("Port already binded on startup?");

        ExecHelper.startSimulator();


//        FileLog.rlog("Waiting for TCP port...");
//        for (int i = 0; i < 180; i++) {
//            if (!TcpConnector.getAvailablePorts().isEmpty())
//                break;
//            Thread.sleep(1000);
//        }
//        if (TcpConnector.getAvailablePorts().isEmpty())
//            throw new IllegalStateException("Did we start it?");
//        /**
//         * If we open a connection just to validate that the process has started, we are getting
//         * weird issues with the second - actual connection
//         */
//        FileLog.rlog("Time for simulator to close the port...");
//        Thread.sleep(3000);
//
//        FileLog.rlog("Got a TCP port! Connecting...");
        LinkManager.start("" + TcpConnector.DEFAULT_PORT);
        /**
         * TCP connector is blocking
         */
        LinkManager.open();

        FileLog.rlog("Let's give it some time to start...");

        final CountDownLatch startup = new CountDownLatch(1);
        SensorCentral.AdcListener listener = new SensorCentral.AdcListener() {
            @Override
            public void onAdcUpdate(SensorCentral model, double value) {
                startup.countDown();
            }
        };
        long waitStart = System.currentTimeMillis();
        SensorCentral.getInstance().addListener(Sensor.RPM, listener);
        startup.await(5, TimeUnit.SECONDS);
        SensorCentral.getInstance().removeListener(Sensor.RPM, listener);
        FileLog.MAIN.logLine("Got first signal in " + (System.currentTimeMillis() - waitStart));

        mainTestBody();
    }

    private static void mainTestBody() throws InterruptedException {
        changeRpm(500);
        changeRpm(2000);


        getWaveChart();
        // we want to wait for the 2nd chart to see same same RPM across the whole chart
        String chartLine = getWaveChart();


        WaveChart chart = WaveChartParser.unpackToMap(chartLine);

        StringBuilder revolutions = chart.get(RevolutionLog.TOP_DEAD_CENTER_MESSAGE);
        if (revolutions.length() == 0)
            throw new IllegalStateException("Empty revolutions in " + chartLine);

        RevolutionLog revolutionLog = RevolutionLog.parseRevolutions(revolutions);
        StringBuilder events = chart.get(WaveChart.INJECTOR_1);
        assertTrue("Events not null", events != null);
        List<WaveReport.UpDown> wr = WaveReport.parse(events.toString());
        int skipped = 0;
        int passed = 0;
        for (WaveReport.UpDown ud : wr) {
            double angleByTime = revolutionLog.getCrankAngleByTime(ud.upTime);
            if (Double.isNaN(angleByTime)) {
                skipped++;
                continue;
            }
            assertCloseEnough(238.75, angleByTime);
            passed++;
        }
        assertTrue(skipped < 2 && passed > 0);
    }

    private static void assertTrue(String msg, boolean b) {
        if (!b)
            throw new IllegalStateException("Not true: " + msg);
    }

    private static void assertCloseEnough(double expected, double current) {
        if (!isCloseEnough(expected, current))
            throw new IllegalStateException("Got " + current + " while expecting " + expected);
    }

    private static void assertTrue(boolean b) {
        if (!b)
            throw new IllegalStateException("Not true");
    }

    private static String getWaveChart() throws InterruptedException {
        final CountDownLatch waveChartLatch = new CountDownLatch(1);

        final AtomicReference<String> result = new AtomicReference<String>();

        LinkManager.engineState.registerStringValueAction(WaveReport.WAVE_CHART, new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String value) {
                waveChartLatch.countDown();
                result.set(value);
            }
        });
        waveChartLatch.await(5, TimeUnit.SECONDS);
        LinkManager.engineState.removeAction(WaveReport.WAVE_CHART);
        return result.get();
    }

    private static void changeRpm(final int rpm) throws InterruptedException {
        final AtomicBoolean responseFlag = new AtomicBoolean();

        CommandQueue.getInstance().write("rpm " + rpm, CommandQueue.DEFAULT_TIMEOUT, new InvocationConfirmationListener() {
            @Override
            public void onCommandConfirmation() {
                synchronized (responseFlag) {
                    responseFlag.set(true);
                    responseFlag.notifyAll();
                }
            }
        });
        waitForResponse(responseFlag, 20);

        final CountDownLatch rpmLatch = new CountDownLatch(1);
        SensorCentral.AdcListener listener = new SensorCentral.AdcListener() {
            @Override
            public void onAdcUpdate(SensorCentral model, double value) {
                double actualRpm = SensorCentral.getInstance().getValue(Sensor.RPM);
                if (isCloseEnough(rpm, actualRpm))
                    rpmLatch.countDown();
            }
        };
        SensorCentral.getInstance().addListener(Sensor.RPM, listener);
        rpmLatch.await(5, TimeUnit.SECONDS);
        SensorCentral.getInstance().removeListener(Sensor.RPM, listener);

        double actualRpm = SensorCentral.getInstance().getValue(Sensor.RPM);

        if (!isCloseEnough(rpm, actualRpm))
            throw new IllegalStateException("rpm change did not happen");
    }

    private static void waitForResponse(AtomicBoolean responseFlag, int timeoutSeconds) throws InterruptedException {
        long end = System.currentTimeMillis() + timeoutSeconds * 1000;

        synchronized (responseFlag) {
            long now = System.currentTimeMillis();
            while (!responseFlag.get() && now < end) {
                responseFlag.wait(end - now);
            }
        }
        if (!responseFlag.get())
            throw new IllegalStateException("No response");
        FileLog.MAIN.logLine("Got response!");
    }
}
