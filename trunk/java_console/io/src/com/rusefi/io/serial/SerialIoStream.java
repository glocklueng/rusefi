package com.rusefi.io.serial;

import com.rusefi.FileLog;
import com.rusefi.Logger;
import com.rusefi.io.DataListener;
import com.rusefi.io.IoStream;
import jssc.SerialPort;
import jssc.SerialPortException;

import java.io.IOException;

/**
 * (c) Andrey Belomutskiy
 * 5/11/2015.
 */
public class SerialIoStream implements IoStream {
    private final SerialPort serialPort;
    private final Logger logger;

    public SerialIoStream(SerialPort serialPort, Logger logger) {
        this.serialPort = serialPort;
        this.logger = logger;
    }

    @Override
    public void close() {
        try {
            FileLog.MAIN.logLine("CLOSING PORT...");
            serialPort.closePort();
            FileLog.MAIN.logLine("PORT CLOSED");
        } catch (SerialPortException e) {
            logger.error("Error closing port: " + e);
        }
    }

    @Override
    public void write(byte[] bytes) throws IOException {
        try {
            serialPort.writeBytes(bytes);
        } catch (SerialPortException e) {
            throw new IOException(e);
        }
    }

    @Override
    public void purge() {
        try {
            serialPort.purgePort(SerialPort.PURGE_RXCLEAR | SerialPort.PURGE_TXCLEAR);
        } catch (SerialPortException e) {
            logger.info("Error while purge: " + e);
            close();
        }
    }

    @Override
    public void addEventListener(DataListener listener) {
        try {
            serialPort.addEventListener(new SerialPortReader(serialPort, listener));
        } catch (SerialPortException e) {
            throw new IllegalStateException(e);
        }
    }
}
