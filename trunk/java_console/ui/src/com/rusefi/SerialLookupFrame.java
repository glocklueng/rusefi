package com.rusefi;

import com.irnems.Launcher;
import jssc.SerialPortList;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * @author Andrey Belomutskiy
 *         2/14/14
 */
public class SerialLookupFrame {
    public static void chooseSerialPort() {
        String ports[] = SerialPortList.getPortNames();

        if (ports.length == 0) {
            JOptionPane.showMessageDialog(null, "No serial ports found");
            System.exit(-1);
        }

        final JFrame frame = new JFrame("Serial port selection");

        JPanel panel = new JPanel(new FlowLayout());

        for (final String port : ports) {
            JButton button = new JButton("Use " + port);

            button.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    frame.dispose();
                    new Launcher(port);

                }
            });


            panel.add(button);
        }

        frame.add(panel);
        frame.pack();
        frame.setVisible(true);


    }
}
