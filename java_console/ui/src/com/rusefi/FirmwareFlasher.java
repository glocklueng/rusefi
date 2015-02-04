package com.rusefi;

import javax.swing.*;
import java.awt.*;

/**
 * (c) Andrey Belomutskiy 2013-2015
 * 2/4/15
 */
public class FirmwareFlasher {
    public static boolean isWindows() {
        return System.getProperty("os.name").toLowerCase().contains("win");
    }

    public static Component getContent() {
        return new JLabel("wip");
    }
}
