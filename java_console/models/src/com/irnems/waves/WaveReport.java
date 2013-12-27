package com.irnems.waves;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Date: 6/23/13
 * (c) Andrey Belomutskiy
 */
public class WaveReport implements TimeAxisTranslator {
    public static final WaveReport MOCK = new WaveReport(Collections.<UpDown>singletonList(new UpDown(0, 1)));
    /**
     * number of ChibiOS systicks per ms
     */
    public static final double SYS_TICKS_PER_MS = 100;
    public static final int mult = (int) (100 * SYS_TICKS_PER_MS); // 100ms

    List<UpDown> list;
    private int maxTime;
    /**
     * min timestamp on this chart, in systicks
     */
    private int minTime;

    public WaveReport(String report) {
        this(parse(report));
    }

    public WaveReport(List<UpDown> list) {
        if (list.isEmpty())
            throw new IllegalStateException("empty");
        this.list = list;
        minTime = list.get(0).upTime;
        maxTime = list.get(list.size() - 1).downTime;
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

    public static List<UpDown> parse(String report) {
        String[] array = report.split("!");
//        if (array.length % 4 != 0)
//            throw new IllegalArgumentException("Unexpected length " + array.length);

        List<UpDown> times = new ArrayList<UpDown>();

        int index = 0;
        if (array[0].equals("down"))
            index += 2;

        while (index + 3 < array.length) {
            if (array[index].equals("down")) {
                index += 2;
                continue;
            }

            String upString = array[index + 1];
            String downString = array[index + 3];
            try {
                int upTime = Integer.parseInt(upString);
                int downTime = Integer.parseInt(downString);

                times.add(new UpDown(upTime, downTime));
            } catch (NumberFormatException e) {
                System.err.println("Invalid? [" + upString + "][" + downString + "]");
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
    public double screenToTime(int screen, int width, ZoomProvider zoomProvider) {
        //  / SYS_TICKS_PER_MS / 1000
        double time = 1.0 * screen * getDuration() / width / zoomProvider.getZoomValue() + minTime;
        int x2 = timeToScreen((int) time, width, zoomProvider);
        System.out.println("" + (screen - x2));
        return (int) time;
    }

    /**
     *
     * @return Length of this chart ini systicks
     */
    public int getDuration() {
        return maxTime - minTime;
    }

    @Override
    public String toString() {
        return "WaveReport{" +
                "size=" + list.size() +
                ", maxTime=" + maxTime +
                ", minTime=" + minTime +
                '}';
    }

    public static class UpDown {
        // times in sys ticks
        public final int upTime;
        public final int downTime;

        UpDown(int upTime, int downTime) {
            this.upTime = upTime;
            this.downTime = downTime;
        }

        public int getDuration() {
            return downTime - upTime;
        }

        @Override
        public String toString() {
            return "UpDown{" +
                    "upTime=" + upTime +
                    ", downTime=" + downTime +
                    '}';
        }
    }
}
