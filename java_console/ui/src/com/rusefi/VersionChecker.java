package com.rusefi;

import com.irnems.FileLog;

import java.io.IOException;
import java.net.URL;
import java.util.Scanner;

/**
 * This class checks the recommended versions numbers and compares them with current versions
 * <p/>
 * (c) Andrey Belomutskiy
 * 8/10/14
 */
public class VersionChecker {
    private static final String VERSIONS_URL = "http://rusefi.com/console/versions.txt";

    public static void start() {
        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {

                try {
                    URL url = new URL(VERSIONS_URL);
                    Scanner s = new Scanner(url.openStream());

                    FileLog.MAIN.logLine("Reading from " + VERSIONS_URL);
                    String s1 = s.next();
                    String s2 = s.next();

                    System.out.println("s1: " + s1);
                    System.out.println("s2: " + s2);

                } catch (IOException e) {
                    e.printStackTrace();
                    FileLog.MAIN.logLine("Failed to read from " + VERSIONS_URL);
                }
            }
        }, "version checker");
        t.setDaemon(true);
        t.start();
    }
}
