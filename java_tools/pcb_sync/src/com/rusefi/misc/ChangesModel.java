package com.rusefi.misc;

import com.rusefi.pcb.PcbMergeTool;
import com.rusefi.util.FileUtils;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

/**
 * 1/19/14
 * (c) Andrey Belomutskiy
 */
public class ChangesModel {
    private static final ChangesModel instance = new ChangesModel();
    private static final String REMOVE = "remove";
    private static final String ADD = "add";
    private static final String OPTIMIZE = "optimize";
    private static final String COPY = "copy";

    public final Set<String> DEL_REQUESTS = new TreeSet<String>(String.CASE_INSENSITIVE_ORDER);
    public final List<AddRequest> ADD_REQUESTS = new ArrayList<AddRequest>();

    public final List<TwoFileRequest> OPTIMIZE_REQUESTS = new ArrayList<TwoFileRequest>();
    public final List<TwoFileRequest> COPY_REQUESTS = new ArrayList<TwoFileRequest>();

    public static ChangesModel getInstance() {
        return instance;
    }

    public static void readConfiguration() throws IOException {
        String changesFileName = "pcb_merge_changes.txt";
        if (new File(changesFileName).isFile()) {
            List<String> a = FileUtils.readFileToList(changesFileName);

            getInstance().read(a);
        }
    }

    public void read(List<String> lines) {
        for (String line : lines) {
            line = line.trim();
            if (line.isEmpty())
                continue;
            if (line.startsWith("#"))
                continue; // this line is a comment

            if (line.toLowerCase().startsWith(REMOVE)) {
                DEL_REQUESTS.add(line.substring(REMOVE.length()).trim());
                continue;
            } else if (line.toLowerCase().startsWith(ADD)) {
                addAddRequest(line.substring(ADD.length()).trim());
                continue;
            } else if (line.toLowerCase().startsWith(OPTIMIZE)) {
                OPTIMIZE_REQUESTS.add(parseTwoFile(line.substring(OPTIMIZE.length()).trim()));
                continue;
            } else if (line.toLowerCase().startsWith(COPY)) {
                COPY_REQUESTS.add(parseTwoFile(line.substring(COPY.length()).trim()));
                continue;
            }

            System.err.println("Ignoring invalid line: " + line);

        }
        PcbMergeTool.log("Got " + DEL_REQUESTS.size() + " remove request(s)");
        PcbMergeTool.log("Got " + ADD_REQUESTS.size() + " add request(s)");
        PcbMergeTool.log("Got " + OPTIMIZE_REQUESTS.size() + " optimize request(s)");
    }

    private TwoFileRequest parseTwoFile(String request) {
        String[] tokens = request.split(" ");
        if (tokens.length != 2)
            throw new IllegalArgumentException("req " + request);

        return new TwoFileRequest(tokens[0], tokens[1]);
    }

    private void addAddRequest(String request) {
        String[] tokens = request.split(" ");
        if (tokens.length == 1) {
            ADD_REQUESTS.add(new AddRequest(tokens[0], 0, 0));
        } else if (tokens.length == 3) {
            double x = Double.parseDouble(tokens[1]);
            double y = Double.parseDouble(tokens[2]);
            ADD_REQUESTS.add(new AddRequest(tokens[0], x, y));
        } else {
            throw new IllegalArgumentException("Invalid: " + request);
        }
    }

    public void clear() {
        DEL_REQUESTS.clear();
        ADD_REQUESTS.clear();
        OPTIMIZE_REQUESTS.clear();
    }
}
