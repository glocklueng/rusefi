package com.rusefi;

import com.irnems.FileLog;
import com.irnems.core.EngineState;
import com.rusefi.io.CommandQueue;
import com.rusefi.io.InvocationConfirmationListener;
import com.rusefi.io.LinkManager;
import com.rusefi.waves.WaveChart;
import com.rusefi.waves.WaveChartParser;
import com.rusefi.waves.WaveReport;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

/**
 * @author Andrey Belomutskiy
 *         3/19/14.
 */
public class IoUtil {
    static void sendCommand(String command) {
        final CountDownLatch responseLatch = new CountDownLatch(1);
        long time = System.currentTimeMillis();
        CommandQueue.getInstance().write(command, CommandQueue.DEFAULT_TIMEOUT, new InvocationConfirmationListener() {
            @Override
            public void onCommandConfirmation() {
                responseLatch.countDown();
            }
        });
        wait(responseLatch, 20);
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
        return getWaveChart();
    }

    private static String getWaveChart() {
        final CountDownLatch waveChartLatch = new CountDownLatch(1);

        final AtomicReference<String> result = new AtomicReference<String>();

        LinkManager.engineState.registerStringValueAction(WaveReport.WAVE_CHART, new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String value) {
                waveChartLatch.countDown();
                result.set(value);
            }
        });
        wait(waveChartLatch, 5);
        LinkManager.engineState.removeAction(WaveReport.WAVE_CHART);
        return result.get();
    }

    static WaveChart nextChart() {
        return WaveChartParser.unpackToMap(getNextWaveChart());
    }
}
