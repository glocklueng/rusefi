package com.rusefi.ui;

import javax.swing.*;
import java.awt.*;

/**
 * (c) Andrey Belomutskiy
 * 2/9/2016
 */
public class GaugesGrid {
    public final JPanel panel;
    public GaugesGrid(int rows, int cols) {
        panel = new JPanel(new GridLayout(rows, cols));
    }
}
