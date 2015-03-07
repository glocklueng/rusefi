package com.rusefi.binaryprotocol;

import com.rusefi.io.serial.PortHolder;
import jssc.SerialPort;
import jssc.SerialPortException;

/**
 * (c) Andrey Belomutskiy
 * 3/6/2015
 */
public class BinaryProtocolCmd {
    private static SerialPort serialPort;

    public static void main(String[] args) throws SerialPortException {
        if (args.length != 1) {
            System.out.println("Exactly one parameter expected");
            return;
        }

        String port = args[0];

        serialPort = new SerialPort(port);
        boolean opened = serialPort.openPort();
        if (!opened) {
            System.out.println("failed to open " + port);
        }
        PortHolder.setupPort(serialPort, 38400);
        System.out.println("Looks good");
        sendQueryCommand();

    }

    private static void sendQueryCommand() throws SerialPortException {
        byte[] command = {'S'};
        sendCrc(command);
    }

    private static void sendCrc(byte[] command) throws SerialPortException {
        byte[] packet = makePacket(command);

        serialPort.writeBytes(packet);
    }

    public static byte[] makePacket(byte[] command) {
        byte[] packet = new byte[command.length + 6];

        packet[0] = (byte) (command.length / 256);
        packet[1] = (byte) command.length;

        int index = packet.length - 1;
        System.arraycopy(command, 0, packet, 2, command.length);
        int crc = CRC.crc32(command, command.length);

        for (int i = 0; i < 4; i++) {
            packet[index--] = (byte) crc;
            crc >>= 8;
        }
        return packet;
    }
}
