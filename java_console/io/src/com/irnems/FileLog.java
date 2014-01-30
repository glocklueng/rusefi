package com.irnems;

import org.jetbrains.annotations.Nullable;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 6/30/13
 * (c) Andrey Belomutskiy
 */
public enum FileLog {
    INSTANCE;
    private static final String DIR = "out/";

    @Nullable
    private OutputStream fileLog; // null if not opened yet or already closed

    private FileLog() {
        fileLog = openLog();
    }

    private static FileOutputStream openLog() {
        if (SerialManager.onlyUI)
            return null;
        String date = getDate();
        try {
            createFolderIfNeeded();
            String fileName = DIR + "rfi_report_" + date + ".csv";
            rlog("Writing to " + fileName);
            return new FileOutputStream(fileName, true);
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
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
        if (fileLog == null)
            return;
        try {
            fileLog.write((fullLine + "\r\n").getBytes());
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

    public static void rlog(String msg) {
        System.out.println("r " + msg);
    }
}