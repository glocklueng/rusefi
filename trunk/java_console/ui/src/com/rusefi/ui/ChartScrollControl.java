package com.rusefi.ui;

import com.rusefi.KeyStrokeShortcut;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * 4/7/14
 * (c) Andrey Belomutskiy
 */
public class ChartScrollControl {
    private final JPanel content = new JPanel(new FlowLayout(FlowLayout.RIGHT, 5, 0));
    private final AtomicInteger index = new AtomicInteger();
    private static final JLabel info = new JLabel();
    private ChartRepository.CRListener listener;

    public ChartScrollControl(final ChartRepository.CRListener listener) {

        this.listener = listener;

        content.setBorder(BorderFactory.createLineBorder(Color.red));

        setInfoText(index);

        JButton prev = new JButton("<");
        prev.setToolTipText("Previous page");
        prev.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                previousPage();
            }
        });


        JButton next = new JButton(">");
        next.setToolTipText("Next page");
        next.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                nextPage();
            }
        });

        content.add(prev);
        content.add(info);
        content.add(next);

        bindKeyStrokeActions();
    }

    private void previousPage() {
        if (index.intValue() > 0) {
            index.decrementAndGet();
            showChart();
        } else if (index.intValue() == 0) {
            // let's go to the last chart if chart repository is not empty
            if (ChartRepository.getInstance().getSize() > 0)
                index.set(ChartRepository.getInstance().getSize() - 1);
            showChart();
        }
    }

    private void showChart() {
        listener.onDigitalChart(ChartRepository.getInstance().getChart(index.get()));
        setInfoText(index);
    }

    private void nextPage() {
        if (index.intValue() < ChartRepository.getInstance().getSize() - 1) {
            index.incrementAndGet();
            showChart();
        }
    }

    private void bindKeyStrokeActions() {
        InputMap inputMap = content.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);

        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, 0), KeyStrokeShortcut.PREVIOUS_PAGE);
        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, 0), KeyStrokeShortcut.NEXT_PAGE);

        content.getActionMap().put(KeyStrokeShortcut.PREVIOUS_PAGE, new AbstractAction() {
            public void actionPerformed(ActionEvent event) {
                previousPage();
            }
        });
        content.getActionMap().put(KeyStrokeShortcut.NEXT_PAGE, new AbstractAction() {
            public void actionPerformed(ActionEvent event) {
                nextPage();
            }
        });
    }

    public JPanel getContent() {
        return content;
    }

    private void setInfoText(AtomicInteger index) {
        info.setText(index.get() + "/" + ChartRepository.getInstance().getSize());
    }

    public void reset() {
        index.set(0);
        setInfoText(index);
    }
}

