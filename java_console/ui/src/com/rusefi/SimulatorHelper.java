package com.rusefi;

import java.io.File;

class SimulatorHelper {
    public static final String BINARY = "rusefi_simulator.exe";

    public static boolean isBinaryHere() {
        return new File(BINARY).exists();
    }
}