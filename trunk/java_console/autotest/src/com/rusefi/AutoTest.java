package com.rusefi;


import com.irnems.FileLog;
import com.rusefi.io.tcp.TcpConnector;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadFactory;

/**
 * rusEfi firmware simulator functional test suite
 *
 * @author Andrey Belomutskiy
 *         3/5/14
 */
public class AutoTest {
    private static final String SIMULATOR_COMMAND = "../win32_functional_tests/rusefi_simulator.exe";

    private static final Executor e = Executors.newFixedThreadPool(10, new ThreadFactory() {
        @Override
        public Thread newThread(Runnable r) {
            Thread t = Executors.defaultThreadFactory().newThread(r);
            t.setDaemon(true);
            return t;
        }
    });

    public static void main(String[] args) throws InterruptedException {
        if (!TcpConnector.getAvailablePorts().isEmpty())
            throw new IllegalStateException("Port already binded on startup?");

        e.execute(new Runnable() {
            @Override
            public void run() {
                startSimulator();
            }
        });


        FileLog.rlog("Waiting for TCP port...");
        for (int i = 0; i < 180; i++) {
            if (!TcpConnector.getAvailablePorts().isEmpty())
                break;
            Thread.sleep(1000);
        }
        if (TcpConnector.getAvailablePorts().isEmpty())
            throw new IllegalStateException("Did we start it?");

        FileLog.rlog("Got a TCP port! Connecting...");

    }

    private static void startSimulator() {
        try {
            String line;
            FileLog.rlog("Executing " + SIMULATOR_COMMAND);
            Process p = Runtime.getRuntime().exec(SIMULATOR_COMMAND);
            BufferedReader input =
                    new BufferedReader
                            (new InputStreamReader(p.getInputStream()));
            while ((line = input.readLine()) != null) {
                System.out.println("from console: " + line);
            }
            input.close();
        } catch (Exception err) {
            err.printStackTrace();
        }
    }
}
