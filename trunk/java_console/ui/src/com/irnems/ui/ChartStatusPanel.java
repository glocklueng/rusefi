package com.irnems.ui;

import com.irnems.waves.TimeAxisTranslator;
import com.irnems.waves.WaveReport;
import com.irnems.waves.ZoomProvider;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.MouseMotionListener;

/**
 * Date: 12/26/13
 * Andrey Belomutskiy (c) 2012-2013
 */
public class ChartStatusPanel {
    public final JPanel infoPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 0, 0));
    private final JLabel xLabel = new JLabel();
    private final JLabel timeLabel = new JLabel();
    private TimeAxisTranslator translator = WaveReport.MOCK;

    final MouseMotionAdapter motionAdapter = new MouseMotionAdapter() {
        @Override
        public void mouseMoved(MouseEvent e) {
            int x = e.getX();
            xLabel.setText("" + x);

            double time = translator.screenToTime(x, infoPanel.getWidth(), zoomProvider);
            timeLabel.setText("" + String.format("%.5f sec", time));


        }
    };
    private ZoomProvider zoomProvider;

    public ChartStatusPanel(ZoomProvider zoomProvider) {
        this.zoomProvider = zoomProvider;
        infoPanel.add(new JLabel("X: "));
        infoPanel.add(xLabel);
        infoPanel.add(new JLabel(" time: "));
        infoPanel.add(timeLabel);
    }

    public void setWaveReport(TimeAxisTranslator translator) {
        this.translator = translator;
    }
}
