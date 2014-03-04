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
    private final static int DEFAULT_PORT = 29001;
    public static final String LOCALHOST = "localhost";
    private final int port;
    private Socket socket;
    private BufferedInputStream stream;
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

    @Override
    public void connect() {
        FileLog.rlog("Connecting to " + port);
        try {
            socket = new Socket(LOCALHOST, port);
            writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            stream = new BufferedInputStream(socket.getInputStream());

            final BufferedReader r = new BufferedReader(new InputStreamReader(stream));

            LinkManager.IO_EXECUTOR.execute(new Runnable() {
                @Override
                public void run() {
                    while (true) {
                        try {
                            String line = r.readLine();
                            LinkManager.engineState.append(line + "\r\n");
                        } catch (IOException e) {
                            System.err.println("End of connection");
                            return;
                        }
                    }
                }
            });

        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
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
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
    }

    public static Collection<? extends String> getAvailablePorts() {
        try {
            Socket s = new Socket(LOCALHOST, DEFAULT_PORT);
            s.close();
            return Collections.singletonList("" + DEFAULT_PORT);
        } catch (IOException e) {
            return Collections.emptyList();
        }
    }
}
