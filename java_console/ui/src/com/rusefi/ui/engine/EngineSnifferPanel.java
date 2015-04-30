package com.rusefi.ui.engine;

import com.rusefi.FileLog;
import com.rusefi.config.Fields;
import com.rusefi.core.EngineState;
import com.rusefi.core.Sensor;
import com.rusefi.core.SensorCentral;
import com.rusefi.io.LinkManager;
import com.rusefi.ui.*;
import com.rusefi.ui.config.BitConfigField;
import com.rusefi.ui.config.ConfigField;
import com.rusefi.ui.storage.Node;
import com.rusefi.ui.util.UiUtils;
import com.rusefi.ui.widgets.AnyCommand;
import com.rusefi.ui.util.URLLabel;
import com.rusefi.waves.RevolutionLog;
import com.rusefi.waves.WaveChart;
import com.rusefi.waves.WaveChartParser;
import com.rusefi.waves.WaveReport;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.List;

import static com.rusefi.ui.util.LocalizedMessages.CLEAR;
import static com.rusefi.ui.util.LocalizedMessages.PAUSE;

/**
 * Engine Sniffer control consists of a set of {@link UpDownImage}
 * <p/>
 * <p/>
 * Date: 6/23/13
 * Andrey Belomutskiy (c) 2012-2013
 *
 * @see EngineSnifferStatusPanel status bar
 * @see com.rusefi.ui.test.WavePanelSandbox
 */
public class EngineSnifferPanel {
    private static final int EFI_DEFAULT_CHART_SIZE = 180;
    public static final Comparator<String> INSTANCE = new NameUtil.ImageOrderComparator();
    private static final String HELP_URL = "http://rusefi.com/wiki/index.php?title=Manual:DevConsole#Digital_Chart";
    public static final String HELP_TEXT = "Click here for online help";
    public static final String SAVE_IMAGE = "save image";

    private final JPanel chartPanel = new JPanel(new BorderLayout());
    private final JPanel panel = new JPanel(new BorderLayout());

    /**
     * imageName -> UpDownImage
     */
    private final Map<String, UpDownImage> images = new TreeMap<>(INSTANCE);
    /**
     * this is the panel which displays all {@link UpDownImage} using {@link GridLayout}
     */
    private final JPanel imagePanel = new JPanel(new GridLayout(1, 1)) {
        @Override
        public Dimension getPreferredSize() {
            Dimension d = chartPanel.getSize();
            Dimension s = super.getPreferredSize();
            return new Dimension((int) (d.width * zoomControl.getZoomProvider().getZoomValue()), s.height);
        }
    };

    private final JScrollPane pane = new JScrollPane(imagePanel, JScrollPane.VERTICAL_SCROLLBAR_NEVER, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

    private final ZoomControl zoomControl = new ZoomControl();
    private final EngineSnifferStatusPanel statusPanel = new EngineSnifferStatusPanel(zoomControl.getZoomProvider());
    private final UpDownImage crank = createImage(NameUtil.CRANK1);
    private final ChartScrollControl scrollControl;

    private boolean isPaused;

    public EngineSnifferPanel(Node config) {
        LinkManager.engineState.registerStringValueAction(EngineState.OUTPIN_TAG, new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String value) {
                String pinInfo[] = value.split("@");
                if (pinInfo.length != 2)
                    return;
                String channel = pinInfo[0];
                String pin = pinInfo[1];
                UpDownImage image = images.get(channel);
                if (image != null)
                    image.setPhysicalPin(pin);
            }
        });


        statusPanel.setWaveReport(crank.createTranslator());

