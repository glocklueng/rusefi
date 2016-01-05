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

        FuelAutoTune.process(false, dataPoints, 0.1);

    }
}
