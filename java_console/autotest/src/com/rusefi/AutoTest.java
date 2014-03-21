package com.rusefi;


import com.irnems.FileLog;
import com.irnems.core.Sensor;
import com.irnems.core.SensorCentral;
import com.rusefi.io.LinkManager;
import com.rusefi.io.tcp.TcpConnector;
import com.rusefi.waves.RevolutionLog;
import com.rusefi.waves.WaveChart;
import com.rusefi.waves.WaveReport;

import java.util.List;
import java.util.concurrent.*;

import static com.rusefi.IoUtil.*;
import static com.rusefi.TestingUtils.assertCloseEnough;
import static com.rusefi.TestingUtils.assertTrue;
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
        WaveChart chart;
        // todo: interesting changeRpm(100);
        changeRpm(200);

        chart = nextChart();
        float x = 55;
        assertWave(chart, WaveChart.SPARK_1, 0.45, x, x + 180, x + 360, x + 540);


        changeRpm(500);
        changeRpm(2000);


        chart = nextChart();

        assertWave(chart, WaveChart.INJECTOR_1, 0.33, 238.75);
        assertWave(chart, WaveChart.INJECTOR_2, 0.33, 53.04);
        assertWave(chart, WaveChart.INJECTOR_3, 0.33, 417.04);
        assertWave(chart, WaveChart.INJECTOR_4, 0.33, 594.04);

        x = 44;
        assertWave(chart, WaveChart.SPARK_1, 0.41, x, x + 180, x + 360, x + 540);
    }

    private static void assertWave(WaveChart chart, String key, double width, double... expectedAngles) {
        RevolutionLog revolutionLog = chart.getRevolutionsLog();
        if (revolutionLog.keySet().isEmpty())
            throw new IllegalStateException("Empty revolutions in " + chart);

        StringBuilder events = chart.get(key);
        assertTrue("Events not null for " + key, events != null);
        List<WaveReport.UpDown> wr = WaveReport.parse(events.toString());
        assertTrue("waves for " + key, !wr.isEmpty());
        for (WaveReport.UpDown ud : wr) {
            double angleByTime = revolutionLog.getCrankAngleByTime(ud.upTime);
            assertCloseEnough("angle for " + key, angleByTime, expectedAngles);

            assertCloseEnough("width for " + key, ud.getDutyCycle(revolutionLog), width);
        }
    }

    private static void changeRpm(final int rpm) throws InterruptedException {
        sendCommand("rpm " + rpm);

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
        rpmLatch.await(10, TimeUnit.SECONDS);
        SensorCentral.getInstance().removeListener(Sensor.RPM, listener);

        double actualRpm = SensorCentral.getInstance().getValue(Sensor.RPM);

        if (!isCloseEnough(rpm, actualRpm))
            throw new IllegalStateException("rpm change did not happen: " + rpm);
    }

}
