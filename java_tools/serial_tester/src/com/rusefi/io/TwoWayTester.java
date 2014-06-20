package com.rusefi.io;

import com.rusefi.io.serial.SerialPortReader;
import jssc.SerialPort;
import jssc.SerialPortException;

public class TwoWayTester {

    private static final int BAUD_RATE = 38400;
    //private static final int BAUD_RATE = 115200;
    public static final String TEST_LINE = "hello1231234dklfjasldfjalsdfkjladkfjladksjfladfkjg;adlfkjg;dlfkjg;ladfkjg;ldkfjg;ldkfjg;ladfkjg;ldfkjg;ldkfjg;ladfkjg;ldfkjg";

    public static void main(String[] args) throws SerialPortException, InterruptedException {
        String port1 = "COM24";
        String port2 = "COM25";

        SerialPort out = open(port1, new DataListener() {
            @Override
            public void onStringArrived(String string) {
                // nothing is expected to arrive
            }
        });
        DataListener listener = new DataListener() {

            int counter;
            StringBuffer sb = new StringBuffer();

            @Override
            public void onStringArrived(String string) {
                sb.append(string);
                if (sb.length() >= TEST_LINE.length()) {
                    String l = sb.substring(0, TEST_LINE.length());

                    if (!l.equalsIgnoreCase(TEST_LINE)) {
                        logLine("WOW   " + l);
                    } else {
                        logLine("Ok " + counter++);
                    }

                    sb.delete(0, TEST_LINE.length());
                } else {
                   logLine("Partial");
                }

            }
        };
        SerialPort in = open(port2, listener);

        while (true) {
            out.writeString(TEST_LINE);
            //Thread.sleep(50);
        }
    }

    public static SerialPort open(String port, DataListener listener) throws SerialPortException {
        SerialPort serialPort = new SerialPort(port);
        logLine("Opening " + port + " @ " + BAUD_RATE);
        boolean opened = serialPort.openPort();//Open serial port
        if (!opened)
            logLine("not opened");
        serialPort.setParams(BAUD_RATE, 8, 1, 0);//Set params.
        int mask = SerialPort.MASK_RXCHAR;
        //Set the prepared mask
        serialPort.setEventsMask(mask);
        serialPort.addEventListener(new SerialPortReader(serialPort, listener));
        return serialPort;
    }

    private static void logLine(String s) {
        System.out.println(s);
    }
}
