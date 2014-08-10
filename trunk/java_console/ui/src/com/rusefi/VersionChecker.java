package com.rusefi;

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

            }
        }, "version checker");
        t.setDaemon(true);
        t.start();
    }
}
