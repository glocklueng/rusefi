package com.rusefi;

import com.rusefi.ui.engine.UpDownImage;
import com.rusefi.ui.util.FrameHelper;
import com.rusefi.ui.util.UiUtils;
import com.rusefi.waves.EngineReport;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Arc2D;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 * 06235/15
 * (c) Andrey Belomutskiy 2013-2015
 */
public class TriggerImage {

    public static final String TRIGGERTYPE = "TRIGGERTYPE";
    private static int WIDTH = 320;

    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.out.println("Path to file expected");
            System.exit(-1);
        }
        String path = args[0];

        FrameHelper f = new FrameHelper();

        JPanel trigger = new JPanel(new BorderLayout()) {
            @Override
            public Dimension getPreferredSize() {
                return new Dimension(3 * WIDTH, 480);
            }
        };

        f.showFrame(trigger);


        BufferedReader br = new BufferedReader(new FileReader(path + File.separator + "triggers.txt"));

        String line;
        while ((line = br.readLine()) != null) {

            if (line.startsWith(TRIGGERTYPE)) {
                readTrigger(br, line, trigger);
            }
        }
    }

    private static void readTrigger(BufferedReader br, String line, JPanel trigger) throws IOException {
        String[] tokens = line.split(" ");
        String id = tokens[1];
        String countStr = tokens[2];
        String name = tokens[3];
        int count = Integer.parseInt(countStr);

        System.out.println("id=" + id + ", count=" + count + ", name=" + name);

        List<Signal> signals = new ArrayList<>();

        for (int index = 0; index < count; index++) {
            line = br.readLine();
            tokens = line.split(" ");
            String signalStr = tokens[2];
            int signal = Integer.parseInt(signalStr);
            String angleStr = tokens[3];
            double angle = Double.parseDouble(angleStr);

            signals.add(new Signal(signal, angle));
        }

        List<Signal> toShow = new ArrayList<>(signals);
        for (Signal s : signals)
            toShow.add(new Signal(s.signal, s.angle + 720));
        for (Signal s : signals)
            toShow.add(new Signal(s.signal, s.angle + 720 * 2));


        double unusedDown = Double.NaN;
        double prevUp = Double.NaN;

        List<EngineReport.UpDown> list = new ArrayList<>();

        for (Signal s: toShow) {
            int waveIndex = s.signal / 1000;

            if (waveIndex != 0)
                continue;

            if (s.signal == 1) {
                // down signal
                if (Double.isNaN(prevUp)) {
                    // we have down before up, we would need to use it later
                    unusedDown = s.angle;
                } else {
                    EngineReport.UpDown ud = new EngineReport.UpDown((int) (WIDTH * prevUp), 0, (int) (WIDTH * s.angle), 0);
                    list.add(ud);
                }


                prevUp = Double.NaN;
            } else {
                // up signal handling
                prevUp = s.angle;
            }
        }

//        if ()

        EngineReport re = new EngineReport(list);

        trigger.removeAll();

        UpDownImage upDownImage = new UpDownImage(re, "trigger");
        upDownImage.showText = false;
        trigger.add(upDownImage, BorderLayout.CENTER);

        UiUtils.trueLayout(trigger);


    }

    private static class Signal {
        private final int signal;
        private final double angle;

        public Signal(int signal, double angle) {

            this.signal = signal;
            this.angle = angle;
        }
    }
}