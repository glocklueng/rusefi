package com.rusefi.test;

import com.irnems.waves.WaveReport;
import com.rusefi.WaveChartParser;
import org.junit.Test;

import java.util.List;
import java.util.Map;

import static junit.framework.Assert.assertEquals;
import static junit.framework.Assert.assertTrue;

/**
 * 1/26/14
 * Andrey Belomutskiy (c) 2012-2014
 */
public class WaveChartParserTest {
    @Test
    public void testMultiParser() {
        Map<String, StringBuilder> result = WaveChartParser.unpackToMap("");
        assertTrue(result.isEmpty());

        result = WaveChartParser.unpackToMap("wave_chart,input1 A8!up!185080!r!0!2670996!crank!up!2670996_2!crank2!up!2674512!Injector 4!up!2674512!Spark 1!up!2674512!Injector 4!down!2674665!Spark 1!down!2674912!crank2!down!2680055!crank2!up!2687963!Injector 2!up!2687963!Spark 1!up!2687963!Injector 2!down!2688116!Spark 1!down!2688363!crank2!down!2693093!crank!down!2697428!crank2!up!2700454!Injector 1!up!2700454!Spark 1!up!2700454!Injector 1!down!2700607!Spark 1!down!2700854!crank2!down!2705329!crank2!up!2712449!Injector 3!up!2712449!Spark 1!up!2712449!Injector 3!down!2712681!Spark 1!down!2712849!crank2!down!2717385!r!0!2721629!crank!up!2721629!crank2!up!2724641!Injector 1!up!2724641!Injector 2!up!2724641!Injector 3!up!2724641!Injector 4!up!2724641!Spark 1!up!2724641!Injector 4!down!2726241!Injector 3!down!2726241!Injector 2!down!2726241!Injector 1!down!2726241!crank2!down!2729677!Spark 1!down!2730008!crank2!up!2736851!Injector 1!up!2736851!Injector 2!up!2736851!Injector 3!up!2736851!Injector 4!up!2736851!Spark 1!up!2736851!Injector 4!down!2738451!Injector 3!down!2738451!Injector 2!down!2738451!Injector 1!down!2738451!crank2!down!2741922!Spark 1!down!2742218!crank!down!2746104!crank2!up!2749010!Injector 1!up!2749010!Injector 2!up!2749010!Injector 3!up!2749010!Injector 4!up!2749010!Spark 1!up!2749010!Injector 4!down!2750601!Injector 3!down!2750601!Injector 2!down!2750601!Injector 1!down!2750601!crank2!down!2753919!Spark 1!down!2754377!crank2!up!2760922!Injector 1!up!2760922!Injector 2!up!2760922!Injector 3!up!2760922!Injector 4!up!2760922!Spark 1!up!2760922!Injector 4!down!2762522!Injector 3!down!2762522!Injector 2!down!2762522!Injector 1!down!2762522!crank2!down!2765882!Spark 1!down!2766289!r!236!2769990!crank!up!2769990!crank2!up!2773003!Injector 1!up!2773003!Injector 2!up!2773003!Injector 3!up!2773003!Injector 4!up!2773003!Spark 1!up!2773003!Injector 4!down!2774603!Injector 3!down!2774603!Injector 2!down!2774603!Injector 1!down!2774603!Spark 1!down!2778110!crank2!down!2778143!crank2!up!2785215!Injector 1!up!2785215!Injector 2!up!2785215!Injector 3!up!2785215!Injector 4!up!2785215!Spark 1!up!2785215!Injector 4!down!2786815!,");
        assertEquals(9, result.size());

        String crankReport = result.get("crank").toString();

        List<WaveReport.UpDown> list = WaveReport.parse(crankReport);
        assertEquals(2, list.size());

        WaveReport.UpDown upDown = list.get(0);
        assertEquals(2670996, upDown.upTime);
        assertEquals(2, upDown.upIndex);

        assertEquals(2697428, upDown.downTime);
        assertEquals(-1, upDown.downIndex);
    }
}
