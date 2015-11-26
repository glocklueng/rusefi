package com.rusefi.io.tcp.test;

import com.rusefi.ConfigurationImage;
import com.rusefi.FileLog;
import com.rusefi.binaryprotocol.BinaryProtocol;
import com.rusefi.io.tcp.BinaryProtocolServer;
import com.rusefi.io.tcp.TcpIoStream;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

class BinaryProtocolServerSandbox {
    public static void main(String[] args) {
        TcpIoStream stream = new TcpIoStream(new ByteArrayInputStream(new byte[0]), new ByteArrayOutputStream());
        BinaryProtocol.instance = new BinaryProtocol(FileLog.LOGGER, stream);
        BinaryProtocol.instance.setController(new ConfigurationImage(new byte[14008]));
        BinaryProtocol.currentOutputs = new byte[1 + BinaryProtocol.OUTPUT_CHANNELS_SIZE];
        BinaryProtocolServer.start();
    }
}