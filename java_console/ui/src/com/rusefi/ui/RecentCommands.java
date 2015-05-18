package com.rusefi.ui;

import com.rusefi.io.CommandQueue;
import com.rusefi.ui.util.UiUtils;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

import static com.rusefi.ui.storage.PersistentConfiguration.getConfig;

/**
 * This UI element displays an array of buttons, each for one of the recently used commands
 */

public class RecentCommands {
    private final static int NUMBER_OF_COMMANDS = 40;
    private static final String KEY = "recent_commands";
    private static final String DELIMETER = "|";
    private static final String STOPENGINE = "stopengine";
    private static final String SHOWCONFIG = "showconfig";
    private static final String HELP = "help";
    private static final String ANALOGINFO = "analoginfo";
    private static final String TRIGGERINFO = "triggerinfo";
    private static final String IDLEINFO = "idleinfo";
    private static final String ALTINFO = "altinfo";
    private static final String ACCELINFO = "accelinfo";
    private static final String TSINFO = "tsinfo";

    private final static Map<String, Icon> COMMAND_ICONS = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);

    static {
        COMMAND_ICONS.put(STOPENGINE, UiUtils.loadIcon("stop.jpg"));
        ImageIcon infoIcon = UiUtils.loadIcon("info.png");
        COMMAND_ICONS.put(SHOWCONFIG, infoIcon);
        COMMAND_ICONS.put(HELP, infoIcon);
        COMMAND_ICONS.put(ANALOGINFO, infoIcon);
        COMMAND_ICONS.put(TRIGGERINFO, infoIcon);
        COMMAND_ICONS.put(IDLEINFO, infoIcon);
        COMMAND_ICONS.put(ALTINFO, infoIcon);
        COMMAND_ICONS.put(ACCELINFO, infoIcon);
        COMMAND_ICONS.put(TSINFO, infoIcon);
    }

    private final JPanel content = new JPanel(new GridLayout(NUMBER_OF_COMMANDS + 1, 1));

    private static final LinkedHashMap<Entry, Object> entries = new LinkedHashMap<Entry, Object>() {
        @Override
        protected boolean removeEldestEntry(Map.Entry<Entry, Object> eldest) {
            return size() > NUMBER_OF_COMMANDS;
        }
    };

    private final AtomicBoolean reentrant = new AtomicBoolean();

    private final JScrollPane messagesScroll = new JScrollPane(content, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

    public RecentCommands() {
        CommandQueue.getInstance().addListener(new CommandQueue.CommandQueueListener() {
            @Override
            public void onCommand(String command) {
                if (!reentrant.get())
                    add(command);
            }
        });

        String value = getConfig().getRoot().getProperty(KEY, null);

        if (value != null && value.trim().length() > 5) {
            unpack(value);
        } else {
            addDefaults();
        }
    }

    private void unpack(String value) {
        entries.clear();
        for (String command : value.split("\\" + DELIMETER))
            add(command);
    }

    private void addDefaults() {
        add(HELP);
        add(SHOWCONFIG);
        add(STOPENGINE);
        add(ANALOGINFO);
        add(TRIGGERINFO);
        add(TSINFO);
        add("writeconfig");
        add("rewriteconfig");
        add("enable injection");
        add("disable injection");
        add("enable ignition");
        add("disable ignition");

        add("enable self_stimulation");
        add("disable self_stimulation");

        add("set_idle_position 50");
        add("sparkbench 5 400 2");
        add("fuelbench 5 400 2");
        add(IDLEINFO);
        add(ALTINFO);
        add(ACCELINFO);
    }

    public void add(String command) {
        synchronized (entries) {
            entries.put(new Entry(command), null);
        }

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                content.removeAll();
                JButton reset = new JButton(UiUtils.loadIcon("undo.jpg"));
                reset.setContentAreaFilled(false);
                reset.setFocusPainted(false);
                reset.setBorder(BorderFactory.createEmptyBorder());
                content.add(UiUtils.wrap(reset));
                reset.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        entries.clear();
                        addDefaults();
                    }
                });

                synchronized (entries) {
                    Set<Entry> sorted = new TreeSet<>();
                    sorted.addAll(entries.keySet());

                    for (Entry entry : sorted) {
                        content.add(createButton(reentrant, entry.command));
                    }
                }
                UiUtils.trueRepaint(content.getParent());
                UiUtils.trueLayout(content.getParent());
            }
        });
        getConfig().getRoot().setProperty(KEY, pack());
    }

    public static JComponent createButton(final AtomicBoolean reentrant, final String command) {
        JButton button = new JButton(command);
        Icon icon = COMMAND_ICONS.get(command);
        if (icon != null)
            button.setIcon(icon);
        button.setBorder(BorderFactory.createEmptyBorder(3, 5, 0, 5));

        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                reentrant.set(true);
                int timeout = CommandQueue.getTimeout(command);
                CommandQueue.getInstance().write(command, timeout);
                reentrant.set(false);
            }
        });

        return UiUtils.wrap(button);
    }

    public Component getContent() {
        return messagesScroll;
    }

    public String pack() {
        StringBuilder sb = new StringBuilder();
        for (Entry command : entries.keySet()) {
            if (sb.length() != 0)
                sb.append(DELIMETER);
            sb.append(command.command);
        }
        return sb.toString();
    }

    static class Entry implements Comparable<Entry> {
        private final String command;

        Entry(String command) {
            this.command = command;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            Entry entry = (Entry) o;

            return !(command != null ? !command.equals(entry.command) : entry.command != null);

        }

        @Override
        public int hashCode() {
            return command != null ? command.hashCode() : 0;
        }

        @Override
        public String toString() {
            return "{" +
                    "command='" + command + '\'' +
                    '}';
        }

        @Override
        public int compareTo(Entry o) {
            return command.compareTo(o.command);
        }
    }

    public static String getRecent(int index) {
        List<Entry> elements;
        index = Math.max(0, index);
        synchronized (entries) {
            elements = new ArrayList<>(entries.keySet());
        }
        if (index >= elements.size())
            return elements.get(0).command;
        return elements.get(elements.size() - 1 - index).command;
    }
}