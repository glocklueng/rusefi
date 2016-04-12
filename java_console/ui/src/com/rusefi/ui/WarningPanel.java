package com.rusefi.ui;

import com.rusefi.Launcher;
import com.rusefi.core.MessagesCentral;
import com.rusefi.ui.util.UiUtils;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class WarningPanel {

    private static final String WARNING = "WARNING";
    private static final String ERROR = "firmware error";
    private final JPanel panel = new JPanel(new BorderLayout());

    private final JLabel label = new JLabel();
    private final JButton reset = new JButton("clear warning");
    private final Timer fatalBlinking = new Timer(1000, new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
            label.setVisible(!label.isVisible());
            UiUtils.trueRepaint(label);
        }
    });

    public WarningPanel() {
        label.setForeground(Color.red);
        panel.add(label, BorderLayout.WEST);

        Font currentFont = label.getFont();
        label.setFont(currentFont.deriveFont((float) (currentFont.getSize() * 1.5)));

        clear();

        reset.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                clear();
            }
        });

        MessagesCentral.getInstance().addListener(new MessagesCentral.MessageListener() {
            boolean haveFatalError;

            @Override
            public void onMessage(Class clazz, String message) {
                if (haveFatalError)
                    return;

                if (message.startsWith(Launcher.FATAL_ERROR_PREFIX)) {
                    haveFatalError = true;
                    fatalBlinking.start();
                    label.setText(message);
                    return;
                }
                if (message.startsWith(WARNING) || message.startsWith(ERROR)) {
                    label.setText(message);
                    reset.setEnabled(true);
                }
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
