package com.irnems.ui;

import com.irnems.FileLog;

import javax.swing.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * Date: 3/24/13
 * (c) Andrey Belomutskiy
 */
public class FrameHelper {

    protected void showFrame(JComponent container) {
        final JFrame f = new JFrame();
        f.setSize(800, 500);
        f.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
        f.addWindowListener(new WindowAdapter() {
            @Override
            public void windowOpened(WindowEvent e) {
                onWindowOpened();
                f.setExtendedState(f.getExtendedState() | JFrame.MAXIMIZED_BOTH);
            }

            @Override
            public void windowClosed(WindowEvent ev) {
                onWindowClosed();
            }
        });
        f.add(container);
        f.setVisible(true);
    }

    protected void onWindowOpened() {
        System.out.println("onWindowOpened");
    }

    protected void onWindowClosed() {
        System.out.println("onWindowClosed");
        FileLog.INSTANCE.close();
    }
}
