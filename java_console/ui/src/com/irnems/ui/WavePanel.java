package com.irnems.ui;

import com.irnems.FileLog;
import com.irnems.SerialManager;
import com.irnems.core.EngineState;
import com.irnems.core.Sensor;
import com.irnems.core.SensorCentral;
import com.irnems.ui.widgets.AnyCommand;
import com.irnems.ui.widgets.UpDownImage;
import com.irnems.waves.WaveReport;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 * Date: 6/23/13
 * Andrey Belomutskiy (c) 2012-2013
 */
public class WavePanel extends JPanel {
    public static final String DELI = "!";
    private static final int EFI_DEFAULT_CHART_SIZE = 180;

    private final Map<String, UpDownImage> images = new LinkedHashMap<String, UpDownImage>();
    private final JPanel imagePanel = new JPanel();
    private final ZoomControl zoomControl = new ZoomControl();
    private final ChartStatusPanel statusPanel = new ChartStatusPanel(zoomControl);
    private final UpDownImage crank = register("crank");

    private boolean isPaused;

    public WavePanel() {
        setLayout(new BorderLayout());

        statusPanel.setWaveReport(crank.createTranslator());

        JButton resetButton = new JButton("reset");
        resetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                for (UpDownImage image : images.values())
                    image.setWaveReport(WaveReport.MOCK, null);
            }
        });

        JButton saveImageButton = new JButton("save image");
        saveImageButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                saveImage();
            }
        });

        final JButton pauseButton = new JButton("pause");
        pauseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                isPaused = !isPaused;
                UiUtils.setPauseButtonText(pauseButton, isPaused);
            }
        });

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 5, 0));
        buttonPanel.add(resetButton);
        buttonPanel.add(saveImageButton);
        buttonPanel.add(pauseButton);
        buttonPanel.add(new RpmControl().setSize(2).getContent());

        JTextField command = AnyCommand.createCommandControl();
        command.setText("chartsize " + EFI_DEFAULT_CHART_SIZE);
        buttonPanel.add(command);

        buttonPanel.add(zoomControl);

        add(buttonPanel, BorderLayout.NORTH);
        add(imagePanel, BorderLayout.CENTER);
        add(statusPanel.infoPanel, BorderLayout.SOUTH);

        zoomControl.listener = new ZoomControl.ZoomControlListener() {
            @Override
            public void onZoomChange() {
                UpDownImage.trueRepaint(imagePanel);
            }
        };

        crank.setZoomProvider(zoomControl);
        imagePanel.add(crank);
        createSecondaryImage("crank2");
        createSecondaryImage("input1 A8");
        createSecondaryImage("input2 E5");

        createSecondaryImage("Spark 1");
        createSecondaryImage("Spark 2");

        createSecondaryImage("Injector 1");
        createSecondaryImage("Injector 2");
        createSecondaryImage("Injector 3");
        createSecondaryImage("Injector 4");

//        imagePanel.add(register("input0 C6").setTranslator(crank.getTranslator()));

        SerialManager.engineState.registerStringValueAction("wave_chart", new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String value) {
                if (isPaused)
                    return;
                displayChart(value);
            }
        });
    }

    public void displayChart(String value) {
        Map<String, StringBuilder> map = unpackToMap(value);

        StringBuilder revolutions = map.get("r");

        for (Map.Entry<String, StringBuilder> e : map.entrySet()) {
            UpDownImage image = images.get(e.getKey());
            if (image == null)
                continue;
            List<WaveReport.UpDown> list = WaveReport.parse(e.getValue().toString());
            if (list.isEmpty()) {
                image.onUpdate(); // this would reset empty image
                continue;
            }
            WaveReport wr = new WaveReport(list);
            image.setWaveReport(wr, revolutions);
        }
    }

    private Map<String, StringBuilder> unpackToMap(String value) {
        System.out.println(": " + value);

        String[] array = value.split(DELI);

        Map<String, StringBuilder> map = new HashMap<String, StringBuilder>();

        int index = 0;
        while (index + 2 < array.length) {
            String name = array[index];

            StringBuilder sb = map.get(name);
            if (sb == null) {
                sb = new StringBuilder();
                map.put(name, sb);
            }

            String signal = array[index + 1];
            String val = array[index + 2];

            sb.append(signal).append(DELI).append(val).append(DELI);
            index += 3;
        }
        return map;
    }

    private void createSecondaryImage(String name) {
        UpDownImage image = register(name).setTranslator(crank.createTranslator());
        image.setZoomProvider(zoomControl);
        imagePanel.add(image);
        imagePanel.setLayout(new GridLayout(images.size(), 1));
    }

    private void saveImage() {
        int rpm = RpmModel.getInstance().getValue();
        double maf = SensorCentral.getInstance().getValue(Sensor.MAF);
        String fileName = FileLog.getDate() + "rpm_" + rpm + "_maf_" + maf + ".png";
        UiUtils.saveImage(fileName, imagePanel);
    }

    private UpDownImage register(String name) {
        UpDownImage image = new UpDownImage(name);
        image.addMouseMotionListener(statusPanel.motionAdapter);
        images.put(name, image);
        return image;
    }
}
