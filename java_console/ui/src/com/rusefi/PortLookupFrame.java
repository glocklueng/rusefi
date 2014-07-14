package com.rusefi;

import com.irnems.Launcher;
import com.rusefi.io.LinkManager;
import com.rusefi.io.tcp.TcpConnector;
import com.rusefi.ui.UiUtils;
import jssc.SerialPortList;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * This frame is used on startup to select the port we would be using
 *
 * @author Andrey Belomutskiy 2/14/14
 */
public class PortLookupFrame {
    public static void chooseSerialPort() {
        List<String> ports = new ArrayList<String>();
        ports.addAll(Arrays.asList(SerialPortList.getPortNames()));
        ports.addAll(TcpConnector.getAvailablePorts());

        final JFrame frame = new JFrame("Serial port selection");

        JPanel content = new JPanel(new BorderLayout());

        final JPanel upperPanel = new JPanel(new FlowLayout());

        if (!ports.isEmpty())
            addPortSelection(ports, frame, upperPanel);

        final JButton buttonLogViewer = new JButton();
        buttonLogViewer.setText("Use " + LinkManager.LOG_VIEWER);
        buttonLogViewer.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.dispose();
                new Launcher(LinkManager.LOG_VIEWER);
            }
        });

        upperPanel.add(buttonLogViewer);

        JPanel lowerPanel = new JPanel(new FlowLayout());
        if (SimulatorHelper.isBinaryHere()) {
        } else {
            lowerPanel.add(new JLabel(SimulatorHelper.BINARY + " not found"));
        }


        content.add(upperPanel, BorderLayout.NORTH);
        content.add(lowerPanel, BorderLayout.SOUTH);

        frame.add(content);
        frame.pack();
        frame.setVisible(true);
        UiUtils.centerWindow(frame);
    }

    private static void addPortSelection(List<String> ports, final JFrame frame, JPanel panel) {
        final JComboBox<String> comboPorts = new JComboBox<String>();
        for (final String port : ports)
            comboPorts.addItem(port);
        panel.add(comboPorts);

        final JButton connect = new JButton("Connect");
        panel.add(connect);
        connect.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.dispose();
                new Launcher(comboPorts.getSelectedItem().toString());
            }
        });
    }
}