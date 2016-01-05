package com.rusefi.autotune.test;

import com.rusefi.autotune.FuelAutoTune;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

/**
 * 1/5/2016
 * (c) Andrey Belomutskiy 2013-2015
 */
public class FuelAutoTuneTest {

    @Test
    public void testAutoTune() {
        List<FuelAutoTune.stDataOnline> dataPoints = new ArrayList<>();
        dataPoints.add(new FuelAutoTune.stDataOnline(13, 1200, 80));

        {
            FuelAutoTune.Result r = FuelAutoTune.process(false, dataPoints, 0.1);
            printNotDefault(r.getKgbcRES(), 1);
        }

        dataPoints.add(new FuelAutoTune.stDataOnline(13, 1200, 80));
        dataPoints.add(new FuelAutoTune.stDataOnline(14, 1300, 60));
        dataPoints.add(new FuelAutoTune.stDataOnline(15, 1400, 70));
        dataPoints.add(new FuelAutoTune.stDataOnline(16, 1500, 90));

        {
            FuelAutoTune.Result r = FuelAutoTune.process(false, dataPoints, 0.1);
            printNotDefault(r.getKgbcRES(), 1);
        }
    }

    /**
     * this method prints all values which do not equal default value
     */
    private static void printNotDefault(double[][] array, double defaultValue) {
        for (int i = 0; i < array.length; i++) {
            printNotDefault(array[i], i, defaultValue);
        }
    }

    private static void printNotDefault(double[] array, int index, double defaultValue) {
        for (int i = 0; i < array.length; i++) {
            if (array[i] != defaultValue)
                System.out.println(index + " " + i + ": " + array[i]);
        }
    }
}
