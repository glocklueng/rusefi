package com.rusefi;

import com.irnems.waves.WaveReport;

import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 * 1/11/14.
 * (c) Andrey Belomutskiy
 */
public class RevolutionLog {
    private final TreeMap<Integer, Integer> time2rpm;

    public RevolutionLog(TreeMap<Integer, Integer> time2rpm) {
        this.time2rpm = time2rpm;
    }

    public static RevolutionLog parseRevolutions(StringBuilder revolutions) {
        TreeMap<Integer, Integer> time2rpm = new TreeMap<Integer, Integer>();
        if (revolutions == null)
            return new RevolutionLog(time2rpm);

        String[] r = revolutions.toString().split("!");
        for (int i = 0; i < r.length - 1; i += 2) {
            int rpm = Integer.parseInt(r[i]);
            int time = Integer.parseInt(r[i + 1]);
            time2rpm.put(time, rpm);
        }
        return new RevolutionLog(time2rpm);
    }

    public String getText(double time) {
        Map.Entry<Integer, Integer> entry = getTimeAndRpm(time);
        String text;
        if (entry == null) {
            text = "n/a";
        } else {
            double diff = time - entry.getKey();

            Integer rpm = entry.getValue();
            double timeForRevolution = 60000 * WaveReport.SYS_TICKS_PER_MS / rpm;

            double angle = 360.0 * diff / timeForRevolution;

            text = String.format("%.2f", angle);
        }
        return text;
    }

    public Map.Entry<Integer, Integer> getTimeAndRpm(double time) {
        return time2rpm.floorEntry((int) time);
    }

    public Set<Integer> keySet() {
        return time2rpm.keySet();
    }
}
