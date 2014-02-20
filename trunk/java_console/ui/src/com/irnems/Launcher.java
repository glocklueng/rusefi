package com.irnems;

import com.irnems.core.EngineState;
import com.irnems.core.MessagesCentral;
import com.irnems.ui.*;
import com.rusefi.AnalogChartPanel;
import com.rusefi.SerialLookupFrame;
import jssc.SerialPortList;

import javax.swing.*;

/**
 * this is the main entry point of rusEfi ECU console
 * <p/>
 * <p/>
 * Date: 12/25/12
 * (c) Andrey Belomutskiy
 */
public class Launcher extends FrameHelper {
    private static final Object CONSOLE_VERSION = "20140219";

    public Launcher(String port) {
        FileLog.INSTANCE.start();

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
//        tabbedPane.setSelectedIndex(5);

        for (String p : SerialPortList.getPortNames())
            MessagesCentral.getInstance().postMessage(Launcher.class, "Available port: " + p);

        showFrame(tabbedPane);
    }

    @Override
    protected void onWindowOpened() {
        super.onWindowOpened();
        setTitle("N/A");
        SerialManager.scheduleOpening();

        SerialManager.engineState.registerStringValueAction("rusEfiVersion", new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String value) {
                setTitle(value);
            }
        });

    }

    private void setTitle(String value) {
        frame.setTitle("Console " + CONSOLE_VERSION + "; firmwave=" + value);
    }

    @Override
    protected void onWindowClosed() {
        super.onWindowClosed();
        /**
         * looks like reconnectTimer in {@link RpmPanel} keeps AWT alive. Simplest solution would be to 'exit'
         */
        System.exit(0);
    }

    public static void main(final String[] args) throws Exception {
        Thread.setDefaultUncaughtExceptionHandler(new DefaultExceptionHandler());
        SwingUtilities.invokeAndWait(new Runnable() {
            public void run() {
                awtCode(args);
            }
        });
    }

    private static void awtCode(String[] args) {
        try {

            boolean isPortDefined = args.length > 0;
            if (isPortDefined) {
                new Launcher(args[0]);
            } else {
                SerialLookupFrame.chooseSerialPort();
            }

        } catch (Throwable e) {
            throw new IllegalStateException(e);
        }
    }
//
//    private static String lookupPort() {
//        String[] ports = new String[]{};
//        if (!SerialManager.onlyUI) {
//            ports = SerialPortList.getPortNames();
//            if (ports.length < 2)
//                throw new IllegalStateException("expected two ports but got only " + Arrays.toString(ports));
//        }
//        return ports.length > 1 ? ports[1] : null;
//    }
}
