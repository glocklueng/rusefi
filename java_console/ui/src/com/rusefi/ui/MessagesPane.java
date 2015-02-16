package com.rusefi.ui;

import com.rusefi.ui.storage.Node;
import com.rusefi.ui.widgets.IdleLabel;

import javax.swing.*;
import java.awt.*;

public class MessagesPane {
    private final JPanel content = new JPanel(new BorderLayout()) {
        @Override
        public Dimension getPreferredSize() {
            Dimension size = super.getPreferredSize();
            return new Dimension(250, size.height);
        }
    };

    public MessagesPane(Node config) {
        MessagesPanel messagesPanel = new MessagesPanel(config);
        content.setBorder(BorderFactory.createLineBorder(Color.red));

        JPanel middlePanel = new JPanel(new BorderLayout());
        middlePanel.add(messagesPanel.getMessagesScroll(), BorderLayout.CENTER);
        middlePanel.add(new RecentCommands().getContent(), BorderLayout.EAST);

        content.add(middlePanel, BorderLayout.CENTER);

        messagesPanel.getButtonPanel().add(new RpmLabel().getContent());
        content.add(messagesPanel.getButtonPanel(), BorderLayout.NORTH);

        JPanel statsPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));

        statsPanel.add(new RpmLabel().getContent());
        statsPanel.add(new IdleLabel());
        statsPanel.add(new WarningPanel().getPanel());

        content.add(statsPanel, BorderLayout.SOUTH);
    }

    public JComponent getContent() {
        return content;
    }
}