package com.rusefi.io;

import com.rusefi.core.EngineState;

/**
 * @author Andrey Belomutskiy
 *         3/3/14
 */
public interface LinkConnector extends LinkDecoder {
    LinkConnector VOID = new LinkConnector() {
        @Override
        public void connect(LinkManager.LinkStateListener listener) {
        }

        @Override
        public void send(String command) throws InterruptedException {
        }

        @Override
        public void restart() {
        }

        @Override
        public boolean hasError() {
            return false;
        }

        @Override
        public String unpack(String packet) {
            return EngineState.unpackString(packet);
        }

        @Override
        public String unpackConfirmation(String message) {
            return message;
        }
    };

    void connect(LinkManager.LinkStateListener listener);

    void send(String command) throws InterruptedException;

    void restart();

    boolean hasError();

    String unpackConfirmation(String message);
}
