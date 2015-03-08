package com.rusefi;

import com.rusefi.core.EngineState;
import com.rusefi.core.MessagesCentral;
import com.rusefi.io.LinkManager;
import com.rusefi.maintenance.VersionChecker;
import com.rusefi.ui.*;
import com.rusefi.ui.engine.EngineSnifferPanel;
import com.rusefi.ui.fsio.FlexibleControls;
import com.rusefi.ui.logview.LogViewer;
import com.rusefi.ui.storage.Node;
import com.rusefi.ui.util.DefaultExceptionHandler;
import com.rusefi.ui.util.FrameHelper;
import jssc.SerialPortList;

import javax.swing.*;

import static com.rusefi.ui.storage.PersistentConfiguration.getConfig;

/**
 * this is the main entry point of rusEfi ECU console
 * <p/>
 * <p/>
 * 12/25/12
 * (c) Andrey Belomutskiy 2013-2015
 *
 * @see StartupFrame
 * @see com.rusefi.ui.engine.EngineSnifferPanel
 * @see com.rusefi.StartupFrame
 */
public class Launcher extends FrameHelper {
    public static final int CONSOLE_VERSION = 20150307;
    public static final boolean SHOW_STIMULATOR = true;
    public static final String TAB_INDEX = "main_tab";
    private final String port;
    private final JTabbedPane tabbedPane = new JTabbedPane();

    public static int defaultFontSize;

    public Launcher(String port) {
        this.port = port;
        FileLog.MAIN.start();

        LinkManager.start(port);

        FileLog.MAIN.logLine("Console " + CONSOLE_VERSION);


        EngineSnifferPanel engineSnifferPanel = new EngineSnifferPanel(getConfig().getRoot().getChild("digital_sniffer"));
        if (LinkManager.isLogViewerMode(port))
            tabbedPane.add("Log Viewer", new LogViewer(engineSnifferPanel));

        RpmPanel mainGauges = new RpmPanel(getConfig().getRoot().getChild("main_gauges"));
        tabbedPane.addTab("Main", mainGauges.createRpmPanel());
        tabbedPane.addTab("Gauges", new GaugesPanel().getContent());
        tabbedPane.addTab("Engine Sniffer", engineSnifferPanel.getPanel());
        tabbedPane.addTab("Sensor Sniffer", new AnalogChartPanel().getPanel());

        tabbedPane.addTab("LE controls", new FlexibleControls().getPanel());

//        tabbedPane.addTab("ADC", new AdcPanel(new BooleanInputsModel()).createAdcPanel());
        if (SHOW_STIMULATOR && !LinkManager.isStimulationMode && !LinkManager.isLogViewerMode(port)) {
            EcuStimulator stimulator = EcuStimulator.getInstance();
            tabbedPane.add("ECU stimulation", stimulator.getPanel());
        }
//        tabbedPane.addTab("live map adjustment", new Live3DReport().getControl());
        tabbedPane.add("Messages", new MessagesPane(getConfig().getRoot().getChild("messages")).getContent());
        tabbedPane.add("Wizards", new Wizard().createPane());


        if (!LinkManager.isLogViewerMode(port)) {
            int selectedIndex = getConfig().getRoot().getIntProperty("main_tab", 2);
            if (selectedIndex < tabbedPane.getTabCount())
                tabbedPane.setSelectedIndex(selectedIndex);
        }

        StartupFrame.setAppIcon(frame);
        showFrame(tabbedPane);
    }

    @Override
    protected void onWindowOpened() {
        super.onWindowOpened();
        setTitle("N/A");

        LinkManager.open();

        LinkManager.engineState.registerStringValueAction(EngineState.RUS_EFI_VERSION_TAG, new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String firmwareVersion) {
                setTitle(firmwareVersion);
                VersionChecker.getInstance().onFirmwareVersion(firmwareVersion);
            }
        });
    }

    private void setTitle(String value) {
        frame.setTitle("Console " + CONSOLE_VERSION + "; firmware=" + value + "@" + port);
    }

    @Override
    protected void onWindowClosed() {
        super.onWindowClosed();
        /**
         * looks like reconnectTimer in {@link RpmPanel} keeps AWT alive. Simplest solution would be to 'exit'
         */
        SimulatorHelper.onWindowClosed();
        Node root = getConfig().getRoot();
        root.setProperty("version", CONSOLE_VERSION);
        root.setProperty(TAB_INDEX, tabbedPane.getSelectedIndex());
        getConfig().save();
        System.exit(0);
    }

    public static void main(final String[] args) throws Exception {
        getConfig().load();
        Thread.setDefaultUncaughtExceptionHandler(new DefaultExceptionHandler());
        VersionChecker.start();
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
                for (String p : SerialPortList.getPortNames())
                    MessagesCentral.getInstance().postMessage(Launcher.class, "Available port: " + p);
                new StartupFrame().chooseSerialPort();
            }

        } catch (Throwable e) {
            throw new IllegalStateException(e);
        }
    }
}
