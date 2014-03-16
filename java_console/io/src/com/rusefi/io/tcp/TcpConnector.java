package com.rusefi.io.tcp;

import com.irnems.FileLog;
import com.rusefi.io.LinkConnector;
import com.rusefi.io.LinkManager;

import java.io.*;
import java.net.Socket;
import java.util.Collection;
import java.util.Collections;

/**
 * @author Andrey Belomutskiy
 *         3/3/14
 */
public class TcpConnector implements LinkConnector {
    public final static int DEFAULT_PORT = 29001;
    public static final String LOCALHOST = "localhost";
    private final int port;
    private BufferedWriter writer;

    public TcpConnector(String port) {
        this.port = getTcpPort(port);
    }

    public static boolean isTcpPort(String port) {
        try {
            getTcpPort(port);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static int getTcpPort(String port) {
        return Integer.parseInt(port);
    }

    /**
     * this implementation is blocking
     */
    @Override
    public void connect() {
        FileLog.rlog("Connecting to " + port);
        BufferedInputStream stream;
        try {
            Socket socket = new Socket(LOCALHOST, port);
            writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            stream = new BufferedInputStream(socket.getInputStream());
        } catch (IOException e) {
            throw new IllegalStateException("Failed to connect to simulator", e);
        }

        final BufferedReader reader = new BufferedReader(new InputStreamReader(stream));

        LinkManager.IO_EXECUTOR.execute(new Runnable() {
            @Override
            public void run() {
                Thread.currentThread().setName("TCP connector loop");
                FileLog.rlog("Running TCP connection loop");
                while (true) {
                    try {
                        String line = reader.readLine();
                        LinkManager.engineState.append(line + "\r\n");
                    } catch (IOException e) {
                        System.err.println("End of connection");
                        return;
                    }
                }
            }
        });

    }

    @Override
    public void restart() {
//        FileLog.rlog("Restarting on " + port);
    }

    @Override
    public void send(String command) throws InterruptedException {
        FileLog.rlog("Writing " + command);
        try {
            writer.write(command + "\r\n");
            writer.flush();
        } catch (IOException e) {
            System.err.println("err in send");
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
    }

    public static Collection<? extends String> getAvailablePorts() {
        try {
            Socket s = new Socket(LOCALHOST, DEFAULT_PORT);
            s.close();
            return Collections.singletonList("" + DEFAULT_PORT);
        } catch (IOException e) {
            System.out.println("Connection refused in getAvailablePorts(): simulator not running");
            return Collections.emptyList();
        }
    }
}
