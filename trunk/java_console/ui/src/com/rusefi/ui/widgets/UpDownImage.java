package com.rusefi.ui.widgets;

import com.irnems.waves.TimeAxisTranslator;
import com.rusefi.waves.WaveReport;
import com.irnems.waves.ZoomProvider;
import com.rusefi.waves.RevolutionLog;

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

    private long lastUpdateTime;
    private ZoomProvider zoomProvider = ZoomProvider.DEFAULT;
    private WaveReport wr;
    private StringBuilder revolutions;
    private final String name;
    private TimeAxisTranslator translator;
    private RevolutionLog time2rpm = RevolutionLog.parseRevolutions(null);

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
        setWaveReport(wr, null);
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
            public int timeToScreen(int time, int width, ZoomProvider zoomProvider) {
                return UpDownImage.this.wr.timeToScreen(time, width, zoomProvider);
            }

            @Override
            public double screenToTime(int screen, int width, ZoomProvider zoomProvider) {
                return UpDownImage.this.wr.screenToTime(screen, width, zoomProvider);
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

    public void setWaveReport(WaveReport wr, StringBuilder revolutions) {
        this.wr = wr;
        this.revolutions = revolutions;
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

        paintScaleLines(g2, d);

        int duration = wr.getDuration();
        g2.setColor(Color.black);

        int line = 0;
        g.drawString(name, 5, ++line * LINE_SIZE);
        g.drawString("Tick length: " + duration + "; count=" + wr.getList().size(), 5, ++line * LINE_SIZE);
        g.drawString("Total seconds: " + (duration / WaveReport.SYS_TICKS_PER_MS / 000.0), 5, ++line * LINE_SIZE);
        g.drawString(FORMAT.format(new Date(lastUpdateTime)), 5, ++line * LINE_SIZE);

        drawStartOfRevolution(g2, d);
    }

    private void drawStartOfRevolution(Graphics2D g2, Dimension d) {
        if (revolutions == null)
            return;

        RevolutionLog time2rpm = RevolutionLog.parseRevolutions(revolutions);

        g2.setStroke(new BasicStroke());
        for (int time : time2rpm.keySet()) {
            int x = translator.timeToScreen(time, d.width, zoomProvider);
            g2.setColor(Color.green);
            g2.drawLine(x, 0, x, d.height);
        }
    }

    private static final BasicStroke LONG_STROKE = new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10.0f,
            new float[]{21.0f, 7.0f}, 0.0f);

    /**
     * This method draws a vertical line every millisecond
     */
    private void paintScaleLines(Graphics2D g2, Dimension d) {
        int fromMs = translator.getMinTime() / WaveReport.mult;
        g2.setStroke(LONG_STROKE);
        g2.setColor(Color.red);

        int toMs = translator.getMaxTime() / WaveReport.mult;
        for (int ms = fromMs; ms <= toMs; ms++) {
            int tick = ms * WaveReport.mult;
            int x = translator.timeToScreen(tick, d.width, zoomProvider);
            g2.drawLine(x, 0, x, d.height);
        }
    }

    private void paintUpDown(Dimension d, WaveReport.UpDown upDown, Graphics g) {

        int x1 = translator.timeToScreen(upDown.upTime, d.width, zoomProvider);
        int x2 = translator.timeToScreen(upDown.downTime, d.width, zoomProvider);

        int y = (int) (0.2 * d.height);

//        g.setColor(Color.cyan);
//        g.fillRect(x1, y, x2 - x1, d.height);

        g.setColor(Color.lightGray);
        g.fillRect(x1, y, x2 - x1, d.height - y);


        g.setColor(Color.blue);
        g.drawLine(x1, y, x2, y);
        g.drawLine(x1, y, x1, d.height);
        g.drawLine(x2, y, x2, d.height);

        g.setColor(Color.red);
        String durationString = String.format(" %.2fms", upDown.getDuration() / WaveReport.SYS_TICKS_PER_MS);

        g.drawString(durationString, x1, (int) (0.5 * d.height));

        g.setColor(Color.darkGray);
        if (upDown.upIndex != -1)
            g.drawString("" + upDown.upIndex, x1, (int) (0.25 * d.height));
        if (upDown.downIndex != -1)
            g.drawString("" + upDown.downIndex, x2, (int) (0.25 * d.height));

        int offset = 3;
        g.setColor(Color.black);
        String fromAngle = time2rpm.getCrankAngleByTimeString(upDown.upTime);
        g.drawString(fromAngle, x1 + offset, (int) (0.75 * d.height));

        g.setColor(Color.green);
        String toAngle = time2rpm.getCrankAngleByTimeString(upDown.downTime);
        g.drawString(toAngle, x1 + offset, (int) (1.0 * d.height));
    }

    public void setRevolutions(StringBuilder revolutions) {
        time2rpm = RevolutionLog.parseRevolutions(revolutions);
    }
}
