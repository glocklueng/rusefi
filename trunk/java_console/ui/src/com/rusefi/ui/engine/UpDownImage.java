package com.rusefi.ui.engine;

import com.rusefi.core.Sensor;
import com.rusefi.core.SensorCentral;
import com.rusefi.ui.util.UiUtils;
import com.rusefi.waves.EngineReport;
import com.rusefi.waves.RevolutionLog;
import com.rusefi.waves.TimeAxisTranslator;
import com.rusefi.waves.ZoomProvider;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * This is a renderer of an individual {@link EngineReport} - this makes a simple Logical Analyzer
 * <p/>
 * <p/>
 * Date: 6/23/13
 * (c) Andrey Belomutskiy
 *
 * @see EngineSnifferPanel
 * @see EngineReport
 */
public class UpDownImage extends JPanel {
    private static final SimpleDateFormat FORMAT = new SimpleDateFormat("yyyy-MM-dd'T'hh:mm:ss");
    private static final int LINE_SIZE = 20;
    public static final Color TIME_SCALE_COLOR = Color.red;
    public static final Color ENGINE_CYCLE_COLOR = Color.green;

    private long lastUpdateTime;
    private ZoomProvider zoomProvider = ZoomProvider.DEFAULT;
    private EngineReport wr;
    private StringBuilder revolutions;
    private final String name;
    private TimeAxisTranslator translator;
    private RevolutionLog time2rpm = RevolutionLog.parseRevolutions(null);
    private String pin = "";
    private long mouseEnterTime;
    private Timer repaintTimer = new Timer(1000, new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
            UiUtils.trueRepaint(UpDownImage.this);
        }
    });
    public boolean showText = true;
    private int currentMouseX = -100;

    public UpDownImage(final String name) {
        this(EngineReport.MOCK, name);
        setToolTip();
    }

    public void setToolTip() {
        UiUtils.setTwoLineToolTip(this, "Channel " + NameUtil.getUiName(name), "Physical pin: " + pin);
    }

    public void setZoomProvider(ZoomProvider zoomProvider) {
        this.zoomProvider = zoomProvider;
    }

    public UpDownImage(EngineReport wr, String name) {
        this.name = name;
        setWaveReport(wr, null);
        setOpaque(true);
        translator = createTranslator();
        addMouseMotionListener(new MouseAdapter() {
            @Override
            public void mouseMoved(MouseEvent e) {
                currentMouseX = e.getX();
                UiUtils.trueRepaint(UpDownImage.this);
            }
        });
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                mouseEnterTime = System.currentTimeMillis();
                UiUtils.trueRepaint(UpDownImage.this);
                repaintTimer.restart();
            }
        });
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

    public void setWaveReport(EngineReport wr, StringBuilder revolutions) {
        this.wr = wr;
        propagateDwellIntoSensor(wr);
        this.revolutions = revolutions;
        lastUpdateTime = System.currentTimeMillis();
        UiUtils.trueRepaint(this);
    }

    private void propagateDwellIntoSensor(EngineReport wr) {
        Sensor sensor = NameUtil.name2sensor.get(name);
        if (sensor == null)
            return;

        if (!wr.getList().isEmpty()) {
            EngineReport.UpDown last = wr.getList().get(wr.getList().size() - 1);
            SensorCentral.getInstance().setValue(last.getDuration(), sensor);
        }
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2 = (Graphics2D) g;

        Dimension d = getSize();
        g.setColor(getBackground());
        g.fillRect(0, 0, d.width, d.height);

        for (EngineReport.UpDown upDown : wr.getList())
            paintUpDown(d, upDown, g);

        if (showText)
            paintScaleLines(g2, d);

        int duration = wr.getDuration();
        g2.setColor(Color.black);

        int line = 0;
        boolean justEntered = System.currentTimeMillis() - mouseEnterTime < 1000;
        Font f = getFont();
        if (justEntered) {
            g.setFont(f.deriveFont(Font.BOLD, f.getSize() * 3));
            g.setColor(Color.red);
        }
        if (showText)
            g.drawString(NameUtil.getUiName(name), 5, ++line * LINE_SIZE + (justEntered ? 30 : 0));
        if (justEntered) {
            // revert font & color
            g.setFont(f);
            g.setColor(Color.black);
        }

        if (showText) {
            g.drawString("Tick length: " + duration + "; count=" + wr.getList().size(), 5, ++line * LINE_SIZE);
            g.drawString("Total seconds: " + (duration / EngineReport.SYS_TICKS_PER_MS / 000.0), 5, ++line * LINE_SIZE);
            g.drawString(FORMAT.format(new Date(lastUpdateTime)), 5, ++line * LINE_SIZE);
        }

        drawStartOfRevolution(g2, d);
    }

    private void drawStartOfRevolution(Graphics2D g2, Dimension d) {
        if (revolutions == null)
            return;

        RevolutionLog time2rpm = RevolutionLog.parseRevolutions(revolutions);

        g2.setStroke(new BasicStroke());
        for (int time : time2rpm.keySet()) {
            int x = translator.timeToScreen(time, d.width, zoomProvider);
            g2.setColor(ENGINE_CYCLE_COLOR);
            g2.drawLine(x, 0, x, d.height);
        }
    }

    private static final BasicStroke LONG_STROKE = new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10.0f,
            new float[]{21.0f, 7.0f}, 0.0f);

    /**
     * This method draws a vertical line every millisecond
     */
    private void paintScaleLines(Graphics2D g2, Dimension d) {
        int fromMs = translator.getMinTime() / EngineReport.mult;
        g2.setStroke(LONG_STROKE);
        g2.setColor(TIME_SCALE_COLOR);

        int toMs = translator.getMaxTime() / EngineReport.mult;

        if (toMs - fromMs > d.getWidth() / 5) {
            /**
             * we should not paint time scale lines if the chart is so long that the whole screen would be covered with
             * lines
             * todo: maybe draw scale lines in seconds, not milliseconds?
             */
            return;
        }

        for (int ms = fromMs; ms <= toMs; ms++) {
            int tick = ms * EngineReport.mult;
            int x = translator.timeToScreen(tick, d.width, zoomProvider);
            g2.drawLine(x, 0, x, d.height);
        }
    }

    private void paintUpDown(Dimension d, EngineReport.UpDown upDown, Graphics g) {
        int x1 = translator.timeToScreen(upDown.upTime, d.width, zoomProvider);
        int x2 = translator.timeToScreen(upDown.downTime, d.width, zoomProvider);

        int y = (int) (0.2 * d.height);

        /**
         * signal body
         */
        g.setColor(Color.lightGray);
        g.fillRect(x1, y, x2 - x1, d.height - y);

        /**
         * signal out-line
         */
        g.setColor(Color.blue);
        g.drawLine(x1, y, x2, y);
        g.drawLine(x1, y, x1, d.height);
        g.drawLine(x2, y, x2, d.height);

        g.setColor(Color.red);
        String durationString = String.format(" %.2fms", upDown.getDuration() / EngineReport.SYS_TICKS_PER_MS);

        if (showText) {
            g.drawString(durationString, x1, (int) (0.5 * d.height));

            double fromAngle = time2rpm.getCrankAngleByTime((double) upDown.upTime);
            double toAngle = time2rpm.getCrankAngleByTime((double) upDown.downTime);

            String fromAngleStr = RevolutionLog.angle2string(fromAngle);

            g.setColor(Color.darkGray);
            if (upDown.upIndex != -1) {
                g.drawString("" + upDown.upIndex, x1, (int) (0.25 * d.height));
//            System.out.println("digital_event," + upDown.upIndex + "," + fromAngleStr);
            }
            if (upDown.downIndex != -1) {
                g.drawString("" + upDown.downIndex, x2, (int) (0.25 * d.height));
//            System.out.println("digital_event," + upDown.downIndex + "," + toAngleStr);
            }

            int offset = 3;
            g.setColor(Color.black);
            g.drawString(fromAngleStr, x1 + offset, (int) (0.75 * d.height));

            g.setColor(Color.black);

            if (Math.abs(x1 - currentMouseX) < 5) {
                double angleDuration = toAngle - fromAngle;
                String durationStr = RevolutionLog.angle2string(angleDuration);
                g.drawString(durationStr, x1 + offset, (int) (1.0 * d.height));
            } else {
                String toAngleStr = RevolutionLog.angle2string(toAngle);
                g.drawString(toAngleStr, x1 + offset, (int) (1.0 * d.height));
            }
        }
    }

    public void setRevolutions(StringBuilder revolutions) {
        time2rpm = RevolutionLog.parseRevolutions(revolutions);
    }

    public void setPhysicalPin(String pin) {
        this.pin = pin;
        setToolTip();
    }
}
