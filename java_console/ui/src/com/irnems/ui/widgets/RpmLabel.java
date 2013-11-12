package com.irnems.ui.widgets;

import com.irnems.core.Sensor;
import com.irnems.core.SensorCentral;

import javax.swing.*;

/**
 * Just a simple JLabel with RPM value
 * <p/>
 * 8/1/13
 * (c) Andrey Belomutskiy
 */
public class RpmLabel extends JLabel {

    public RpmLabel() {
        SensorCentral.getInstance().addListener(Sensor.RPM, new SensorCentral.AdcListener() {
            @Override
            public void onAdcUpdate(SensorCentral model, double value) {
                RpmLabel.this.setText("RPM: " + (int) value);
            }
        });
    }
}
