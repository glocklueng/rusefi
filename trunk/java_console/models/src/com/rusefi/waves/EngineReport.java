package com.rusefi.waves;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * A model of a digital signal represented as a sequence of {@link UpDown}
 *
 * Date: 6/23/13
 * (c) Andrey Belomutskiy
 *
 * @see com.rusefi.EngineSnifferPanel.AnalogChart
 */
public class EngineReport implements TimeAxisTranslator {
    public static final String ENGINE_CHART = "wave_chart";
    public static final EngineReport MOCK = new EngineReport(Collections.singletonList(new UpDown(0, -1, 1, -1)));
    /**
     * number of ChibiOS systicks per ms
     */
    public static final double SYS_TICKS_PER_MS = 100;
    public static final double RATIO = 0.05;
    public static final int mult = (int) (100 * SYS_TICKS_PER_MS); // 100ms
    private static final String WC_DOWN = "d";
    private static final String WC_UP = "u";

    private final List<UpDown> list;
    private int maxTime;
    /**
     * min timestamp on this chart, in systicks
     */
    private int minTime;

    public EngineReport(String report) {
        this(parse(report));
    }

    public EngineReport(List<UpDown> list) {
        this.list = list;
        if (!list.isEmpty()) {
            minTime = list.get(0).upTime;
            maxTime = list.get(list.size() - 1).downTime;
        }
    }

    public static boolean isCloseEnough(double v1, double v2) {
        return isCloseEnough(v1, v2, RATIO);
    }

    public static boolean isCloseEnough(double v1, double v2, double th) {
        if (v2 == 0)
            return v1 == 0;
        double ratio = v1 / v2;
        return Math.abs(1 - ratio) < th;
    }

    public List<UpDown> getList() {
        return list;
    }

    @Override
    public int getMaxTime() {
        return maxTime;
    }

    @Override
    public int getMinTime() {
        return minTime;
    }

    @NotNull
    public static List<UpDown> parse(String report) {
        String[] array = report.split("!");
//        if (array.length % 4 != 0)
//            throw new IllegalArgumentException("Unexpected length " + array.length);

        List<UpDown> times = new ArrayList<>();

        int index = 0;
        if (array[0].equals(WC_DOWN))
            index += 2;

        while (index + 3 < array.length) {
            if (!array[index].startsWith(WC_UP)) {
                index += 2;
                continue;
            }
            if (!array[index + 2].startsWith(WC_DOWN)) {
                index += 2;
                continue;
            }

            String upString[] = array[index].split("_");
            String downString[] = array[index + 2].split("_");
            try {
                int upTime = Integer.parseInt(array[index + 1]);
                int downTime = Integer.parseInt(array[index + 3]);

                int upEventIndex = upString.length > 1 ? Integer.parseInt(upString[1]) : -1;
                int downEventIndex = downString.length > 1 ? Integer.parseInt(downString[1]) : -1;


                times.add(new UpDown(upTime, upEventIndex, downTime, downEventIndex));
            } catch (NumberFormatException e) {
                System.err.println("Invalid? [" + Arrays.toString(upString) + "][" + Arrays.toString(downString) + "]");
            }

            index += 4;
        }
        return times;
    }

    @Override
    public int timeToScreen(int time, int width, ZoomProvider zoomProvider) {
        double translated = (time - minTime) * zoomProvider.getZoomValue() / getDuration();
        return (int) (width * translated);
    }

    @Override
    public double screenToTime(int screenX, int screenWidth, ZoomProvider zoomProvider) {
        //  / SYS_TICKS_PER_MS / 1000
        double time = 1.0 * screenX * getDuration() / screenWidth / zoomProvider.getZoomValue() + minTime;
        int x2 = timeToScreen((int) time, screenWidth, zoomProvider);
//        FileLog.rlog("screenToTime " + (screen - x2));
        return (int) time;
    }

    /**
     * @return Length of this chart ini systicks
     */
    public int getDuration() {
        return maxTime - minTime;
    }

    @Override
    public String toString() {
        return "EngineReport{" +
                "size=" + list.size() +
                ", maxTime=" + maxTime +
                ", minTime=" + minTime +
                '}';
    }

    public static class UpDown {
        // times in sys ticks
        public final int upTime;
        public final int upIndex;
        public final int downTime;
        public final int downIndex;

        public UpDown(int upTime, int upIndex, int downTime, int downIndex) {
            this.upTime = upTime;
            this.upIndex = upIndex;
            this.downTime = downTime;
            this.downIndex = downIndex;
        }

        public int getDuration() {
            return downTime - upTime;
        }

        @Override
        public String toString() {
            return "UpDown{" +
                    "upTime=" + upTime +
                    ", downTime=" + downTime +
                    ", d=" + getDuration() +
                    '}';
        }

        public double getDutyCycle(RevolutionLog rl) {
            double angleDuration = (rl.getCrankAngleByTime(downTime) + 720 - rl.getCrankAngleByTime(upTime)) % 360;
            if (angleDuration < 0)
                throw new IllegalStateException("Negative width: " + angleDuration);
            return angleDuration / 360;
        }
    }
}
