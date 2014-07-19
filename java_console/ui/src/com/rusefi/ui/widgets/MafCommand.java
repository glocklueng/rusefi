package com.rusefi.ui.widgets;

import com.irnems.EcuStimulator;
import com.irnems.core.Sensor;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;

/**
 * 6/30/13
 * (c) Andrey Belomutskiy
 */
public class MafCommand extends JPanel {
    public MafCommand() {
        setBorder(BorderFactory.createLineBorder(Color.BLACK));
        setLayout(new FlowLayout(FlowLayout.LEFT));
        add(new JLabel("MAF: "));
        final JSpinner maf = new JSpinner(new SpinnerNumberModel(Double.valueOf(1.5), null, null, Double.valueOf(0.11))) {
            @Override
            public Dimension getPreferredSize() {
                Dimension size = super.getPreferredSize();
                return new Dimension(100, size.height);
            }
        };
        final SpinnerNumberModel m = (SpinnerNumberModel) maf.getModel();
//        m.setStepSize(0.1);
//        maf.setValue(3);
        maf.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                Double value = (Double) m.getValue();

                EcuStimulator.setPotVoltage(value, Sensor.MAF);
            }
        });


        add(maf);
    }
}
