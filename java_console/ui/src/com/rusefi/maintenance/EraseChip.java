package com.rusefi.maintenance;

import javax.swing.*;
import java.awt.event.ActionEvent;

public class EraseChip extends ProcessStatusWindow {
    private final JButton button = new JButton("Erase Chip");

    private static final String OPEN_OCD_COMMAND = FirmwareFlasher.OPENOCD_BIN +
            " -f interface/stlink-v2.cfg -f board/stm32f4discovery.cfg -c init -c targets -c \"halt\" -c \"flash erase_address 0x08000000 0x080000\" -c shutdown";

    public EraseChip() {
        button.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (JOptionPane.showConfirmDialog(button, "Do you really want to reset stm32 chip?") !=
                        JOptionPane.YES_OPTION)
                    return;
                submitAction(new Runnable() {
                    @Override
                    public void run() {
                        executeCommand(OPEN_OCD_COMMAND);
                    }
                });
            }
        });
    }

    public JButton getButton() {
        return button;
    }
}