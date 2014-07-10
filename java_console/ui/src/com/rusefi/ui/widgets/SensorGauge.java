package com.rusefi.ui.widgets;

import com.irnems.core.Sensor;
import com.irnems.core.SensorCentral;
import eu.hansolo.steelseries.gauges.Radial;
import eu.hansolo.steelseries.tools.ColorDef;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Arrays;
import java.util.Collection;

/**
 * Date: 7/9/14
 * (c) Andrey Belomutskiy 2012-2014
 */

public class SensorGauge {
    public static final Collection<Sensor> MOCKABLE = Arrays.asList(Sensor.CLT, Sensor.AFR, Sensor.IAT);

    public static Component createGauge(final Sensor sensor) {
        return createGauge(sensor, 1);
    }

    public static Component createGauge(final Sensor sensor, final double correction) {
        final Radial gauge = createRadial(sensor.getName(), sensor.getUnits(), sensor.getMaxValue(), sensor.getMinValue());

        gauge.setBackgroundColor(sensor.getColor());

        SensorCentral.getInstance().addListener(sensor, new SensorCentral.AdcListener() {
            public void onAdcUpdate(SensorCentral model, double value) {
                gauge.setValue(value * correction);
            }
        });
        gauge.setLcdDecimals(2);

        gauge.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    int size = gauge.getSize().width;
                    JFrame n = new JFrame(sensor.getName());
                    boolean isMockable = MOCKABLE.contains(sensor);
                    int h = isMockable ? (int) (size * 1.5) : size;

                    JPanel content = new JPanel(new BorderLayout());

                    content.add(createGauge(sensor, correction), BorderLayout.CENTER);

                    n.setSize(size, h);
                    n.setAlwaysOnTop(true);
                    n.add(content);
                    n.setVisible(true);
                    n.setLocation(e.getXOnScreen(), e.getYOnScreen());
                }
            }
        });

        return gauge;
    }

    public static Radial createRadial(String title, String units, double maxValue, double minValue) {
//        final Section[] SECTIONS =
//                {
//                        new Section(0, to, Color.red)
//                };

        Radial radial1 = new Radial();
//        radial1.setSections(SECTIONS);
        radial1.setTitle(title);
        radial1.setUnitString(units);

        //radial1.setTrackStop(to);

        radial1.setMinValue(minValue);
        radial1.setMaxValue(maxValue);
        radial1.setThresholdVisible(false);
        radial1.setPointerColor(ColorDef.RED);

        radial1.setValue(0);
        return radial1;
    }
}


