package com.rusefi;

import com.rusefi.ui.engine.UpDownImage;
import com.rusefi.ui.util.FrameHelper;
import com.rusefi.ui.util.UiUtils;
import com.rusefi.waves.EngineReport;
import org.putgemin.VerticalFlowLayout;

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
    public static final String TRIGGERS = "triggers";
    private static int WIDTH = 320;
    /**
     * number of extra frames
     */
    private static int EXTRA_COUNT = 0;

    private static int WAVE_COUNT = 2;

    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.out.println("Path to file expected");
            System.exit(-1);
        }
        String path = args[0];

        FrameHelper f = new FrameHelper();

        TriggerPanel trigger = new TriggerPanel(new GridLayout(WAVE_COUNT, 1)) {
            @Override
            public Dimension getPreferredSize() {
                return new Dimension((1 + EXTRA_COUNT) * WIDTH, 480);
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

    private static void readTrigger(BufferedReader br, String line, TriggerPanel trigger) throws IOException {
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
        for (int i = 1; i<= EXTRA_COUNT; i++) {
            for (Signal s : signals)
                toShow.add(new Signal(s.signal, s.angle + i * 720));
        }

        List<WaveState> waves = new ArrayList<>();
        waves.add(new WaveState());
        waves.add(new WaveState());

        for (Signal s : toShow) {
            int waveIndex = s.signal / 1000;
            int signal = s.signal % 1000;

            if (waveIndex > 1) {
                // TT_HONDA_ACCORD_CD
                continue;
//                throw new IllegalStateException(s.signal + " in " + name);
            }

            WaveState waveState = waves.get(waveIndex);
            waveState.handle(signal, s.angle);
        }

//        if (!Double.isNaN(unusedDown)) {

        //          prevUp -= 2 * 720; // this up is from the 3rd frame

        // add at the start
//            list.add(0, new EngineReport.UpDown(angleToTime(prevUp - 720), 0, angleToTime(unusedDown), 0));

        // add at the end
        //          list.add(0, new EngineReport.UpDown(angleToTime(prevUp + 2 * 720), 0, angleToTime(unusedDown + 3 * 720), 0));
//        }

        trigger.removeAll();

        EngineReport re0 = new EngineReport(waves.get(0).list);
        EngineReport re1 = new EngineReport(waves.get(1).list);

        UpDownImage upDownImage0 = new UpDownImage(re0, "trigger");
        upDownImage0.showText = false;
        trigger.add(upDownImage0);

        UpDownImage upDownImage1 = new UpDownImage(re1, "trigger");
        upDownImage1.showText = false;
        trigger.add(upDownImage1);

        trigger.name = name;

        UiUtils.trueLayout(trigger);
        new File(TRIGGERS).mkdir();
        UiUtils.saveImage(TRIGGERS + File.separator + "trigger_" + id + ".png", trigger);
    }

    private static int angleToTime(double prevUp) {
        return (int) (WIDTH * prevUp);
    }

    private static class Signal {
        private final int signal;
        private final double angle;

        public Signal(int signal, double angle) {
            this.signal = signal;
            this.angle = angle;
        }
    }

    private static class WaveState {
        double unusedDown = Double.NaN;
        double prevUp = Double.NaN;

        List<EngineReport.UpDown> list = new ArrayList<>();

        public void handle(int signal, double angle) {
            if (signal == 1) {
                // down signal
                if (Double.isNaN(prevUp)) {
                    // we have down before up, we would need to use it later
                    unusedDown = angle;
                } else {
                    EngineReport.UpDown ud = new EngineReport.UpDown(angleToTime(prevUp), 0, angleToTime(angle), 0);
                    list.add(ud);
                }
                prevUp = Double.NaN;
            } else {
                // up signal handling
                prevUp = angle;
            }
        }
    }

    private static class TriggerPanel extends JPanel {
        public String name = "";

        public TriggerPanel(LayoutManager layout) {
            super(layout);
        }

        @Override
        public void paint(Graphics g) {
            super.paint(g);

            g.setColor(Color.black);
            Font f = g.getFont();
            g.setFont(new Font(f.getName(), Font.BOLD, f.getSize() * 3));

            int h = getHeight();

            g.drawString(name, 0, (int) (h * 0.75));
        }
    }
}