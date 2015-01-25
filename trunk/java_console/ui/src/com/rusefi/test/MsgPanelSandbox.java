package com.rusefi.test;

import com.rusefi.ui.FrameHelper;
import com.rusefi.ui.MessagesPanel;

public class MsgPanelSandbox extends FrameHelper {
    private MsgPanelSandbox() {
        showFrame(new MessagesPanel(true).getContent());

    }

    public static void main(String[] args) {

        new MsgPanelSandbox();

    }
}