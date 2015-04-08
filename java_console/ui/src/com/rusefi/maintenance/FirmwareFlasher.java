package com.rusefi.maintenance;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;

/**
 * (c) Andrey Belomutskiy 2013-2015
 * 2/4/15
 */
public class FirmwareFlasher extends ProcessStatusWindow {
    public static final String IMAGE_DEBUG_FILE = "rusefi_debug.bin";
    public static final String IMAGE_RELEASE_FILE = "rusefi_release.bin";
    static final String OPENOCD_BIN = "openocd/bin/openocd-0.8.0.exe";
    private static final String SUCCESS_MESSAGE_TAG = "shutdown command invoked";
    private static final String FAILED_MESSAGE_TAG = "failed";

    private final JButton button;
    private String fileName;

    public FirmwareFlasher(String fileName, String buttonTest) {
        this.fileName = fileName;
        button = new JButton(buttonTest);
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                int dialogResult = JOptionPane.showConfirmDialog(button, "Do you really want to update firmware? Please disconnect battery before erasing.",
                        "Please disconnect from vehicle", JOptionPane.YES_NO_OPTION);
                if (dialogResult != JOptionPane.YES_OPTION)
                    return;


                wnd.showFrame("rusEfi Firmware Flasher");

                Runnable runnable = new Runnable() {
                    @Override
                    public void run() {
                        doFlashFirmware();
                    }
                };
                submitAction(runnable);
            }
        });
    }

    private void doFlashFirmware() {
        if (!new File(fileName).exists()) {
            wnd.appendMsg(fileName + " not found, cannot proceed !!!");
            return;
        }
        StringBuffer error = executeCommand(OPENOCD_BIN + " -f interface/stlink-v2.cfg -f board/stm32f4discovery.cfg -c \"program " +
                fileName +
                " verify reset exit 0x08000000\"");
        if (error.toString().contains(SUCCESS_MESSAGE_TAG) && !error.toString().contains(FAILED_MESSAGE_TAG)) {
            wnd.appendMsg("!!! Looks good!!!");
        } else {
            wnd.appendMsg("!!! FIRMWARE FLASH: DOES NOT LOOK RIGHT !!!");
        }
    }

    public JButton getButton() {
        return button;
    }

}