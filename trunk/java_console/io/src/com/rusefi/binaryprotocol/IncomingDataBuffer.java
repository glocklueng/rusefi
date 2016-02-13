package com.rusefi.binaryprotocol;

import com.rusefi.Logger;
import com.rusefi.Timeouts;
import etch.util.CircularByteBuffer;
import net.jcip.annotations.ThreadSafe;

import java.io.EOFException;
import java.util.Arrays;

/**
 * (c) Andrey Belomutskiy
 * 6/20/2015.
 */
@ThreadSafe
public class IncomingDataBuffer {
    private static final int BUFFER_SIZE = 10000;
    /**
     * buffer for response bytes from controller
     */
    private final CircularByteBuffer cbb;
    private final Logger logger;

    public IncomingDataBuffer(Logger logger) {
        this.cbb = new CircularByteBuffer(BUFFER_SIZE);
        this.logger = logger;
    }

    public void addData(byte[] freshData) {
        logger.trace(freshData.length + " byte(s) arrived");
        synchronized (cbb) {
            if (cbb.size() - cbb.length() < freshData.length) {
                logger.error("IncomingDataBuffer: buffer overflow not expected");
                cbb.clear();
            }
            cbb.put(freshData);
            cbb.notifyAll();
        }
    }

    /**
     * @return true in case of timeout, false if everything is fine
     */
    public boolean waitForBytes(int count, long start, String msg) throws InterruptedException {
        logger.info("Waiting for " + count + " byte(s): " + msg);
        synchronized (cbb) {
            while (cbb.length() < count) {
                int timeout = (int) (start + Timeouts.BINARY_IO_TIMEOUT - System.currentTimeMillis());
                if (timeout <= 0) {
                    return true; // timeout. Sad face.
                }
                cbb.wait(timeout);
            }
        }
        return false; // looks good!
    }

    public void dropPending() {
        synchronized (cbb) {
            int pending = cbb.length();
            if (pending > 0) {
                logger.error("Unexpected pending data: " + pending + " byte(s)");
                byte[] bytes = new byte[pending];
                cbb.get(bytes);
                logger.error("data: " + Arrays.toString(bytes));
            }
        }
    }

    public int getShort() throws EOFException {
        synchronized (cbb) {
            return cbb.getShort();
        }
    }

    public int getInt() throws EOFException {
        synchronized (cbb) {
            return cbb.getInt();
        }
    }

    public void getData(byte[] packet) {
        synchronized (cbb) {
            cbb.get(packet);
        }
    }
}
