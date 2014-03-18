package com.rusefi.waves;

import java.util.Map;

/**
 * A collection of {@link WaveReport}
 * <p/>
 * <p/>
 *
 * @see WaveChartParser
 * <p/>
 * Date: 3/17/14
 * (c) Andrey Belomutskiy
 */
public class WaveChart {
    public static final String INJECTOR_1 = "Injector 1";
    public final Map<String, StringBuilder> map;

    public WaveChart(Map<String, StringBuilder> map) {
        this.map = map;
    }

    public StringBuilder get(String key) {
        return map.get(key);
    }
}
