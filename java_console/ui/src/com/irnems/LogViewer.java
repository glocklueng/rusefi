package com.irnems;

import com.irnems.core.EngineState;
import com.irnems.file.FileUtils;
import com.irnems.ui.FrameHelper;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * 7/27/13
 * (c) Andrey Belomutskiy
 */
public class LogViewer extends FrameHelper {

    int currentChartIndex = 0;

    private LogViewer() {

        JPanel upperPanel = new JPanel(new FlowLayout());


        JButton next = new JButton("next");
        next.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                currentChartIndex++;
                refreshChart();

            }
        });

        upperPanel.add(next);


        refreshChart();

    }

    private void refreshChart() {
        String chart = ChartRepository.getInstance().getChart(currentChartIndex);
    }

    public static void main(String[] args) {
        String filename = "a.csv";

        EngineState.EngineStateListener listener = new EngineState.EngineStateListenerImpl() {
        };

        EngineState engineState = new EngineState(listener);
        engineState.registerStringValueAction("wave_chart", new EngineState.ValueCallback<String>() {
            @Override
            public void onUpdate(String value) {
                FileLog.rlog("chart " + value);

                ChartRepository.getInstance().addChart(value);

            }
        });
        FileUtils.readFile2(filename, engineState);

    }
}
