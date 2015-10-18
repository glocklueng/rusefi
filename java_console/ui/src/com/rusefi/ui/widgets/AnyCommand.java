package com.rusefi.ui.widgets;

import com.rusefi.io.CommandQueue;
import com.rusefi.ui.RecentCommands;
import com.rusefi.ui.storage.Node;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.JTextComponent;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Date: 3/20/13
 * (c) Andrey Belomutskiy
 */
public class AnyCommand {
    public static final String KEY = "last_value";

    private final JTextComponent text;
    private JPanel content = new JPanel(new FlowLayout(FlowLayout.LEFT));
    private boolean reentrant;
    private Listener listener;

    private AnyCommand(final JTextComponent text, final Node config, String defaultCommand, final boolean listenToCommands, boolean withCommandCaption) {
        this.text = text;
        text.setText(defaultCommand);
        content.setBorder(BorderFactory.createLineBorder(Color.PINK));
        if (withCommandCaption) {
            content.add(new JLabel("Command: "));
        }
        content.add(text);
        JButton go = new JButton("Go");
        go.setContentAreaFilled(false);
        go.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                send();
            }
        });
        content.add(go);

        CommandQueue.getInstance().addListener(new CommandQueue.CommandQueueListener() {
            @Override
            public void onCommand(String command) {
                if (listenToCommands && !reentrant)
                    text.setText(command);
            }
        });

        text.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                changedUpdate(null);
            }

            @Override
            public void removeUpdate(DocumentEvent e) {

            }

            @Override
            public void changedUpdate(DocumentEvent e) {
                boolean isOk = isValidInput(text.getText());
                text.setBorder(isOk ? null : BorderFactory.createLineBorder(Color.red));
                config.setProperty(KEY, text.getText());
            }
        });

//        text.setInputVerifier(new InputVerifier() {
//            @Override
//            public boolean verify(JComponent input) {
//                boolean isOk = isValidInput(text);
//                text.setBorder(isOk ? null : BorderFactory.createLineBorder(Color.red));
//                return isOk;
//            }
//        });
        // todo: limit the length of text in the text field
    }

    private void send() {
        String cmd = text.getText();
        for (String s : cmd.split("\n"))
            doSend(s);
    }

    private void doSend(String cmd) {
        if (!isValidInput(cmd))
            return;
        if (listener != null)
            listener.onSend();
        int timeout = CommandQueue.getTimeout(cmd);
        reentrant = true;
        CommandQueue.getInstance().write(cmd.toLowerCase(), timeout);
        reentrant = false;
    }

    private static boolean isValidInput(String text) {
        boolean isOk = true;
        for (char c : text.toCharArray()) {
            if (c > 127) {
                /**
                 * https://sourceforge.net/p/rusefi/tickets/63/
                 * only English characters are accepted - we need to reject two-byte unicode stuff
                 */
                isOk = false;
                break;
            }
        }
        return isOk;
    }

    public JComponent getContent() {
        return content;
    }

    public void setContent(JPanel content) {
        this.content = content;
    }

    interface Listener {
        void onSend();
    }

    public static AnyCommand createField(Node config, boolean listenToCommands, boolean withCommandCaption) {
        return createField(config, config.getProperty(KEY), listenToCommands, withCommandCaption);
    }

    public static AnyCommand createField(Node config, String defaultCommand, boolean listenToCommands, boolean withCommandCaption) {
        final JTextField text = new JTextField() {
            @Override
            public Dimension getPreferredSize() {
                Dimension size = super.getPreferredSize();
                return new Dimension(200, size.height);
            }
        };

        final AnyCommand command = new AnyCommand(text, config, defaultCommand, listenToCommands, withCommandCaption);
        text.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                command.send();
            }
        });

        final AtomicInteger index = new AtomicInteger();
        command.listener = new Listener() {
            @Override
            public void onSend() {
                index.set(0);
            }
        };

        text.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_UP) {
                    String command = RecentCommands.getRecent(index.incrementAndGet());
                    text.setText(command);
                } else if (e.getKeyCode() == KeyEvent.VK_DOWN) {
                    String command = RecentCommands.getRecent(index.decrementAndGet());
                    text.setText(command);
                }
            }
        });

        return command;
    }

    public static AnyCommand createArea(Node config, String defaultCommand, boolean listenToCommands, boolean withCommandCaption) {
        final JTextArea text = new JTextArea(3, 20) {
            @Override
            public Dimension getPreferredSize() {
                Dimension size = super.getPreferredSize();
                return new Dimension(200, size.height);
            }
        };
//        text.setMax

        return new AnyCommand(text, config, defaultCommand, listenToCommands, withCommandCaption);
    }
}