        JButton clearButton = new JButton(CLEAR.getMessage());
        clearButton.setMnemonic('c');
        clearButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                for (UpDownImage image : images.values())
                    image.setWaveReport(WaveReport.MOCK, null);
            }
        });

        JButton saveImageButton = new JButton(SAVE_IMAGE);
        saveImageButton.setMnemonic('s');
        saveImageButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                saveImage();
            }
        });

        final JButton pauseButton = new JButton(PAUSE.getMessage());
        pauseButton.setMnemonic('p');
        pauseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                isPaused = !isPaused;
                UiUtils.setPauseButtonText(pauseButton, isPaused);
            }
        });

        JPanel upperPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 5, 0));
        upperPanel.add(clearButton);
        upperPanel.add(saveImageButton);
        upperPanel.add(pauseButton);
        upperPanel.add(new RpmLabel(2).getContent());

        JComponent command = new AnyCommand(config, "chartsize " + EFI_DEFAULT_CHART_SIZE, true).getContent();
        upperPanel.add(command);

        upperPanel.add(zoomControl);

        scrollControl = ChartRepository.getInstance().createControls(new ChartRepository.ChartRepositoryListener() {
            @Override
            public void onDigitalChart(String chart) {
                displayChart(chart);
            }
        });
        if (LinkManager.isLogViewer())
            upperPanel.add(scrollControl.getContent());

        upperPanel.add(new URLLabel(HELP_TEXT, HELP_URL));

        JPanel lowerButtons = new JPanel(new FlowLayout(FlowLayout.RIGHT, 5, 0));
        lowerButtons.add(new BitConfigField(Fields.isDigitalChartEnabled, "Collect Engine Data").getContent());
        lowerButtons.add(new ConfigField(Fields.ENGINE_SNIFFER_SIZE, "Engine Sniffer size").getContent());

        JPanel bottomPanel = new JPanel(new BorderLayout());
        bottomPanel.add(lowerButtons, BorderLayout.NORTH);
        bottomPanel.add(statusPanel.infoPanel, BorderLayout.SOUTH);

        chartPanel.add(upperPanel, BorderLayout.NORTH);
        chartPanel.add(pane, BorderLayout.CENTER);
        chartPanel.add(bottomPanel, BorderLayout.SOUTH);

        zoomControl.listener = new ZoomControl.ZoomControlListener() {
            @Override
            public void onZoomChange() {
                UiUtils.trueRepaint(imagePanel);
            }
        };

        crank.setZoomProvider(zoomControl.getZoomProvider());
        resetImagePanel();
//        createSecondaryImage("c2");
//        createSecondaryImage("input1 A8");
//        createSecondaryImage("input2 E5");
//

        LinkManager.engineState.registerStringValueAction(WaveReport.WAVE_CHART, new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String value) {
                if (isPaused)
                    return;
                displayChart(value);
            }
        });

        panel.add(chartPanel, BorderLayout.CENTER);
        panel.add(new WarningPanel().getPanel(), BorderLayout.SOUTH);

