package com.irnems;

import com.irnems.core.MessagesCentral;
import com.irnems.core.Pair;
import org.jetbrains.annotations.NotNull;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * This class keeps re-sending a command till a proper confirmation is received
 * <p/>
 * Date: 1/7/13
 * (c) Andrey Belomutskiy
 */
@SuppressWarnings("FieldCanBeLocal")
public class CommandQueue {
    private static final String CONFIRMATION_PREFIX = "confirmation_";
    private final Object lock = new Object();
    private String latestConfirmation;

    private static final CommandQueue instance = new CommandQueue();
    private final BlockingQueue<Pair<String, Integer>> pendingCommands = new LinkedBlockingQueue<Pair<String, Integer>>();

    private final Runnable runnable = new Runnable() {
        @SuppressWarnings("InfiniteLoopStatement")
        @Override
        public void run() {
            MessagesCentral.getInstance().postMessage(CommandQueue.class, "SerialIO started");
            while (true) {
                try {
                    sendPendingCommand();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    throw new IllegalStateException(e);
                }
            }
        }
    };

    /**
     * this method is always invoked on 'Commands Queue' thread {@link #runnable}
     *
     * @throws InterruptedException
     */
    private void sendPendingCommand() throws InterruptedException {
        /**
         * here we block in case there is no command to send
         */
        @NotNull
        final Pair<String, Integer> command = pendingCommands.take();
        // got a command? let's send it!
        sendCommand(command);
    }

    /**
     * this method keeps retrying till a confirmation is received
     */
    private void sendCommand(final Pair<String, Integer> pair) throws InterruptedException {
        int counter = 0;
        latestConfirmation = null;
        String command = pair.first;

        while (!command.equals(latestConfirmation)) {
            counter++;
            PortHolder.getInstance().packAndSend(command);
            synchronized (lock) {
                lock.wait(pair.second);
            }
        }

        if (counter != 1)
            MessagesCentral.getInstance().postMessage(CommandQueue.class, "Took " + counter + " attempts");
    }

    private CommandQueue() {
        new Thread(runnable, "Commands Queue").start();
        final MessagesCentral mc = MessagesCentral.getInstance();
        mc.addListener(new MessagesCentral.MessageListener() {
            @Override
            public void onMessage(Class clazz, String message) {
                if (message.startsWith(CONFIRMATION_PREFIX))
                    handleConfirmationMessage(message, mc);
            }
        });
    }

    private void handleConfirmationMessage(String message, MessagesCentral mc) {
        String confirmation = message.substring(CONFIRMATION_PREFIX.length());
        int index = confirmation.indexOf(":");
        if (index < 0) {
            mc.postMessage(CommandQueue.class, "Broken confirmation: " + confirmation);
            return;
        }
        int length = Integer.parseInt(confirmation.substring(index + 1));
        if (length != index) {
            mc.postMessage(CommandQueue.class, "Broken confirmation length: " + confirmation);
            return;
        }
        latestConfirmation = confirmation.substring(0, length);
        mc.postMessage(CommandQueue.class, "got valid conf! " + latestConfirmation);
        synchronized (lock) {
            lock.notifyAll();
        }
    }

    public static CommandQueue getInstance() {
        return instance;
    }

    public void write(String command) {
        write(command, 300);
    }

    public void write(String command, int timeout) {
        pendingCommands.add(new Pair<String, Integer>(command, timeout));
    }
}
