package com.rusefi.binaryprotocol;

import com.rusefi.ConfigurationImage;
import com.rusefi.io.DataListener;
import com.rusefi.io.serial.SerialPortReader;
import etch.util.CircularByteBuffer;
import jssc.SerialPort;
import jssc.SerialPortException;

import java.io.EOFException;
import java.util.Arrays;

/**
 * (c) Andrey Belomutskiy
 * 3/6/2015
 */
public class BinaryProtocol {
    private static final int BLOCKING_FACTOR = 256;
    private static final byte RESPONSE_OK = 0;
    private final SerialPort serialPort;
    private static final int BUFFER_SIZE = 10000;
    final CircularByteBuffer cbb;

    public BinaryProtocol(SerialPort serialPort) throws SerialPortException {
        this.serialPort = serialPort;

        cbb = new CircularByteBuffer(BUFFER_SIZE);
        DataListener listener = new DataListener() {
            @Override
            public void onDataArrived(byte[] freshData) {
                System.out.println(freshData.length + " byte(s) arrived");
                synchronized (cbb) {
                    if (cbb.size() - cbb.length() < freshData.length) {
                        System.out.println("buffer overflow not expected");
                        cbb.clear();
                    }
                    cbb.put(freshData);
                    cbb.notifyAll();
                }
            }
        };
        serialPort.addEventListener(new SerialPortReader(serialPort, listener));
    }

    private void waitForBytes(int count) throws InterruptedException {
        System.out.println("Waiting for " + count + " byte(s)");
        synchronized (cbb) {
            while (cbb.length() < count)
                cbb.wait();
        }
    }

    /**
     * this method adds two bytes for packet size before and four bytes for CRC after
     */
    public static byte[] makePacket(byte[] command) {
        byte[] packet = new byte[command.length + 6];

        packet[0] = (byte) (command.length / 256);
        packet[1] = (byte) command.length;

        System.arraycopy(command, 0, packet, 2, command.length);
        int crc = CRC.crc32(command);

        putInt(packet, packet.length - 4, crc);
        return packet;
    }

    private static void putInt(byte[] packet, int offset, int value) {
        int index = offset + 3;
        for (int i = 0; i < 4; i++) {
            packet[index--] = (byte) value;
            value >>= 8;
        }
    }

    private static void putShort(byte[] packet, int offset, int value) {
        int index = offset + 1;
        for (int i = 0; i < 2; i++) {
            packet[index--] = (byte) value;
            value >>= 8;
        }
    }

    public void sendQueryCommand() throws SerialPortException {
        byte[] command = {'S'};
        sendCrcPacket(command);
    }

    public void sendCrcPacket(byte[] command) throws SerialPortException {
        byte[] packet = makePacket(command);

        System.out.println("Sending " + Arrays.toString(packet));
        serialPort.writeBytes(packet);
    }

    public static int swap16(int x) {
        return (((x & 0xFF) << 8) | ((x) >> 8));
    }

    public static int swap32(int x) {
        return (((x) >> 24) & 0xff) | (((x) << 8) & 0xff0000) | (((x) >> 8) & 0xff00) | (((x) << 24) & 0xff000000);
    }

    public byte[] receivePacket() throws InterruptedException, EOFException {
        synchronized (cbb) {
            waitForBytes(2);

            int packetSize = BinaryProtocol.swap16(cbb.getShort());
            System.out.println("Got packet size " + packetSize);
            if (packetSize < 0 || packetSize > 300) {
                // invalid packet size
                return null;
            }
            waitForBytes(packetSize + 4);

            byte[] packet = new byte[packetSize];
            int packetCrc;
            synchronized (cbb) {
                cbb.get(packet);
                packetCrc = BinaryProtocol.swap32(cbb.getInt());
            }
            int actualCrc = CRC.crc32(packet);

            boolean isCrcOk = actualCrc == packetCrc;
            if (!isCrcOk) {
                System.out.println(String.format("%x", actualCrc) + " vs " + String.format("%x", packetCrc));
                return null;
            }
            System.out.println("packet " + Arrays.toString(packet) + ": crc OK");

            return packet;
        }
    }

    public void readImage(ConfigurationImage image) throws SerialPortException, EOFException, InterruptedException {
        int offset = 0;

        while (offset < image.getSize()) {
            int remainingSize = image.getSize() - offset;
            int requestSize = Math.min(remainingSize, BLOCKING_FACTOR);

            byte packet[] = new byte[7];
            packet[0] = 'R';
            putShort(packet, 1, 0); // page
            putShort(packet, 3, swap16(offset));
            putShort(packet, 5, swap16(requestSize));

            sendCrcPacket(packet);

            byte[] response = receivePacket();
            if (response == null || response.length == 0 || response[0] != RESPONSE_OK || response.length != requestSize + 1) {
                System.out.println("Something is wrong, retrying...");
                continue;
            }


            offset += requestSize;
        }
        System.out.println("Got image!");
    }
}
