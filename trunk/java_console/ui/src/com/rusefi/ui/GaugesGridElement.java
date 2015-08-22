package com.rusefi.ui;

import com.rusefi.core.Sensor;
import com.rusefi.ui.storage.Node;
import com.rusefi.ui.widgets.JPanelWithListener;
import com.rusefi.ui.widgets.SensorGauge;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * (c) Andrey Belomutskiy
 * 8/21/2015.
 */
public class GaugesGridElement {
    private static final String GAUGE_TYPE = "gauge";

    public static Component createGauge(Sensor sensor, SensorGauge.GaugeChangeListener gaugeChangeListener) {
        final JPanelWithListener wrapper = new JPanelWithListener(new BorderLayout());

        JMenuItem switchToLiveGraph = new JMenuItem("Live Graph");
        switchToLiveGraph.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                wrapper.removeAllChildrenAndListeners();

            }
        });


        SensorGauge.createGaugeBody(sensor, wrapper, gaugeChangeListener, switchToLiveGraph);

        return wrapper;
    }

    public static Component read(final Node config, Sensor defaultSensor) {
        String gaugeName = config.getProperty(GAUGE_TYPE, defaultSensor.name());
        Sensor sensor = lookup(gaugeName, defaultSensor);
        return GaugesGridElement.createGauge(sensor, new SensorGauge.GaugeChangeListener() {
            @Override
            public void onSensorChange(Sensor sensor) {
                config.setProperty(GAUGE_TYPE, sensor.name());
            }
        });
    }

    private static Sensor lookup(String gaugeName, Sensor defaultValue) {
        Sensor sensor;
        try {
            sensor = Sensor.valueOf(Sensor.class, gaugeName);
        } catch (IllegalArgumentException e) {
            sensor = defaultValue;
        }
        return sensor;
    }
}
