package com.rusefi.ui;

import com.rusefi.ui.storage.Node;
import com.rusefi.ui.util.UiUtils;
import com.rusefi.ui.widgets.AnyCommand;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import static com.rusefi.ui.util.LocalizedMessages.CLEAR;
import static com.rusefi.ui.util.LocalizedMessages.PAUSE;

/**
 * This panel displays plain-text 'msg' plain-text debug messages
 * <p/>
 * <p/>
 * Date: 4/27/13
 * (c) Andrey Belomutskiy
 *
 * @see AnyCommand
 */
public class MessagesPanel {
    private static final String FONT_SIZE = "font_size";
    private static final String FONT_NAME = "font_name";

    private final MessagesView messagesView = new MessagesView();

    private final JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 5, 0));

    public MessagesPanel(JComponent extraButton) {
        JPanel middlePanel = new JPanel(new BorderLayout());
        middlePanel.add(messagesView.messagesScroll, BorderLayout.CENTER);
//        buttonPanel.setBorder(BorderFactory.createLineBorder(Color.cyan));

        JButton resetButton = new JButton(CLEAR.getMessage());
        resetButton.setMnemonic('c');
        resetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                messagesView.clear();
            }
        });

        final JButton pauseButton = new JButton(PAUSE.getMessage());
        pauseButton.setMnemonic('p');
        pauseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                messagesView.isPaused = !messagesView.isPaused;
                UiUtils.setPauseButtonText(pauseButton, messagesView.isPaused);
            }
        });

        buttonPanel.add(resetButton);
        buttonPanel.add(pauseButton);
        if (extraButton != null)
            buttonPanel.add(extraButton);
    }

    public JPanel getButtonPanel() {
        return buttonPanel;
    }

    public JScrollPane getMessagesScroll() {
        return messagesView.messagesScroll;
    }

    public Font getFont() {
        return messagesView.messages.getFont();
    }

    public void setFont(Font font, Node config) {
        messagesView.messages.setFont(font);
        config.setProperty(FONT_SIZE, font.getSize());
        config.setProperty(FONT_NAME, font.getName());
    }

    public void loadFont(Node config) {
        Font f = getFont();
        int size = config.getIntProperty(FONT_SIZE, f.getSize());
        String name = config.getProperty(FONT_NAME, f.getName());
        setFont(new Font(f.getName(), f.getStyle(), size), config);
    }
}
