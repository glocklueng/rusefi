package com.rusefi;

import java.io.*;
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
    static float table[][] = new float[SIZE][];

    public static void main(String[] args) throws IOException {
        BufferedReader r = new BufferedReader(new FileReader(INPUT_NAME));

        readAxle(loadBins, r);
        readAxle(rpmBins, r);

        for (int i = 0; i < SIZE; i++) {
            table[i] = new float[SIZE];
        }

        readTable(table, r);

        BufferedWriter w = new BufferedWriter(new FileWriter("output.c"));

        for (int i = 0; i < SIZE; i++)
            writeLine(table[i], w, i);
        w.close();
    }

    private static void writeLine(float[] floats, BufferedWriter w, int index) throws IOException {
        StringBuilder sb = new StringBuilder("{");


        sb.append("/* " + index + " " + String.format("%3.3f", loadBins[index]) + "\t*/");
        for (int i = 0; i < SIZE; i++) {
            sb.append("/* " + i + " " + rpmBins[i] + "*/" + String.format("%3.3f", floats[i]) + ",\t");
        }
        sb.append("},\r\n");

        w.write(sb.toString());
    }

    private static void readTable(float[][] table, BufferedReader r) throws IOException {
        int index = 0;

        while (index < SIZE) {
            String line = r.readLine();
            if (line == null)
                throw new IOException("End of file?");
            line = line.trim();
            if (line.isEmpty())
                continue;

            String[] values = line.split(" ");
            if (values.length != SIZE)
                throw new IllegalStateException("Unexpected line: " + line);

            for (int i = 0; i < SIZE; i++) {
                table[index][i] = Float.parseFloat(values[i]);
            }
            System.out.println("Got line " + index + ": " + Arrays.toString(table[index]));
            index++;
        }
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
