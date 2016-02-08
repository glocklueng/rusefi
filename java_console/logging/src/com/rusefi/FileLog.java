package com.rusefi;

import org.jetbrains.annotations.Nullable;

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 6/30/13
 * (c) Andrey Belomutskiy
 */
public enum FileLog {
    MAIN,
    SIMULATOR_CONSOLE;

    public static final String DIR = "out/";
    public static String currentLogName;
    public static final String END_OF_TIMESTAND_TAG = "<EOT>: ";
    public static final Logger LOGGER = new Logger() {
        @Override
        public void trace(String msg) {
        }

        @Override
        public void info(String msg) {
            MAIN.logLine(msg);
        }

        @Override
        public void error(String msg) {
            MAIN.logLine(msg);
        }
    };

    @Nullable
    private OutputStream fileLog; // null if not opened yet or already closed

    FileLog() {
    }

    public void start() {
        if (fileLog != null)
            return;
        try {
            fileLog = openLog();
        } catch (FileNotFoundException e) {
            throw new IllegalStateException(e);
        }
    }

    private FileOutputStream openLog() throws FileNotFoundException {
        String date = getDate();
        createFolderIfNeeded();
        currentLogName = name() + "_rfi_report_" + date + ".csv";
        String fileName = DIR + currentLogName;
        rlog("Writing to " + fileName);
        return new FileOutputStream(fileName, true);
    }

    private static void createFolderIfNeeded() {
        File dir = new File(DIR);
        if (dir.exists())
            return;
        boolean created = dir.mkdirs();
        if (!created)
            throw new IllegalStateException("Failed to create " + DIR + " folder");
    }

    public static String getDate() {
        return new SimpleDateFormat("yyyy-MM-dd HH_mm").format(new Date());
    }

    public synchronized void logLine(String fullLine) {
        System.out.println(fullLine);
        if (fileLog == null)
            return;
        try {
            fileLog.write((new Date() + END_OF_TIMESTAND_TAG + fullLine + "\r\n").getBytes());
            fileLog.flush();
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }

    }

    public synchronized void close() {
        if (fileLog == null)
            return; // already closed
        try {
            rlog("Closing file...");
            fileLog.close();
            fileLog = null;
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }

    private static void rlog(String msg) {
        System.out.println("rlog " + msg);
    }

    public void log(IllegalStateException exception) {
        if (fileLog == null)
            throw new NullPointerException("fileLog");
        OutputStreamWriter os = new OutputStreamWriter(fileLog);
        exception.printStackTrace(new PrintWriter(os));
    }

    public void logException(String msg, Throwable e) {
        logLine(msg + e);
        e.printStackTrace();
    }
}