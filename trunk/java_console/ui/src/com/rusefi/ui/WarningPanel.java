package com.rusefi.ui;

import com.irnems.core.MessagesCentral;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class WarningPanel {

    private final JPanel panel = new JPanel(new BorderLayout());

    private final JLabel label = new JLabel();
    private final JButton reset = new JButton("reset");

    public WarningPanel() {
        label.setForeground(Color.red);
        panel.add(label, BorderLayout.WEST);

        clear();

        reset.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                clear();
            }
        });

        MessagesCentral.getInstance().addListener(new MessagesCentral.MessageListener() {
            @Override
            public void onMessage(Class clazz, String message) {
                if (!message.startsWith("WARNING"))
                    return;
                label.setText(message);
                reset.setEnabled(true);
            }
        });
        panel.add(reset, BorderLayout.EAST);
    }

    private void clear() {
        label.setText("");
        reset.setEnabled(false);
    }

    public JPanel getPanel() {
        return panel;
    }
}
