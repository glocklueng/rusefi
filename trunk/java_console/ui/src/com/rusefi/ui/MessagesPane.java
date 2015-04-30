package com.rusefi.ui;

import ZoeloeSoft.projects.JFontChooser.JFontChooser;
import com.rusefi.Launcher;
import com.rusefi.ui.engine.EngineSnifferPanel;
import com.rusefi.ui.storage.Node;
import com.rusefi.ui.util.URLLabel;
import com.rusefi.ui.widgets.IdleLabel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MessagesPane {
    private static final String HELP_URL = "http://rusefi.com/wiki/index.php?title=Manual:Software:dev_console_commands";

    private final JPanel content = new JPanel(new BorderLayout()) {
        @Override
        public Dimension getPreferredSize() {
            Dimension size = super.getPreferredSize();
            return new Dimension(250, size.height);
        }
    };
    private final JButton fontButton = new JButton("Font");

    public MessagesPane(final Node config) {
        JPanel topPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 5, 0));

        final MessagesPanel upperPanel = new MessagesPanel(config, true);
        upperPanel.loadFont(config);

        JPanel middlePanel = new JPanel(new BorderLayout());
        middlePanel.add(upperPanel.getMessagesScroll(), BorderLayout.CENTER);
        middlePanel.add(new RecentCommands().getContent(), BorderLayout.EAST);

        content.add(middlePanel, BorderLayout.CENTER);

        upperPanel.getButtonPanel().add(new RpmLabel(2).getContent());
        topPanel.add(upperPanel.getButtonPanel());
        topPanel.add(fontButton);
        topPanel.add(new URLLabel(EngineSnifferPanel.HELP_TEXT, HELP_URL));
        content.add(topPanel, BorderLayout.NORTH);

        JPanel statsPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));

        statsPanel.add(new RpmLabel().getContent());
        statsPanel.add(new IdleLabel());
        statsPanel.add(new WarningPanel().getPanel());

        content.add(statsPanel, BorderLayout.SOUTH);

        fontButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFontChooser fc = new JFontChooser(Launcher.getFrame());
                fc.setLocationRelativeTo(fontButton);
                if (fc.showDialog(upperPanel.getFont()) == JFontChooser.OK_OPTION) {
                    upperPanel.setFont(fc.getFont(), config);
                }
            }
        });
    }

    public JComponent getContent() {
        return content;
    }
}