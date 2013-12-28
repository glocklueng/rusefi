package com.irnems.ui;

import com.irnems.ui.widgets.UpDownImage;
import com.irnems.waves.TimeAxisTranslator;
import com.irnems.waves.WaveReport;
import com.irnems.waves.ZoomProvider;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.MouseMotionListener;
import java.util.Map;
import java.util.TreeMap;

/**
 * Date: 12/26/13
 * Andrey Belomutskiy (c) 2012-2013
 */
public class ChartStatusPanel {
    public final JPanel infoPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 0, 0));
    private final JLabel xLabel = new JLabel();
    private final JLabel timeLabel = new JLabel();
    private final JLabel angleLabel = new JLabel();
    private TimeAxisTranslator translator = WaveReport.MOCK;

    private TreeMap<Integer, Integer> time2rpm = new TreeMap<Integer, Integer>();

    final MouseMotionAdapter motionAdapter = new MouseMotionAdapter() {
        @Override
        public void mouseMoved(MouseEvent event) {
            int x = event.getX();
            xLabel.setText("" + x);

            double time = translator.screenToTime(x, infoPanel.getWidth(), zoomProvider);
            timeLabel.setText("" + String.format("%.5f sec", time));

            Map.Entry<Integer, Integer> entry = time2rpm.floorEntry((int) time);
            if (entry == null) {
                angleLabel.setText("n/a");
            } else {
                double diff = time - entry.getKey();

                Integer rpm = entry.getValue();
                double timeForRevolution = 60000 * WaveReport.SYS_TICKS_PER_MS / rpm;

                double angle = 360.0 * diff / timeForRevolution;

                angleLabel.setText(String.format("%.2f", angle));
            }
        }
    };
    private ZoomProvider zoomProvider;

    public ChartStatusPanel(ZoomProvider zoomProvider) {
        this.zoomProvider = zoomProvider;
        infoPanel.add(new JLabel("X: "));
        infoPanel.add(xLabel);
        infoPanel.add(new JLabel(" time: "));
        infoPanel.add(timeLabel);

        infoPanel.add(new JLabel(" angle: "));
        infoPanel.add(angleLabel);
    }

    public void setWaveReport(TimeAxisTranslator translator) {
        this.translator = translator;
    }

    public void setRevolutions(StringBuilder revolutions) {
        if (revolutions == null) {
            time2rpm.clear();
            return;
        }
        time2rpm = UpDownImage.parseResolutions(revolutions);
    }
}
