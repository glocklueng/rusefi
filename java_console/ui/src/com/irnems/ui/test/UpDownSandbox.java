package com.irnems.ui.test;

import com.irnems.waves.WaveReport;
import com.irnems.core.test.WaveReportTest;
import com.irnems.ui.FrameHelper;
import com.irnems.ui.widgets.UpDownImage;

import javax.swing.*;
import java.lang.reflect.InvocationTargetException;

/**
 * Date: 6/23/13
 * (c) Andrey Belomutskiy
 */
public class UpDownSandbox extends FrameHelper {

    public UpDownSandbox() {

        WaveReport wr = new WaveReport(WaveReportTest.report);

        showFrame(new UpDownImage(wr, "test"));

    }

    public static void main(String[] args) throws InvocationTargetException, InterruptedException {
        SwingUtilities.invokeAndWait(new Runnable() {
            @Override
            public void run() {
                new UpDownSandbox();
            }
        });
    }
}
