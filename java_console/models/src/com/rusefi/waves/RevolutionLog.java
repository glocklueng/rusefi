package com.rusefi.waves;

import com.rusefi.io.tcp.TcpConnector;

import java.util.*;

import static com.rusefi.io.tcp.TcpConnector.*;

/**
 * 1/11/14.
 * (c) Andrey Belomutskiy
 */
public class RevolutionLog {
    public static final String TOP_DEAD_CENTER_MESSAGE = "r";
    private final TreeMap<Integer, Integer> time2rpm;

    public RevolutionLog(TreeMap<Integer, Integer> time2rpm) {
        this.time2rpm = time2rpm;
    }

    public static RevolutionLog parseRevolutions(CharSequence revolutions) {
        TreeMap<Integer, Integer> time2rpm = new TreeMap<Integer, Integer>();
        if (revolutions == null)
            return new RevolutionLog(time2rpm);

        String[] r = revolutions.toString().split("!");
        for (int i = 0; i < r.length - 1; i += 2) {
            int rpm = parseIntWithReason(r[i], "RL rpm");
            int time = parseIntWithReason(r[i + 1], "RL time");
            time2rpm.put(time, rpm);
        }
        return new RevolutionLog(time2rpm);
    }

    public String getCrankAngleByTimeString(double time) {
        double result = getCrankAngleByTime(time);
        return Double.isNaN(result) ? "n/a" : String.format("%.2f", result);
    }

    public double getCrankAngleByTime(double time) {
        return doGetAngle(time, true);
    }

    private double doGetAngle(double time, boolean tryNextRevolution) {
        Map.Entry<Integer, Integer> entry = getTimeAndRpm(time);
        if (entry == null) {
            if (tryNextRevolution && time2rpm.size() >= 2) {
                // we are here if the value is below the first revolution point
                List<Map.Entry<Integer, Integer>> element = new ArrayList<Map.Entry<Integer, Integer>>(time2rpm.entrySet());
                Map.Entry<Integer, Integer> first = element.get(0);
                Map.Entry<Integer, Integer> second = element.get(1);

                int oneRevolutionDuration = second.getKey() - first.getKey();
                return doGetAngle(time + oneRevolutionDuration, false);
            } else {
                return Double.NaN;
            }
        } else {
            double diff = time - entry.getKey();

            Integer rpm = entry.getValue();
            double timeForRevolution = 60000 * WaveReport.SYS_TICKS_PER_MS / rpm;

            return 360.0 * diff / timeForRevolution;
        }
    }

    public Map.Entry<Integer, Integer> getTimeAndRpm(double time) {
        return time2rpm.floorEntry((int) time);
    }

    public Set<Integer> keySet() {
        return time2rpm.keySet();
    }
}
