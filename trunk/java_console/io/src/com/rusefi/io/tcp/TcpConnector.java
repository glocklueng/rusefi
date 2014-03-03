package com.rusefi.io.tcp;

import com.irnems.FileLog;
import com.rusefi.io.LinkConnector;

import java.io.IOException;
import java.net.Socket;
import java.net.URLConnection;
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

        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }

    @Override
    public void restart() {
        FileLog.rlog("Restarting on " + port);
    }

    @Override
    public void send(String command) throws InterruptedException {
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
