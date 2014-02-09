package com.irnems;

import com.irnems.core.MessagesCentral;
import com.irnems.ui.*;
import com.rusefi.AnalogChartPanel;
import jssc.SerialPortException;
import jssc.SerialPortList;

import javax.swing.*;
import java.util.Arrays;

/**
 * this is the main entry point of rusEfi ECU console
 * <p/>
 * <p/>
 * Date: 12/25/12
 * (c) Andrey Belomutskiy
 */
public class Launcher extends FrameHelper {

    public Launcher(String port) throws SerialPortException {
        SerialManager.port = port;

        JTabbedPane tabbedPane = new JTabbedPane();

        RpmPanel rpmPanel = new RpmPanel();
        tabbedPane.addTab("Main", rpmPanel.createRpmPanel());
        tabbedPane.addTab("Gauges", new GaugePanel());
        tabbedPane.addTab("Digital Sniffer", WavePanel.getInstance());
        tabbedPane.addTab("Analog Sniffer", new AnalogChartPanel());

//        tabbedPane.addTab("ADC", new AdcPanel(new BooleanInputsModel()).createAdcPanel());
//        tabbedPane.add("Emulation Map", EcuStimulator.panel);
//        tabbedPane.addTab("live map adjustment", new Live3DReport().getControl());
        tabbedPane.add("MessagesCentral", new MsgPanel());

        tabbedPane.add("Log Viewer", new LogViewer());

        tabbedPane.setSelectedIndex(2);
        tabbedPane.setSelectedIndex(5);

        for (String p : SerialPortList.getPortNames())
            MessagesCentral.getInstance().postMessage(Launcher.class, "Available port: " + p);

        showFrame(tabbedPane);
    }

    @Override
    protected void onWindowOpened() {
        super.onWindowOpened();
        SerialManager.scheduleOpening();
    }

    @Override
    protected void onWindowClosed() {
        super.onWindowClosed();
        /**
         * looks like reconnectTimer in {@link RpmPanel} keeps AWT alive. Simplest solution would be to 'exit'
         */
        System.exit(0);
    }

    public static void main(String[] args) throws Exception {
        Thread.setDefaultUncaughtExceptionHandler(new DefaultExceptionHandler());

        try {
            FileLog.INSTANCE.start();
        } catch (Throwable e) {
            DefaultExceptionHandler.handleException(e);
        }

        final String port = args.length > 0 ? args[0] : lookupPort();

        SwingUtilities.invokeAndWait(new Runnable() {
            public void run() {
                try {
                    new Launcher(port);
                } catch (SerialPortException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    private static String lookupPort() {
        String[] ports = new String[]{};
        if (!SerialManager.onlyUI) {
            ports = SerialPortList.getPortNames();
            if (ports.length < 2)
                throw new IllegalStateException("expected two ports but got only " + Arrays.toString(ports));
        }
        return ports.length > 1 ? ports[1] : null;
    }
}
