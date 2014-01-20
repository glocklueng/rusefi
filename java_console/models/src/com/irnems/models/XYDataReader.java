package com.irnems.models;

import com.irnems.FileLog;

import java.io.*;

/**
 * 6/30/13
 * (c) Andrey Belomutskiy
 */
public class XYDataReader {
    public static XYData readFile(String fileName) {
        if (!new File(fileName).exists())
            throw new IllegalArgumentException("No file: " + fileName);
        try {
            return doReadFile(fileName);
        } catch (FileNotFoundException e) {
            throw new IllegalStateException(e);
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }

    private static XYData doReadFile(String fileName) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        String line;
        XYData data = new XYData();
        while ((line = reader.readLine()) != null) {
            //process each line in some way
            Point3D xyz = Point3D.parseLine(line);
            data.addPoint(xyz);
        }
        FileLog.rlog("x range: " + data.getMinXValue() + " to " + data.getMaxXValue());
        FileLog.rlog("y range: " + data.getMinYValue() + " to " + data.getMaxYValue());
        return data;
    }
}
