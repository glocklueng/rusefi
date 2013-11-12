package com.irnems.ui;

import javax.swing.*;
import java.awt.*;

/**
 * 9/17/13
 * (c) Andrey Belomutskiy
 */
public class RpmControl {
    public JPanel upperPanel = new JPanel(new FlowLayout());

    protected final JLabel rpmValue = new JLabel("N/A");

    public RpmControl() {
        JLabel rpmCaption = new JLabel("RPM:");
        Font f = rpmCaption.getFont();
        int fontSize = 15 * f.getSize();
        rpmCaption.setFont(new Font(f.getName(), f.getStyle(), fontSize));
        rpmCaption.setBorder(BorderFactory.createLineBorder(Color.white));
        rpmValue.setFont(new Font(f.getName(), f.getStyle(), fontSize));
        rpmValue.setForeground(Color.red);

        upperPanel.setBorder(BorderFactory.createLineBorder(Color.white));
        upperPanel.add(rpmCaption);
        upperPanel.add(rpmValue, "grow, wrap");


        RpmModel.getInstance().addListener(new RpmModel.RpmListener() {
            public void onRpmChange(RpmModel rpm) {
                rpmValue.setText(rpm.getSmoothedValue() + "");
            }
        });
    }
}
