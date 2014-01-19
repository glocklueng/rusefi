package com.rusefi.misc;

import com.rusefi.pcb.PcbMergeTool;

import java.util.List;
import java.util.Set;
import java.util.TreeSet;

/**
 * 1/19/14
 * (c) Andrey Belomutskiy
 */
public class ChangesModel {
    private static final ChangesModel instance = new ChangesModel();

    public Set<String> DEL = new TreeSet<String>(String.CASE_INSENSITIVE_ORDER);

    public static ChangesModel getInstance() {
        return instance;
    }

    public void read(List<String> lines) {
        for (String line : lines) {
            line = line.trim();
            if (line.isEmpty())
                continue;
            DEL.add(line);
        }
        PcbMergeTool.log("Got " + DEL.size() + " delete entries");
    }
}
