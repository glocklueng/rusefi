package com.rusefi;

import com.irnems.FileLog;
import com.irnems.core.MessagesCentral;
import com.irnems.core.Sensor;
import com.irnems.core.SensorCentral;
import com.irnems.ui.RpmModel;
import com.irnems.ui.UiUtils;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.List;

/**
 * Date: 12/21/13
 * Andrey Belomutskiy (c) 2012-2013
 */
public class AnalogChartPanel extends JPanel {
    private final TreeMap<Double, Double> values = new TreeMap<Double, Double>();

    private double minX;
    private double maxX;

    private static final String KEY = "analog_chart";

    private double minY;
    private double maxY;

    private boolean paused = false;

    public AnalogChartPanel() {
        super(new BorderLayout());

        MessagesCentral.getInstance().addListener(new MessagesCentral.MessageListener() {
            @Override
            public void onMessage(Class clazz, String message) {
                if (paused || !message.startsWith(KEY))
                    return;
                unpackValues(values, message);

                processValues();
            }
        });

        final AnalogChart analogChart = new AnalogChart();

        JPanel upperPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 5, 0));

        JButton imageButton = new JButton("save image");
        upperPanel.add(imageButton);
        imageButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int rpm = RpmModel.getInstance().getValue();
                String fileName = FileLog.getDate() + "rpm_" + rpm + "_analog" + ".png";
                UiUtils.saveImage(fileName, analogChart);
            }
        });

        final JButton pauseButton = new JButton("Pause");
        upperPanel.add(pauseButton);
        pauseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                paused = !paused;
                pauseButton.setText(paused ? "Resume" : "Pause");
            }
        });

        add(upperPanel, BorderLayout.NORTH);
        add(analogChart, BorderLayout.CENTER);
    }

    private void processValues() {
        List<Double> keys = new ArrayList<Double>(values.keySet());
        minX = keys.get(0);
        maxX = keys.get(keys.size() - 1);
        System.out.println("Analog chart from " + minX + " to " + maxX);

        TreeSet<Double> sortedValues = new TreeSet<Double>();
        sortedValues.addAll(values.values());
        List<Double> values = new ArrayList<Double>(sortedValues);

        minY = values.get(0);
        maxY = values.get(values.size() - 1);
    }

    private class AnalogChart extends JComponent {
        @Override
        public void paint(Graphics g) {
            super.paint(g);
            //Graphics2D g2 = (Graphics2D) g;

            Dimension size = getSize();

            g.drawString("X range from " + minX + " to " + maxX, 4, 20);
            g.drawString("Y range from " + minY + " to " + maxY, 4, 40);

            int prevX = 0;
            int prevY = size.height;

            double bX = size.width / (maxX - minX);
            double bY = size.height / (maxY - minY);

            for (Map.Entry<Double, Double> e : values.entrySet()) {
                int x = (int) ((e.getKey() - minX) * bX);
                int y = size.height - (int) ((e.getValue() - minY) * bY);

                g.drawLine(prevX, prevY, x, y);
                prevX = x;
                prevY = y;
            }
        }
    }

    private void unpackValues(TreeMap<Double, Double> values, String chart) {
        values.clear();

        String[] tokens = chart.split("\\|");
        for (int i = 1; i < tokens.length - 1; ) {
            String key = tokens[i++];
            String value = tokens[i++];

            values.put(Double.parseDouble(key), Double.parseDouble(value));
        }
    }
}