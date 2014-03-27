package com.rusefi;


import com.irnems.FileLog;
import com.rusefi.waves.WaveChart;

import static com.rusefi.IoUtil.nextChart;
import static com.rusefi.IoUtil.sendCommand;

/**
 * rusEfi firmware simulator functional test suite
 * <p/>
 * java -cp rusefi_console.jar com.rusefi.AutoTest
 *
 * @author Andrey Belomutskiy
 *         3/5/14
 */
public class AutoTest {
    private static void mainTestBody() {
        testFordAspire();

        sendCommand("set_engine_type 2");
        testDodgeNeon();

        sendCommand("set_engine_type 7");
        testFord6();

        sendCommand("set_engine_type 4");
        testFordFiesta();
    }

    private static void testDodgeNeon() {
        WaveChart chart;
        IoUtil.changeRpm(2000);
        chart = nextChart();

        String msg = "Neon";

        TestingUtils.assertWave(msg, chart, WaveChart.INJECTOR_4, 0.1, 51);
        TestingUtils.assertWave(msg, chart, WaveChart.INJECTOR_2, 0.1, 231);
        TestingUtils.assertWave(msg, chart, WaveChart.INJECTOR_1, 0.1, 411);
        TestingUtils.assertWave(msg, chart, WaveChart.INJECTOR_3, 0.1, 591);

        TestingUtils.assertWave(msg, chart, WaveChart.SPARK_4, 0.13333, 6);
        TestingUtils.assertWave(chart, WaveChart.SPARK_2, 0.13333, 186);
        TestingUtils.assertWave(chart, WaveChart.SPARK_1, 0.13333, 366);
        TestingUtils.assertWave(chart, WaveChart.SPARK_3, 0.13333, 546);
    }

    private static void testFordFiesta() {
//        WaveChart chart;
//        changeRpm(2000);
//        chart = nextChart();
    }

    private static void testFord6() {
        WaveChart chart;
        IoUtil.changeRpm(2000);
        chart = nextChart();

        int x = 10;
        TestingUtils.assertWave("ford 6", chart, WaveChart.SPARK_1, 0.01666, x, x + 120, x + 240, x + 360, x + 480, x + 600);

    }

    private static void testFordAspire() {
        WaveChart chart;
        // todo: interesting changeRpm(100);
        sendCommand("set_cranking_rpm 500");
        IoUtil.changeRpm(200);

        chart = nextChart();
        float x = 55;
        TestingUtils.assertWave("aspire", chart, WaveChart.SPARK_1, 0.18, x, x + 180, x + 360, x + 540);

        sendCommand("set_cranking_timing_angle 40");
        chart = nextChart();
        x = 64;
        TestingUtils.assertWave("aspire", chart, WaveChart.SPARK_1, 0.18, x, x + 180, x + 360, x + 540);
        sendCommand("set_cranking_timing_angle -149");

        sendCommand("set_cranking_charge_angle 40");
        chart = nextChart();
        x = 80;
        TestingUtils.assertWave("aspire", chart, WaveChart.SPARK_1, 40.0 / 360, x, x + 180, x + 360, x + 540);
        sendCommand("set_cranking_charge_angle 65");

        IoUtil.changeRpm(600);
        chart = nextChart();
        x = 76;
        TestingUtils.assertWave(chart, WaveChart.SPARK_1, 0.04, x, x + 180, x + 360, x + 540);
        sendCommand("set_cranking_rpm 700");
        chart = nextChart();
        x = 55;
        TestingUtils.assertWave("cranking@600", chart, WaveChart.SPARK_1, 0.18, x, x + 180, x + 360, x + 540);

        IoUtil.changeRpm(2000);
        sendCommand("set_whole_fuel_map 1.57");

        chart = nextChart();

        TestingUtils.assertWave(chart, WaveChart.INJECTOR_1, 0.051, 238.75);
        TestingUtils.assertWave(chart, WaveChart.INJECTOR_2, 0.051, 53.04);
        TestingUtils.assertWave(chart, WaveChart.INJECTOR_3, 0.051, 417.04);
        TestingUtils.assertWave(chart, WaveChart.INJECTOR_4, 0.051, 594.04);

        x = 44;
        TestingUtils.assertWave(chart, WaveChart.SPARK_1, 0.133, x, x + 180, x + 360, x + 540);

        sendCommand("set_fuel_map 2200 4 15.66");
        sendCommand("set_fuel_map 2000 4 15.66");
        sendCommand("set_fuel_map 2200 4.2 15.66");
        sendCommand("set_fuel_map 2000 4.2 15.66");
        // fake 2 means 4 on the gauge because of the divider. should we simplify this?
        sendCommand("set_fake_maf_voltage 2");
        chart = nextChart();

        TestingUtils.assertWave(chart, WaveChart.INJECTOR_1, 0.522, 238.75);
        TestingUtils.assertWave(chart, WaveChart.INJECTOR_2, 0.522, 53.04);
        TestingUtils.assertWave(chart, WaveChart.INJECTOR_3, 0.522, 417.04);
        TestingUtils.assertWave(chart, WaveChart.INJECTOR_4, 0.522, 594.04);

        x = 58;
        TestingUtils.assertWave(chart, WaveChart.SPARK_1, 0.133, x, x + 180, x + 360, x + 540);
    }


    public static void main(String[] args) throws InterruptedException {
        FileLog.SIMULATOR_CONSOLE.start();
        FileLog.MAIN.start();

        boolean failed = false;
        try {
            IoUtil.launchSimulator();
            mainTestBody();
        } catch (Throwable e) {
            e.printStackTrace();
            failed = true;
        } finally {
            ExecHelper.destroy();
        }
        if (failed)
            System.exit(-1);
        FileLog.MAIN.logLine("*******************************************************************************");
        FileLog.MAIN.logLine("************************************  Looks good! *****************************");
        FileLog.MAIN.logLine("*******************************************************************************");
        System.exit(0); // this is a safer method eliminating the issue of non-daemon threads
    }
}
