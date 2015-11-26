package com.rusefi.ui;

import com.rusefi.core.Sensor;
import com.rusefi.core.SensorCentral;
import org.scilab.forge.jlatexmath.TeXConstants;
import org.scilab.forge.jlatexmath.TeXFormula;
import org.scilab.forge.jlatexmath.TeXIcon;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;

public class FormulasPane {
    private final JPanel content = new JPanel(new BorderLayout());
    private final JPanel centerProxy = new JPanel(new BorderLayout());

    public FormulasPane() {
        content.add(centerProxy, BorderLayout.CENTER);

        updateFormula();
        new Timer(200, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                updateFormula();
            }
        }).start();
    }

    private void updateFormula() {
        SensorCentral sc = SensorCentral.getInstance();
        double clt = sc.getValue(Sensor.CLT);
        double iat = sc.getValue(Sensor.IAT);
        double tps = sc.getValue(Sensor.TPS);
        double map = sc.getValue(Sensor.MAP);

        String tCharge = "$Tcharge=f(CLT=" + String.format("%.1f", clt) + "C,IAT=" + String.format("%.1f", iat)
                + "C,TPS=99\\%)=123C$";

        String page = tCharge + "\r\n";

        TeXFormula formula = new TeXFormula(page);
        TeXIcon icon = formula.createTeXIcon(TeXConstants.STYLE_DISPLAY, 20);

        BufferedImage image = new BufferedImage(icon.getIconWidth(), icon.getIconHeight(), BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2 = image.createGraphics();
        g2.setColor(Color.white);
        g2.fillRect(0, 0, icon.getIconWidth(), icon.getIconHeight());
        JLabel label = new JLabel(icon);

        centerProxy.removeAll();
        centerProxy.add(label, BorderLayout.CENTER);
    }

    public JPanel getContent() {
        return content;
    }
}