package com.irnems.ui;

import javax.swing.*;
import java.awt.*;

/**
 * 6/30/13
 * (c) Andrey Belomutskiy
 */
public class DefaultExceptionHandler implements Thread.UncaughtExceptionHandler {
    public void uncaughtException(Thread t, Throwable e) {
        // Here you should have a more robust, permanent record of problems
        JOptionPane.showMessageDialog(findActiveFrame(),
                e.toString(), "Exception Occurred", JOptionPane.OK_OPTION);
        e.printStackTrace();
    }

    private static Frame findActiveFrame() {
        Frame[] frames = JFrame.getFrames();
        for (Frame frame : frames) {
            if (frame.isVisible())
                return frame;
        }
        return null;
    }
}
