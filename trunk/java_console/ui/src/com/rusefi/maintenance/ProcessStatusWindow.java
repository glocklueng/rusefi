package com.rusefi.maintenance;

import com.rusefi.ui.StatusWindow;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

/**
 * (c) Andrey Belomutskiy 2013-2016
 */
public class ProcessStatusWindow {
    public static boolean isWindows() {
        return System.getProperty("os.name").toLowerCase().contains("win");
    }

    protected final StatusWindow wnd = new StatusWindow();

    protected static boolean isRunning(Process p) {
        try {
            p.exitValue();
            return false;
        } catch (IllegalThreadStateException e) {
            return true;
        }
    }

    /**
     * This method listens to a data stream from the process, appends messages to UI
     * and accumulates output in a buffer
     */
    protected void startStreamThread(final Process p, final InputStream stream, final StringBuffer buffer) {
        final Thread t = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    BufferedReader bis = new BufferedReader(new InputStreamReader(stream));
                    while (isRunning(p)) {
                        String line = bis.readLine();
                        if (line == null)
                            break;
                        wnd.appendMsg(line);
                        buffer.append(line);
                    }
                } catch (IOException e) {
                    wnd.appendMsg("Stream " + e);
                }
            }
        });
        t.setDaemon(true);
        t.start();
    }

    protected StringBuffer executeCommand(String command) {
        wnd.appendMsg("Executing " + command);
        StringBuffer output = new StringBuffer();
        StringBuffer error = new StringBuffer();
        try {
            Process p = Runtime.getRuntime().exec(command);
            startStreamThread(p, p.getInputStream(), output);
            startStreamThread(p, p.getErrorStream(), error);
            p.waitFor();
        } catch (IOException e) {
            wnd.appendMsg("IOError: " + e);
        } catch (InterruptedException e) {
            wnd.appendMsg("WaitError: " + e);
        }
        return error;
    }

    protected void submitAction(Runnable runnable) {
        Thread thread = new Thread(runnable, "console extProcessThread");
        thread.setDaemon(true);
        thread.start();
    }
}