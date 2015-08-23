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
    private static final String IS_LIVE_GRAPH = "type";

    private final JPanelWithListener wrapper = new JPanelWithListener(new BorderLayout());
    private final Node config;

    private GaugesGridElement(Node config) {
        this.config = config;
    }

    private Component createLiveBarElement(final Node config, final Sensor defaultSensor) {
        wrapper.setLayout(new GridLayout(2, 1));

        JMenuItem switchToGauge = new JMenuItem("Switch to Gauge Mode");
        switchToGauge.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                wrapper.removeAllChildrenAndListeners();
                config.setBoolProperty(IS_LIVE_GRAPH, false);

                createGauge(defaultSensor);
            }
        });

        wrapper.add(new SensorLiveGraph(config.getChild("top"), defaultSensor, switchToGauge));
        wrapper.add(new SensorLiveGraph(config.getChild("bottom"), Sensor.RPM, switchToGauge));
        return wrapper;
    }

    private Component createGauge(final Sensor sensor) {
        SensorGauge.GaugeChangeListener gaugeChangeListener = new SensorGauge.GaugeChangeListener() {
            @Override
            public void onSensorChange(Sensor sensor) {
                config.setProperty(GAUGE_TYPE, sensor.name());
            }
        };

        JMenuItem switchToLiveGraph = new JMenuItem("Switch to Live Graph");
        switchToLiveGraph.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                wrapper.removeAllChildrenAndListeners();
                config.setBoolProperty(IS_LIVE_GRAPH, true);

                createLiveBarElement(config, sensor);
            }
        });

        wrapper.setLayout(new BorderLayout());
        SensorGauge.createGaugeBody(sensor, wrapper, gaugeChangeListener, switchToLiveGraph);

        return wrapper;
    }

    public static Component read(final Node config, Sensor defaultSensor) {

        if (config.getBoolProperty(IS_LIVE_GRAPH)) {
            return new GaugesGridElement(config).createLiveBarElement(config, defaultSensor);
        }

        String gaugeName = config.getProperty(GAUGE_TYPE, defaultSensor.name());
        Sensor sensor = Sensor.lookup(gaugeName, defaultSensor);
        return new GaugesGridElement(config).createGauge(sensor);
    }

}
