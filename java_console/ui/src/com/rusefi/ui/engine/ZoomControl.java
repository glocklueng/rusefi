package com.rusefi.ui.engine;

import com.rusefi.waves.ZoomProvider;
import com.rusefi.KeyStrokeShortcut;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

/**
 * 7/7/13
 * (c) Andrey Belomutskiy
 */
class ZoomControl extends JPanel {
//    private final JLabel currentValue = new JLabel();
    private double value;
    public ZoomControlListener listener = null;
    private final JButton resetZoom = new JButton("*");

    ZoomProvider zoomProvider = new ZoomProvider() {
        @Override
        public double getZoomValue() {
            return value;
        }

        public String toString() {
            return "zoom " + value;
        }
    };

    public ZoomControl() {
        super(new FlowLayout());
        setValue(1);

//        final JTextField text = new JTextField() {
//            @Override
//            public Dimension getPreferredSize() {
//                Dimension size = super.getPreferredSize();
//                return new Dimension(200, size.height);
//            }
//        };

//        add(currentValue);

        JButton plus = new JButton("+");
        plus.setMnemonic('z');
        plus.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                zoomIn();
            }
        });
        plus.setToolTipText("Zoom in");
        add(plus);

        resetZoom.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                setValue(1);
            }
        });
        resetZoom.setToolTipText("Reset zoom");
        add(resetZoom);

        JButton minus = new JButton("-");
        plus.setMnemonic('x');
        minus.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                zoomOut();
            }
        });
        minus.setToolTipText("Zoom out");
        add(minus);

        bindKeyStrokeActions();
    }

    private void bindKeyStrokeActions() {
        InputMap inputMap = getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);

        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_ADD, 0), KeyStrokeShortcut.ZOOM_IN);
        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_SUBTRACT, 0), KeyStrokeShortcut.ZOOM_OUT);

        getActionMap().put(KeyStrokeShortcut.ZOOM_IN, new AbstractAction() {
            public void actionPerformed(ActionEvent event) {
                zoomIn();
            }
        });

        getActionMap().put(KeyStrokeShortcut.ZOOM_OUT, new AbstractAction() {
            public void actionPerformed(ActionEvent event) {
                zoomOut();
            }
        });
    }

    private void zoomIn() {
        setValue(value * 1.1);
    }

    private void zoomOut() {
        setValue(value / 1.1);
    }

    private void setValue(double value) {
        this.value = value;
        //currentValue.setText(String.format(" %.4fms", value));
        resetZoom.setEnabled(Math.abs(1 - value) > 0.01);
        if (listener != null)
            listener.onZoomChange();
    }

    public ZoomProvider getZoomProvider() {
        return zoomProvider;
    }

    interface ZoomControlListener {
        void onZoomChange();
    }
}
