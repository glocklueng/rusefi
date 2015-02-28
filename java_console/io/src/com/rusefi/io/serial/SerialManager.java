package com.rusefi.io.serial;

import com.rusefi.FileLog;
import com.rusefi.core.MessagesCentral;
import com.rusefi.io.DataListener;
import com.rusefi.io.LinkManager;

/**
 * 7/9/13
 * (c) Andrey Belomutskiy
 */
class SerialManager {
    public static String port;

    private static boolean closed;

    static DataListener dataListener = new DataListener() {
        public void onStringArrived(String string) {
            //                jTextAreaIn.append(string);
            LinkManager.engineState.processNewData(string);
        }
    };
    private static LinkManager.LinkStateListener listener;

    public static void scheduleOpening(LinkManager.LinkStateListener listener) {
        SerialManager.listener = listener;
        FileLog.rlog("scheduleOpening");
        LinkManager.IO_EXECUTOR.execute(new Runnable() {
            @Override
            public void run() {
                FileLog.rlog("scheduleOpening>openPort");
                PortHolder.getInstance().openPort(port, SerialManager.dataListener, SerialManager.listener);
            }
        });
    }

    public static void restart() {
        LinkManager.IO_EXECUTOR.execute(new Runnable() {
            @Override
            public void run() {
                MessagesCentral.getInstance().postMessage(SerialManager.class, "Restarting serial IO");
                if (closed)
                    return;
                PortHolder.getInstance().close();
                boolean result = PortHolder.getInstance().openPort(port, dataListener, SerialManager.listener);
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
