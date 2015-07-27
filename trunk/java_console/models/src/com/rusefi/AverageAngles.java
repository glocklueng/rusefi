package com.rusefi;

import org.apache.commons.math3.stat.descriptive.moment.Mean;
import org.apache.commons.math3.stat.descriptive.moment.StandardDeviation;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * 2/15/2015
 */
public class AverageAngles {

    private static final int MAX_RPM_CHANGE = 20;
    private int rpmAtPrevChart;
    Map<Integer, List<AngleEvent>> angleData = new TreeMap<>();

    public AverageAngles() {
        clear();
    }

    public String getReport() {
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        try {
            printReport(new PrintStream(byteArrayOutputStream));
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
        return byteArrayOutputStream.toString();
    }

    public void clear() {
        rpmAtPrevChart = -1;
        angleData.clear();
    }

    public void add(int rpm, String line) {
        if (rpmAtPrevChart != -1 && Math.abs(rpmAtPrevChart - rpm) > MAX_RPM_CHANGE) {
            System.out.println("Skipping due to rpm change: was " + rpmAtPrevChart + " now " + rpm);
            rpmAtPrevChart = rpm;
            return;
        }
        rpmAtPrevChart = rpm;

        String v[] = line.split("\\|");
        System.out.println("rpm " + rpm + ": " + v.length + " values");

        List<AngleEvent> current = new ArrayList<>();

        for (int i = 0; i < v.length / 2; i++) {
            Double angle = Double.parseDouble(v[2 * i]);
            int signal = (int)Double.parseDouble(v[2 * i + 1]);
            if (Double.isNaN(angle)) {
                System.out.println("Skipping due to NaN");
                return;
            }
            current.add(new AngleEvent(angle));
        }

        for (int i = 0; i < current.size(); i++) {
            List<AngleEvent> list = angleData.get(i);
            if (list == null) {
                list = new ArrayList<>();
                angleData.put(i, list);
            }
            list.add(current.get(i));
        }
    }

    public void printReport(Appendable stream) throws IOException {
        List<Double> angles = new ArrayList<>();

        stream.append("Based on " + angleData.size() + " charts\r\n");

        stream.append("index,average,stdev,diff\r\n");

        double prev = 0;

        for (Map.Entry<Integer, List<AngleEvent>> e : angleData.entrySet()) {
            int k = e.getKey();
            List<AngleEvent> v = e.getValue();
            double values[] = new double[v.size()];
            for (int i = 0; i < v.size(); i++)
                values[i] = v.get(i).getAngle();

            Mean m = new Mean();
            double mean = m.evaluate(values);

            StandardDeviation sd = new StandardDeviation();
            double sdv = sd.evaluate(values, mean);

            angles.add(mean);

            double diff = mean - prev;
            prev = mean;
            stream.append(k + "," + mean + "," + sdv + "," + diff + "\r\n");
        }
        if (angleData.isEmpty())
            return;
        Double lastValue = angles.get(angles.size() - 1);
        stream.append("Last value = " + lastValue + "\r\n");
        double delta = 720 - lastValue;
        for (double v : angles) {
            stream.append((delta + v) + "\r\n");
        }
    }

    private static class AngleEvent {
        private final double angle;

        public AngleEvent(double angle) {
            this.angle = angle;
        }

        public double getAngle() {
            return angle;
        }
    }
}
