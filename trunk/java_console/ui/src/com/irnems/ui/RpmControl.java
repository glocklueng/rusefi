package com.irnems.ui;

import com.irnems.SerialManager;
import com.irnems.core.EngineTimeListener;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * 9/17/13
 * (c) Andrey Belomutskiy
 */
public class RpmControl {
    private JPanel content = new JPanel(new FlowLayout(FlowLayout.LEFT, 5, 0));

    private final JLabel rpmValue = new JLabel("N/A");
    private final JLabel rpmCaption = new JLabel("RPM:");

    public RpmControl() {
        rpmCaption.setBorder(BorderFactory.createLineBorder(Color.white));
        rpmValue.setForeground(Color.red);

        content.setBorder(BorderFactory.createLineBorder(Color.white));
        content.add(rpmCaption);
        content.add(rpmValue, "grow, wrap");

        RpmModel.getInstance().addListener(new RpmModel.RpmListener() {
            public void onRpmChange(RpmModel rpm) {
                int value = rpm.getSmoothedValue();
                if (value == -1)
                    rpmValue.setText("Noise");
                else
                    rpmValue.setText(value + "");
            }
        });

        final Timer timer1 = new Timer(2000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rpmValue.setForeground(Color.red);
            }
        });


        SerialManager.engineState.timeListeners.add(new EngineTimeListener() {
            @Override
            public void onTime(double time) {
                rpmValue.setForeground(Color.green);
                /**
                 * this timer will catch engine inactivity and display a warning
                 */
                timer1.restart();
            }
        });
    }

    public JPanel getContent() {
        return content;
    }

    public RpmControl setSize(int size) {
        Font f = rpmCaption.getFont();
        int fontSize = size * f.getSize();
        Font font = new Font(f.getName(), f.getStyle(), fontSize);
        setFont(font);
        return this;
    }

    private void setFont(Font font) {
        rpmCaption.setFont(font);
        rpmValue.setFont(font);
    }
}
