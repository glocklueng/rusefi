package com.rusefi.io;

import com.rusefi.FileLog;
import com.rusefi.core.EngineState;
import com.rusefi.io.serial.SerialConnector;
import com.rusefi.io.tcp.TcpConnector;
import org.jetbrains.annotations.NotNull;

import java.util.concurrent.*;

/**
 * @author Andrey Belomutskiy
 *         3/3/14
 */
public class LinkManager {
    public static LinkDecoder ENCODER = new LinkDecoder() {
        @Override
        public String unpack(String packedLine) {
            return LinkManager.unpack(packedLine);
        }
    };

    public final static Executor IO_EXECUTOR = Executors.newSingleThreadExecutor(new ThreadFactory() {
        @Override
        public Thread newThread(@NotNull Runnable r) {
            Thread t = new Thread(r);
            t.setName("IO executor thread");
            t.setDaemon(true);  // need daemon thread so that COM thread is also daemon
            return t;
        }
    });
    public static final String LOG_VIEWER = "log viewer";
    public static final LinkedBlockingQueue<Runnable> COMMUNICATION_QUEUE = new LinkedBlockingQueue<>();
    public static final ExecutorService COMMUNICATION_EXECUTOR = new ThreadPoolExecutor(1, 1,
            0L, TimeUnit.MILLISECONDS,
            COMMUNICATION_QUEUE,
            new ThreadFactory() {
                @Override
                public Thread newThread(Runnable r) {
                    Thread t = Executors.defaultThreadFactory().newThread(r);
                    t.setName("communication executor");;
                    return t;
                }
            });
    public static EngineState engineState = new EngineState(new EngineState.EngineStateListenerImpl() {
        @Override
        public void beforeLine(String fullLine) {
            FileLog.MAIN.logLine(fullLine);
        }
    });
    public static LinkConnector connector;

    /**
     * This flag controls if mock controls are needed
     */
    public static boolean isStimulationMode;

    public static void start(String port) {
        FileLog.MAIN.logLine("Starting " + port);
        if (isLogViewerMode(port)) {
            connector = LinkConnector.VOID;
        } else if (TcpConnector.isTcpPort(port)) {
            connector = new TcpConnector(port);
            isStimulationMode = true;
        } else {
            connector = new SerialConnector(port);
        }
    }

    public static boolean isLogViewerMode(String port) {
        return port.equals(LOG_VIEWER);
    }

    public static boolean isLogViewer() {
        return connector == LinkConnector.VOID;
    }

    /**
     * todo: should this be merged into {@link #start(String)} ?
     */
    public static void open(LinkStateListener listener) {
        if (connector == null)
            throw new NullPointerException("connector");
        connector.connect(listener);
    }

    public static void open() {
        open(LinkStateListener.VOID);
    }

    public static void send(String command) throws InterruptedException {
        if (connector == null)
            throw new NullPointerException("connector");
        connector.send(command);
    }

    public static String encodeCommand(String command) {
        return "sec!" + command.length() + "!" + command;
    }

    public static void restart() {
        connector.restart();
    }

    public static String unpack(String packet) {
        return connector.unpack(packet);
    }

    public static boolean hasError() {
        return connector.hasError();
    }

    public static String unpackConfirmation(String message) {
        return connector.unpackConfirmation(message);
    }

    public static interface LinkStateListener {
        LinkStateListener VOID = new LinkStateListener() {
            @Override
            public void onConnectionFailed() {
            }

            @Override
            public void onConnectionEstablished() {

            }
        };

        void onConnectionFailed();

        void onConnectionEstablished();
    }
}
