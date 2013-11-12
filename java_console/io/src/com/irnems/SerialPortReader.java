package com.irnems;

import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

/**
 * Date: 12/25/12
 * (c) Andrey Belomutskiy
 */
public class SerialPortReader implements SerialPortEventListener {
    private SerialPort serialPort;
    private StringListener listener;

    public SerialPortReader(SerialPort serialPort, StringListener listener) {
        this.serialPort = serialPort;
        this.listener = listener;
    }

    public void serialEvent(SerialPortEvent spe) {
        if (spe.isRXCHAR() || spe.isRXFLAG()) {
            try {
                handleRx(spe);
            } catch (SerialPortException e) {
                e.printStackTrace(System.err);
            }
        } else {
            System.out.println("SerialPortReader serialEvent " + spe);
        }
    }

    private void handleRx(SerialPortEvent spe) throws SerialPortException {
        if (spe.getEventValue() > 0) {
            byte[] buffer = serialPort.readBytes(spe.getEventValue());
            String str = new String(buffer);
            listener.onStringArrived(str);
 //           System.out.println("arrived [" + str + "]");
        }
    }

    public interface StringListener {
        void onStringArrived(String string);
    }
}
