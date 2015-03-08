package com.rusefi;

import java.io.*;
import java.util.Arrays;

/**
 * (c) Andrey Belomutskiy
 * 3/6/2015
 */
public class ConfigurationImage {
    private final static String BIN_HEADER = "RUSEFI0.1";
    private byte content[];

    public ConfigurationImage(int size) {
        content = new byte[size];
    }

    public ConfigurationImage(byte[] content) {
        this.content = content;
    }

    public int getSize() {
        return content.length;
    }

    public byte[] getFileContent() throws IOException {
        try (ByteArrayOutputStream baos = new ByteArrayOutputStream()) {
            byte[] bytes = BIN_HEADER.getBytes();
            if (bytes.length != BIN_HEADER.length())
                throw new IllegalStateException("Encoding issue");
            baos.write(bytes);
            baos.write(content);
            return baos.toByteArray();
        }
    }

    public void saveToFile(String fileName) throws IOException {
        FileOutputStream fos = new FileOutputStream(fileName);
        fos.write(getFileContent());
        fos.close();
        System.out.println("Saved to " + fileName);
    }

    public static ConfigurationImage readFromFile(String fileName, Logger logger) throws IOException {
        File file = new File(fileName);
        int size = (int) file.length();

        int contentSize = size - BIN_HEADER.length();

        FileInputStream fis = new FileInputStream(fileName);
        byte[] header = new byte[BIN_HEADER.length()];
        int result = fis.read(header);
        if (result != header.length)
            return null;
        if (!Arrays.equals(header, BIN_HEADER.getBytes()))
            return null;
        ConfigurationImage image = new ConfigurationImage(contentSize);
        result = fis.read(image.content);
        return result == image.getContent().length ? image : null;
    }

    public static byte[] extractContent(byte[] rom) {
        if (rom.length < BIN_HEADER.length())
            return null;
        byte[] result = new byte[rom.length - BIN_HEADER.length()];
        System.arraycopy(rom, BIN_HEADER.length(), result, 0, result.length);
        return result;
    }

    public byte[] getContent() {
        return content;
    }

    @SuppressWarnings("CloneDoesntCallSuperClone")
    @Override
    public ConfigurationImage clone() {
        byte[] copy = content.clone();
        return new ConfigurationImage(copy);
    }
}
