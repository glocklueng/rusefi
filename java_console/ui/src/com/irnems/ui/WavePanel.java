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

        SerialManager.engineState.registerStringValueAction("wave_chart", new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String value) {
                if (isPaused)
                    return;
                displayChart(value);
            }
        });

        displayChart("wave_chart,crank!up!195516017!crank2!up!195520613!crank2!down!195520982!crank2!up!195522416!crank2!down!195522773!crank2!up!195524194!crank2!down!195524549!crank2!up!195525950!crank2!down!195526298!crank2!up!195531597!crank!down!195534219!crank2!down!195536880!crank2!up!195538456!crank2!down!195538828!crank2!up!195540239!crank2!down!195540593!crank2!up!195542000!crank2!down!195542353!crank!up!195547625!crank2!up!195552694!crank2!down!195553059!crank2!up!195554486!crank2!down!195554847!crank2!up!195556270!crank2!down!195556630!crank2!up!195558020!crank2!down!195558366!r!187!195561100!crank!down!195561100!crank2!up!195563637!crank2!down!195568921!crank2!up!195570499!crank2!down!195570866!crank2!up!195572279!crank2!down!195572636!crank2!up!195574030!crank2!down!195574383!crank!up!195580109!crank2!up!195584695!crank2!down!195585052!crank2!up!195586479!crank2!down!195586838!crank2!up!195588254!crank2!down!195588602!crank2!up!195590004!crank2!down!195590354!crank2!up!195595644!crank!down!195598280!crank2!down!195600917!crank2!up!195602491!crank2!down!195602858!crank2!up!195604283!crank2!down!195604636!crank2!up!195606027!crank2!down!195606370!crank!up!195611646!crank2!up!195616703!crank2!down!195617066!crank2!up!195618496!crank2!down!195618856!crank2!up!195620272!crank2!down!195620623!crank2!up!195622035!crank2!down!195622385!r!187!195625106!crank!down!195625106!crank2!up!195627647!crank2!down!195632923!crank2!up!195634492!crank2!down!195634860!crank2!up!195636280!crank2!down!195636628!crank2!up!195638009!crank2!down!195638351!crank!up!195644090!crank2!up!195648680!crank2!down!195649038!crank2!up!195650470!crank2!down!195650826!crank2!up!195652244!crank2!down!195652554!crank2!up!195652554!crank2!down!195652554!crank2!up!195652554!crank!down!195652554!crank!up!195652554!crank2!down!195652593!crank2!down!195653575!crank2!up!195653575!crank2!down!195653575!crank2!up!195653575!crank2!up!195653975!crank2!down!195654325!crank2!up!195659895!crank!down!195662965!crank2!down!195666267!crank2!up!195668322!crank2!down!195668794!crank2!up!195670657!crank2!down!195671125!,");
    }

    public void displayChart(String value) {
        Map<String, StringBuilder> map = unpackToMap(value);

        StringBuilder revolutions = map.get("r");


        statusPanel.setRevolutions(revolutions);

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
