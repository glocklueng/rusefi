package com.rusefi.misc;

/**
 * @author Andrey Belomutskiy
 *         1/24/14
 */
public class AddRequest {
    public final String fileName;
    public final double x;
    public final double y;

    public AddRequest(String fileName, double x, double y) {
        this.fileName = fileName;
        this.x = x;
        this.y = y;
    }
}
