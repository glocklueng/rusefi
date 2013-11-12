package com.irnems;

import com.irnems.core.EngineState;
import com.irnems.core.MessagesCentral;

import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadFactory;

/**
 * 7/9/13
 * (c) Andrey Belomutskiy
 */
public class SerialManager {
    public static String port;

    private final static Executor SERIAL_EXECUTOR = Executors.newSingleThreadExecutor(new ThreadFactory() {
        @Override
        public Thread newThread(Runnable r) {
            Thread t = new Thread(r);
            t.setName("SerialManager executor thread");
            t.setDaemon(true);  // need daemon thread so that COM thread is also daemon
            return t;
        }
    });


    public static EngineState engineState = new EngineState(new EngineState.EngineStateListenerImpl() {
        @Override
        public void beforeLine(String fullLine) {
            System.out.println("SerialManager.beforeLine: " + fullLine);
            FileLog.INSTANCE.logLine(fullLine);
        }
    });

    public static boolean onlyUI = false;
    private static boolean closed;

    public static void scheduleOpening() {
        System.out.println("scheduleOpening");
        SERIAL_EXECUTOR.execute(new Runnable() {
            @Override
            public void run() {
                System.out.println("scheduleOpening>openPort");
                PortHolder.getInstance().openPort(port, engineState);
            }
        });
    }

    public static void restart() {
        SERIAL_EXECUTOR.execute(new Runnable() {
            @Override
            public void run() {
                MessagesCentral.getInstance().postMessage(SerialManager.class, "Restarting serial IO");
                if (closed)
                    return;
                PortHolder.getInstance().close();
                PortHolder.getInstance().openPort(port, engineState);
            }
        });
    }
/*
    static String[] findSerialPorts() {
        List<String> result = new ArrayList<String>();

        Enumeration<CommPortIdentifier> portEnum = CommPortIdentifier.getPortIdentifiers();
        while (portEnum.hasMoreElements()) {
            CommPortIdentifier portIdentifier = portEnum.nextElement();
            System.out.println(portIdentifier.getName() + " - " + getPortTypeName(portIdentifier.getPortType()));
            if (portIdentifier.getPortType() == CommPortIdentifier.PORT_SERIAL)
                result.add(portIdentifier.getName());
        }
        return result.toArray(new String[result.size()]);
    }

    static String getPortTypeName(int portType) {
        switch (portType) {
            case CommPortIdentifier.PORT_I2C:
                return "I2C";
            case CommPortIdentifier.PORT_PARALLEL:
                return "Parallel";
            case CommPortIdentifier.PORT_RAW:
                return "Raw";
            case CommPortIdentifier.PORT_RS485:
                return "RS485";
            case CommPortIdentifier.PORT_SERIAL:
                return "Serial";
            default:
                return "unknown type";
        }
    }
  */
    //    public static void close() {
//        closed = true;
//        SerialIO.getInstance().stop();
//    }
}
