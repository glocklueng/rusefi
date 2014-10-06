package com.rusefi;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/**
 * (c) Andrey Belomutskiy
 * <p/>
 * 10/6/14
 */
public class EnumToString {
    public static void main(String[] args) {
        process("../../firmware/controllers/algo/io_pins.h", "out.h");
    }

    private static void process(String inFileName, String outFileName) {
        BufferedReader reader;

        boolean isInsideEnum;

        try {
            reader = new BufferedReader(new FileReader(inFileName));
            String line;
            while ((line = reader.readLine()) != null) {
                line = line.replaceAll("\\s+", "");

                if (line.startsWith("typedefenum{")) {
                    System.out.println("Entering enum");
                    isInsideEnum = true;
                } else if (line.startsWith("}")) {
                    System.out.println("Ending enum" + line);
                }

            }
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }
}
