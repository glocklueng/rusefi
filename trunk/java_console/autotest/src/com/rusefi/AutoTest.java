package com.rusefi;


import com.irnems.FileLog;
import com.irnems.core.Sensor;
import com.irnems.core.SensorCentral;
import com.rusefi.io.CommandQueue;
import com.rusefi.io.LinkManager;
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
    private static final String SIMULATOR_COMMAND = "../win32_functional_tests/build/rusefi_simulator.exe";
    private static final int SECOND = 1000;
    private static Process simulatorProcess;

    private static final Executor e = Executors.newFixedThreadPool(10, new ThreadFactory() {
        @Override
        public Thread newThread(Runnable r) {
            Thread t = Executors.defaultThreadFactory().newThread(r);
            t.setDaemon(true);
            return t;
        }
    });

    public static void main(String[] args) throws InterruptedException {
        try {
            runTest();
        } finally {
            if (simulatorProcess != null) {
                FileLog.rlog("Destroying subprocess...");
                simulatorProcess.destroy();
            }
        }
    }

    private static void runTest() throws InterruptedException {
        if (!TcpConnector.getAvailablePorts().isEmpty())
            throw new IllegalStateException("Port already binded on startup?");

        e.execute(new Runnable() {
            @Override
            public void run() {
                startSimulator();
            }
        });


//        FileLog.rlog("Waiting for TCP port...");
//        for (int i = 0; i < 180; i++) {
//            if (!TcpConnector.getAvailablePorts().isEmpty())
//                break;
//            Thread.sleep(1000);
//        }
//        if (TcpConnector.getAvailablePorts().isEmpty())
//            throw new IllegalStateException("Did we start it?");
//        /**
//         * If we open a connection just to validate that the process has started, we are getting
//         * weird issues with the second - actual connection
//         */
//        FileLog.rlog("Time for simulator to close the port...");
//        Thread.sleep(3000);
//
//        FileLog.rlog("Got a TCP port! Connecting...");
        LinkManager.start("" + TcpConnector.DEFAULT_PORT);
        /**
         * TCP connector is blocking
         */
        LinkManager.open();

        FileLog.rlog("Let's give it some time to start...");
        Thread.sleep(5000); // let's give it some time to start

        CommandQueue.getInstance().write("rpm 500", CommandQueue.DEFAULT_TIMEOUT);

        SensorCentral.getInstance().getValue(Sensor.RPM);

        Thread.sleep(10 * SECOND);


        Thread.sleep(60 * 1000);
    }

    private static void startSimulator() {
        Thread.currentThread().setName("Main simulation");

        try {
            String line;
            FileLog.rlog("Executing " + SIMULATOR_COMMAND);
            simulatorProcess = Runtime.getRuntime().exec(SIMULATOR_COMMAND);
            BufferedReader input =
                    new BufferedReader
                            (new InputStreamReader(simulatorProcess.getInputStream()));
            while ((line = input.readLine()) != null) {
                System.out.println("from console: " + line);
            }
            System.out.println("end of console");
            input.close();
        } catch (Exception err) {
            err.printStackTrace();
        }
    }
}
