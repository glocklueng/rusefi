package com.rusefi;

import com.rusefi.core.EngineState;
import com.rusefi.core.Sensor;
import com.rusefi.core.SensorCentral;
import com.rusefi.io.CommandQueue;
import com.rusefi.io.InvocationConfirmationListener;
import com.rusefi.io.LinkManager;
import com.rusefi.io.tcp.TcpConnector;
import com.rusefi.waves.WaveChart;
import com.rusefi.waves.WaveChartParser;
import com.rusefi.waves.WaveReport;
import jssc.SerialPortList;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

import static com.rusefi.waves.WaveReport.isCloseEnough;

/**
 * @author Andrey Belomutskiy
 *         3/19/14.
 */
public class IoUtil {
    private static final int CMD_TIMEOUT = 20;

    /**
     * Send a command and wait for the confirmation
     *
     * @throws IllegalStateException if command was not confirmed
     */
    static void sendCommand(String command) {
        sendCommand(command, CommandQueue.DEFAULT_TIMEOUT);
    }

    static void sendCommand(String command, int timeoutMs) {
        final CountDownLatch responseLatch = new CountDownLatch(1);
        long time = System.currentTimeMillis();
        if (LinkManager.hasError())
            throw new IllegalStateException("IO error");
        FileLog.MAIN.logLine("Sending command [" + command + "]");
        CommandQueue.getInstance().write(command, timeoutMs, new InvocationConfirmationListener() {
            @Override
            public void onCommandConfirmation() {
                responseLatch.countDown();
            }
        });
        wait(responseLatch, CMD_TIMEOUT);
        if (LinkManager.hasError())
            throw new IllegalStateException("IO error");
        FileLog.MAIN.logLine("Command [" + command + "] executed in " + (System.currentTimeMillis() - time));
    }

    private static void wait(CountDownLatch responseLatch, int seconds) {
        try {
            responseLatch.await(seconds, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            throw new IllegalStateException(e);
        }
    }

    static String getNextWaveChart() {
        // we need to skip TWO because spark could have been scheduled a while ago and happen now
        // todo: improve this logic, compare times
        getWaveChart();
        getWaveChart();
        // we want to wait for the 2nd chart to see same same RPM across the whole chart
        String result = getWaveChart();
        FileLog.MAIN.logLine("current chart: " + result);
        return result;
    }

    /**
     * This method is blocking and waits for the next wave chart to arrive
     *
     * @return next wave chart in the I/O pipeline
     */
    private static String getWaveChart() {
        final CountDownLatch waveChartLatch = new CountDownLatch(1);

        final AtomicReference<String> result = new AtomicReference<>();

        FileLog.MAIN.logLine("waiting for next chart");
        LinkManager.engineState.registerStringValueAction(WaveReport.WAVE_CHART, new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String value) {
                waveChartLatch.countDown();
                result.set(value);
            }
        });
        int timeout = 60;
        long waitStartTime = System.currentTimeMillis();
        wait(waveChartLatch, timeout);
        FileLog.MAIN.logLine("got next chart in " + (System.currentTimeMillis() - waitStartTime) + "ms");
        LinkManager.engineState.removeAction(WaveReport.WAVE_CHART);
        if (result.get() == null)
            throw new IllegalStateException("Chart timeout: " + timeout);
        return result.get();
    }

    static WaveChart nextChart() {
        return WaveChartParser.unpackToMap(getNextWaveChart());
    }

    static void changeRpm(final int rpm) {
        sendCommand("rpm " + rpm);
        long time = System.currentTimeMillis();

        final CountDownLatch rpmLatch = new CountDownLatch(1);
        SensorCentral.SensorListener listener = new SensorCentral.SensorListener() {
            @Override
            public void onSensorUpdate(double value) {
                double actualRpm = SensorCentral.getInstance().getValue(Sensor.RPM);
                if (isCloseEnough(rpm, actualRpm))
                    rpmLatch.countDown();
            }
        };
        SensorCentral.getInstance().addListener(Sensor.RPM, listener);
        try {
            rpmLatch.await(10, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            throw new IllegalStateException(e);
        }
        FileLog.MAIN.logLine("RPM change [" + rpm + "] executed in " + (System.currentTimeMillis() - time));
        SensorCentral.getInstance().removeListener(Sensor.RPM, listener);

        double actualRpm = SensorCentral.getInstance().getValue(Sensor.RPM);

        if (!isCloseEnough(rpm, actualRpm))
            throw new IllegalStateException("rpm change did not happen: " + rpm + ", actual " + actualRpm);
    }

    static void waitForFirstResponse() throws InterruptedException {
        FileLog.MAIN.logLine("Let's give it some time to start...");
        final CountDownLatch startup = new CountDownLatch(1);
        SensorCentral.SensorListener listener = new SensorCentral.SensorListener() {
            @Override
            public void onSensorUpdate(double value) {
                startup.countDown();
            }
        };
        long waitStart = System.currentTimeMillis();
        SensorCentral.getInstance().addListener(Sensor.RPM, listener);
        startup.await(5, TimeUnit.SECONDS);
        SensorCentral.getInstance().removeListener(Sensor.RPM, listener);
        FileLog.MAIN.logLine("Got first signal in " + (System.currentTimeMillis() - waitStart));
    }

    static void launchSimulator() throws InterruptedException {
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
        LinkManager.engineState.registerStringValueAction(EngineState.RUS_EFI_VERSION_TAG, (EngineState.ValueCallback<String>) EngineState.ValueCallback.VOID);
        waitForFirstResponse();
    }

    @SuppressWarnings("UnusedDeclaration")
    static void sleep(int seconds) {
        try {
            Thread.sleep(seconds * 1000L);
        } catch (InterruptedException e) {
            throw new IllegalStateException(e);
        }
    }

    /**
     * @return null if no port located
     */
    static String getDefaultPort() {
        String[] ports = SerialPortList.getPortNames();
        if (ports.length == 0) {
            System.out.println("Port not specified and no ports found");
            return null;
        }
        String port = ports[ports.length - 1];
        System.out.println("Using last of " + ports.length + " port(s)");
        return port;
    }

    static void realHardwareConnect(String port) {
        LinkManager.start(port);
        LinkManager.open();
        LinkManager.engineState.registerStringValueAction(EngineState.RUS_EFI_VERSION_TAG, (EngineState.ValueCallback<String>) EngineState.ValueCallback.VOID);
        LinkManager.engineState.registerStringValueAction(EngineState.OUTPIN_TAG, (EngineState.ValueCallback<String>) EngineState.ValueCallback.VOID);
        LinkManager.engineState.registerStringValueAction(AverageAnglesUtil.KEY, (EngineState.ValueCallback<String>) EngineState.ValueCallback.VOID);
    }
}
