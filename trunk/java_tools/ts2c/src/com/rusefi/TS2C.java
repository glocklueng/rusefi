package com.rusefi;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

/**
 * 12/27/2014
 * Andrey Belomutskiy, (c) 2012-2014
 */
public class TS2C {
    private static final String INPUT_NAME = "input.txt";
    private static final int SIZE = 16;

    static float loadBins[] = new float[SIZE];
    static float rpmBins[] = new float[SIZE];

    public static void main(String[] args) throws IOException {
        BufferedReader r = new BufferedReader(new FileReader(INPUT_NAME));

        readAxle(loadBins, r);
        readAxle(rpmBins, r);


    }

    private static void readAxle(float[] bins, BufferedReader r) throws IOException {
        int index = 0;

        while (index < SIZE) {
            String line = r.readLine();
            if (line == null)
                throw new IOException("End of file?");
            line = line.trim();
            if (line.isEmpty())
                continue;
            bins[index++] = Float.parseFloat(line);


        }

        System.out.println("Got bins " + Arrays.toString(bins));

    }
}
