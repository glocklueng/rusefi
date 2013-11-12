package com.irnems.ui.widgets;

import com.irnems.waves.TimeAxisTranslator;
import com.irnems.waves.WaveReport;
import com.irnems.waves.ZoomProvider;

import javax.swing.*;
import java.awt.*;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * This is a renderer of {@link WaveReport} - this makes a simple Logical Analyzer
 * <p/>
 * <p/>
 * Date: 6/23/13
 * (c) Andrey Belomutskiy
 */
public class UpDownImage extends JPanel {
    private static final SimpleDateFormat FORMAT = new SimpleDateFormat("yyyy-MM-dd'T'hh:mm:ss");
    private static final int LINE_SIZE = 20;
    /**
     * number of ChibiOS systicks per ms
     */
    public static final double TICKS_PER_MS = 100;

    private long lastUpdateTime;
    private ZoomProvider zoomProvider = ZoomProvider.DEFAULT;
    private WaveReport wr;
    private final String name;
    private TimeAxisTranslator translator;

    public UpDownImage(final String name) {
        this(WaveReport.MOCK, name);
    }

    public void setZoomProvider(ZoomProvider zoomProvider) {
        this.zoomProvider = zoomProvider;
    }

    public void onUpdate() {
        trueRepaint(this);
    }

    public static void trueRepaint(JComponent control) {
        control.invalidate();
        control.repaint();
    }

    public UpDownImage(WaveReport wr, String name) {
        this.name = name;
        setWaveReport(wr);
        setOpaque(true);
        translator = createTranslator();
    }

    public UpDownImage setTranslator(TimeAxisTranslator translator) {
        this.translator = translator;
        return this;
    }

    public TimeAxisTranslator createTranslator() {
        return new TimeAxisTranslator() {
            @Override
            public int translateTime(int time, int width, ZoomProvider zoomProvider) {
                return UpDownImage.this.wr.translateTime(time, width, zoomProvider);
            }

            @Override
            public int getMaxTime() {
                return UpDownImage.this.wr.getMaxTime();
            }

            @Override
            public int getMinTime() {
                return UpDownImage.this.wr.getMinTime();
            }
        };
    }

    public void setWaveReport(WaveReport wr) {
        this.wr = wr;
        lastUpdateTime = System.currentTimeMillis();
        onUpdate();
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2 = (Graphics2D) g;

        Dimension d = getSize();
        g.setColor(getBackground());
        g.fillRect(0, 0, d.width, d.height);

        for (WaveReport.UpDown upDown : wr.getList())
            paintUpDown(d, upDown, g);

        paintVerticalLines(g2, d);

        int duration = wr.getDuration();
        g2.setColor(Color.black);

        int line = 0;
        g.drawString(name, 5, ++line * LINE_SIZE);
        g.drawString("Tick length: " + duration + "; count=" + wr.getList().size(), 5, ++line * LINE_SIZE);
        g.drawString("Total seconds: " + (duration / TICKS_PER_MS / 000.0), 5, ++line * LINE_SIZE);
        g.drawString(FORMAT.format(new Date(lastUpdateTime)), 5, ++line * LINE_SIZE);
    }

    private void paintVerticalLines(Graphics2D g2, Dimension d) {
        int mult = 100 * 100; // 100ms
        int fromMs = translator.getMinTime() / mult;
        g2.setStroke(new BasicStroke());
        g2.setColor(Color.red);

        int toMs = translator.getMaxTime() / mult;
        for (int ms = fromMs; ms <= toMs; ms++) {
            int tick = ms * mult;
            int x = translator.translateTime(tick, d.width, zoomProvider);
            g2.drawLine(x, 0, x, d.height);
        }
    }

    private void paintUpDown(Dimension d, WaveReport.UpDown upDown, Graphics g) {

        int x1 = translator.translateTime(upDown.upTime, d.width, zoomProvider);
        int x2 = translator.translateTime(upDown.downTime, d.width, zoomProvider);

        int y = (int) (0.2 * d.height);

        g.setColor(Color.cyan);
        g.fillRect(x1, y, x2 - x1, d.height);

        g.setColor(Color.black);
        g.drawLine(x1, y, x2, y);
        g.drawLine(x1, y, x1, d.height);
        g.drawLine(x2, y, x2, d.height);

        g.setColor(Color.red);
        g.drawString(String.format(" %.2fms", upDown.getDuration() / TICKS_PER_MS), x1, (int) (0.5 * d.height));

    }
}
