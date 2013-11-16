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
 * (c) Andrey Belomutskiy
 */
public class WavePanel extends JPanel {
    public static final String DELI = "!";
    private final Map<String, UpDownImage> images = new LinkedHashMap<String, UpDownImage>();
    private final JPanel imagePanel = new JPanel();
    private boolean isPaused;
    private final UpDownImage crank = register("crank");
    private final ZoomControl zoomControl = new ZoomControl();

    public WavePanel() {
        setLayout(new BorderLayout());

        JButton resetButton = new JButton("reset");
        resetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                for (UpDownImage image : images.values())
                    image.setWaveReport(WaveReport.MOCK);
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

        JPanel buttonPanel = new JPanel(new FlowLayout());
        buttonPanel.add(resetButton);
        buttonPanel.add(saveImageButton);
        buttonPanel.add(pauseButton);

        JTextField command = AnyCommand.createCommandControl();
        command.setText("chartsize 90");
        buttonPanel.add(command);

        buttonPanel.add(zoomControl);

        add(buttonPanel, BorderLayout.NORTH);

        add(imagePanel, BorderLayout.CENTER);

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

        for (Map.Entry<String, StringBuilder> e : map.entrySet()) {
            UpDownImage image = images.get(e.getKey());
            List<WaveReport.UpDown> list = WaveReport.parse(e.getValue().toString());
            if (list.isEmpty()) {
                image.onUpdate(); // this would reset empty image
                continue;
            }
            WaveReport wr = new WaveReport(list);
            image.setWaveReport(wr);
        }
    }

    private Map<String, StringBuilder> unpackToMap(String value) {
        System.out.println(": " + value);

        String[] array = value.split(DELI);

        Map<String, StringBuilder> map = new HashMap<String, StringBuilder>();

        for (String name : images.keySet())
            map.put(name, new StringBuilder());

        int index = 0;
        while (index + 2 < array.length) {
            String name = array[index];

            if (!images.containsKey(name)) {
                System.out.println("what name? " + name);
                index += 3;
                continue;
//                createSecondaryImage(name);
//                map.put(name, new StringBuilder());
            }

            String signal = array[index + 1];
            String val = array[index + 2];

            StringBuilder sb = map.get(name);
            if (sb == null)
                throw new NullPointerException("Not found " + name);
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
        images.put(name, image);
        return image;
    }
}