//        displayChart("wave_chart,crank2!down!192811978!crank2!up!192813389!crank2!down!192813749!crank2!up!192815156!crank2!down!192815512!crank!up!192820764!crank2!up!192825818!crank2!down!192826182!crank2!up!192827610!crank2!down!192827975!crank2!up!192829399!crank2!down!192829757!crank2!up!192831154!crank2!down!192831507!r!187!192834224!crank!down!192834224!crank2!up!192836757!crank2!down!192841994!crank2!up!192843561!crank2!down!192843925!crank2!up!192845334!crank2!down!192845693!crank2!up!192847086!crank2!down!192847439!crank!up!192853135!crank2!up!192857701!crank2!down!192858065!crank2!up!192859491!crank2!down!192859858!crank2!up!192861269!crank2!down!192861626!crank2!up!192863025!crank2!down!192863382!crank2!up!192868647!crank!down!192871268!crank2!down!192872804!crank2!up!192872804!crank!down!192872804!crank!up!192872804!crank2!down!192873898!crank2!up!192875508!crank2!down!192875887!crank2!up!192877357!crank2!down!192877732!crank2!up!192879192!crank2!down!192879565!crank!up!192886293!r!0!194982088!crank!down!194982088!crank2!up!194984699!crank2!down!194990112!crank2!up!194991715!crank2!down!194992085!crank2!up!194993530!crank2!down!194993884!crank2!up!194995292!crank2!down!194995645!crank!up!195001475!crank2!up!195006153!crank2!down!195006515!crank2!up!195007968!crank2!down!195008325!crank2!up!195009773!crank2!down!195010134!crank2!up!195011549!crank2!down!195011901!crank2!up!195017256!crank!down!195019915!crank2!down!195022597!crank2!up!195024189!crank2!down!195024554!crank2!up!195025980!crank2!down!195026329!crank2!up!195027744!crank2!down!195028103!crank!up!195033418!crank2!up!195038542!crank2!down!195038911!crank2!up!195040351!crank2!down!195040722!crank2!up!195042167!crank2!down!195042529!crank2!up!195043934!crank2!down!195044294!r!187!195047060!crank!down!195047060!crank2!up!195049619!crank2!down!195054954!crank2!up!195056549!crank2!down!195056920!crank2!up!195058345!crank2!down!195058703!crank2!up!195060114!crank2!down!195060464!crank!up!195066245!crank2!up!195070882!crank2!down!195071250!crank2!up!195072689!crank2!down!195073054!crank2!up!195074479!,");
    }

    private void resetImagePanel() {
        imagePanel.removeAll();
        imagePanel.add(crank);
        images.put(NameUtil.CRANK1, crank);
    }

    public void displayChart(String value) {
        WaveChart map = WaveChartParser.unpackToMap(value);

        StringBuilder revolutions = map.get(RevolutionLog.TOP_DEAD_CENTER_MESSAGE);

        statusPanel.setRevolutions(revolutions);

        /**
         * First let's create images for new keys
         */
        for (String imageName : map.getMap().keySet())
            createSecondaryImage(imageName);


        for (String imageName : images.keySet()) {
            UpDownImage image = images.get(imageName);
            if (image == null)
                throw new IllegalStateException("image not found for " + imageName);

            StringBuilder sb = map.getMap().get(imageName);
            String report = sb == null ? "" : sb.toString();

            image.setRevolutions(revolutions);
            List<WaveReport.UpDown> list = WaveReport.parse(report);
            WaveReport wr = new WaveReport(list);
            image.setWaveReport(wr, revolutions);
        }
        /**
         * this is to fix the UI glitch when images tab shows a tiny square
         */
        UiUtils.trueRepaint(chartPanel.getParent());
    }

    public JPanel getPanel() {
        return panel;
    }

    private void createSecondaryImage(String name) {
        if (images.containsKey(name) || RevolutionLog.TOP_DEAD_CENTER_MESSAGE.equalsIgnoreCase(name))
            return;

        int index = getInsertIndex(name, images.keySet());

        FileLog.MAIN.logLine("Registering " + name + "@" + index);

        UpDownImage image = createImage(name);
        images.put(name, image);
        image.setTranslator(crank.createTranslator());
        image.setZoomProvider(zoomControl.getZoomProvider());
        imagePanel.add(image, index);
        imagePanel.setLayout(new GridLayout(images.size(), 1));
    }

    public static int getInsertIndex(String name, Set<String> strings) {
        String[] mapKeys = new String[strings.size()];
        int pos = 0;
        for (String key : strings)
            mapKeys[pos++] = key;

//        int index = -Arrays.binarySearch(mapKeys, name) - 1;
        int index = -Arrays.binarySearch(mapKeys, 0, mapKeys.length, name, INSTANCE) - 1;
        if (index >= strings.size())
            index = -1;
        return index;
    }

    private void saveImage() {
        int rpm = RpmModel.getInstance().getValue();
        double maf = SensorCentral.getInstance().getValue(Sensor.MAF);
        String fileName = FileLog.getDate() + "rpm_" + rpm + "_maf_" + maf + ".png";

        UiUtils.saveImageWithPrompt(fileName, panel, imagePanel);
    }

    private UpDownImage createImage(String name) {
        UpDownImage image = new UpDownImage(name);
        image.addMouseMotionListener(statusPanel.motionAdapter);
        return image;
    }

    public void reloadFile() {
        displayChart(ChartRepository.getInstance().getChart(0));
        scrollControl.reset();
    }
}
