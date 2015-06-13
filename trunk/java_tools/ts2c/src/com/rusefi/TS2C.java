package com.rusefi;

import java.io.*;
import java.util.Arrays;
import java.util.Date;

/**
 * 12/27/2014
 * Andrey Belomutskiy, (c) 2012-2014
 */
@SuppressWarnings("StringConcatenationInsideStringBufferAppend")
public class TS2C {
    private static final int SIZE = 16;

    static float loadBins[] = new float[SIZE];
    static float rpmBins[] = new float[SIZE];
    static float table[][] = new float[SIZE][];

    public static void main(String[] args) throws IOException {

        if (args.length != 4) {
            System.out.println("Four parameters expected: ");
            System.out.println("  INPUT_MSQ_FILE NAME LOAD_SECTION_NAME RPM_SECTION_NAME TABLE_NAME");
            System.out.println("for example");
            System.out.println("  currenttune.msq ignitionLoadBins ignitionRpmBins veTable");
            System.exit(-1);
        }
        String fileName = args[0];
        String loadSectionName = args[1];
        String rpmSectionName = args[2];
        String tableName = args[3];

        BufferedReader r = readAndScroll(fileName, loadSectionName);
        readAxle(loadBins, r);
        r = readAndScroll(fileName, rpmSectionName);
        readAxle(rpmBins, r);

        for (int i = 0; i < SIZE; i++) {
            table[i] = new float[SIZE];
        }

        r = readAndScroll(fileName, tableName);
        readTable(table, r);

        BufferedWriter w = new BufferedWriter(new FileWriter("output.c"));
        w.write("/* Generated by TS2C on " + new Date() + "*/\r\n");

        for (int i = 0; i < SIZE; i++)
            writeLine(table[i], w, i);
        w.close();
    }

    private static BufferedReader readAndScroll(String fileName, String sectionName) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        System.out.println("Reading from " + fileName + ", scrolling to " + sectionName);
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.contains(sectionName)) {
                System.out.println("Found " + line);
                break;
            }
        }
        return reader;
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
