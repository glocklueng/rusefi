package com.rusefi.io.serial;

import com.rusefi.FileLog;
import com.rusefi.Logger;
import com.rusefi.binaryprotocol.BinaryProtocol;
import com.rusefi.core.MessagesCentral;
import com.rusefi.io.CommandQueue;
import com.rusefi.io.DataListener;
import com.rusefi.io.LinkManager;
import jssc.SerialPort;
import jssc.SerialPortException;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.concurrent.*;

/**
 * This class holds the reference to the actual Serial port object
 * <p/>
 * 7/25/13
 * (c) Andrey Belomutskiy
 */
public class PortHolder {
    //    private static final int BAUD_RATE = 8 * 115200;// 921600;
//    private static final int BAUD_RATE = 2 * 115200;
    private static final int BAUD_RATE = 115200;
    private static final int SECOND = 1000;
    private static final int MINUTE = 60 * SECOND;
    private static PortHolder instance = new PortHolder();
    private final Object portLock = new Object();

    private final LinkedBlockingQueue<Runnable> EXE_Q = new LinkedBlockingQueue<>();

    private final ExecutorService PORT_QUEUE = new ThreadPoolExecutor(1, 1,
            0L, TimeUnit.MILLISECONDS,
            EXE_Q);

    public PortHolderListener portHolderListener = PortHolderListener.VOID;
    private DataListener listener;
    private BinaryProtocol bp;

    private PortHolder() {
    }

    @Nullable
    private SerialPort serialPort;

    boolean openPort(String port, DataListener dataListener, LinkManager.LinkStateListener listener) {
        this.portHolderListener.onPortHolderMessage(SerialManager.class, "Opening port: " + port);
        if (port == null)
            return false;
        boolean result = open(port, dataListener);
        if (!result)
            listener.onConnectionFailed();
        return result;
    }

    public boolean open(String port, final DataListener listener) {
        this.listener = listener;
        SerialPort serialPort = new SerialPort(port);
        try {
            FileLog.MAIN.logLine("Opening " + port + " @ " + BAUD_RATE);
            boolean opened = serialPort.openPort();//Open serial port
            if (!opened)
                FileLog.MAIN.logLine("not opened!");
            setupPort(serialPort, BAUD_RATE);
//            serialPort.addEventListener(new SerialPortReader(serialPort, portHolderListener));
        } catch (SerialPortException e) {
            FileLog.rlog("ERROR " + e.getMessage());
            return false;
        }
        FileLog.rlog("PortHolder: Sleeping a bit");
        try {
            // todo: why is this delay here? add a comment
            Thread.sleep(200);
        } catch (InterruptedException e) {
            throw new IllegalStateException(e);
        }

        synchronized (portLock) {
            this.serialPort = serialPort;
            portLock.notifyAll();
        }

        bp = new BinaryProtocol(Logger.STDOUT, serialPort);

        bp.switchToBinaryProtocol();
//        bp.readImage(BinaryProtocol.IMAGE_SIZE);

        Runnable textPull = new Runnable() {
            @Override
            public void run() {
                while (true) {
                    if (EXE_Q.isEmpty()) {
                        PORT_QUEUE.submit(new Runnable() {
                            @Override
                            public void run() {
                                String text = bp.requestText();
                                listener.onDataArrived((text + "\r\n").getBytes());
                            }
                        });
                    }
                    sleep();
                }
            }
        };
        Thread tr = new Thread(textPull);
        tr.setName("text pull");
        tr.start();

//
//        try {
//            FileLog.rlog("PortHolder: test command");
//            /**
//             * Let's make sure we have not connected to Tuner Studio port?
//             * @see EngineState#TS_PROTOCOL_TAG
//             */
//            doWriteCommand("test");
//        } catch (SerialPortException e) {
//            return false;
//        }
        return true;
    }

    private void sleep() {
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            throw new IllegalStateException(e);
        }
    }

    public static void setupPort(SerialPort serialPort, int baudRate) throws SerialPortException {
        serialPort.setParams(baudRate, 8, 1, 0);//Set params.
        int mask = SerialPort.MASK_RXCHAR;
        //Set the prepared mask
        serialPort.setEventsMask(mask);
    }

    public void close() {
        synchronized (portLock) {
            if (serialPort != null) {
                try {
                    serialPort.closePort();
                    serialPort = null;
                } catch (SerialPortException e) {
                    FileLog.MAIN.logLine("Error while closing: " + e);
                } finally {
                    portLock.notifyAll();
                }
            }
        }
    }

    /**
     * this method blocks till a connection is available
     */
    public void packAndSend(final String command) throws InterruptedException {
        FileLog.MAIN.logLine("Sending [" + command + "]");
        portHolderListener.onPortHolderMessage(PortHolder.class, "Sending [" + command + "]");

        Future f = PORT_QUEUE.submit(new Runnable() {
            @Override
            public void run() {
                bp.sendTextCommand(command);
            }
        });

        try {
            f.get(30, TimeUnit.SECONDS);
        } catch (ExecutionException e) {
            throw new IllegalStateException(e);
        } catch (TimeoutException e) {
            throw new IllegalStateException(e);
        }
        /**
         * this here to make CommandQueue happy
         */
        MessagesCentral.getInstance().postMessage(PortHolder.class, CommandQueue.CONFIRMATION_PREFIX + command);


//        long now = System.currentTimeMillis();
//
//        synchronized (portLock) {
//            while (serialPort == null) {
//                if (System.currentTimeMillis() - now > 3 * MINUTE)
//                    portHolderListener.onPortHolderMessage(PortHolder.class, "Looks like connection is gone :(");
//                portLock.wait(MINUTE);
//            }
//            // we are here only when serialPort!=null, that means we have a connection
//            try {
//                doWriteCommand(command);
//            } catch (SerialPortException e) {
//                throw new IllegalStateException(e);
//            }
//        }
    }

    private void doWriteCommand(@NotNull String command) throws SerialPortException {
        if (serialPort == null)
            throw new NullPointerException("serialPort");
        serialPort.writeBytes((command + "\n").getBytes());
    }

    public static PortHolder getInstance() {
        return instance;
    }
}
