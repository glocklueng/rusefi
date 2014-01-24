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
    public static final String REMOVE = "remove";
    private static final String ADD = "add";

    public final Set<String> DEL_REQUESTS = new TreeSet<String>(String.CASE_INSENSITIVE_ORDER);
    public final List<AddRequest> ADD_REQUESTS = new ArrayList<AddRequest>();

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
                addDelRequest(line.substring(REMOVE.length()).trim());
                continue;
            } else if (line.toLowerCase().startsWith(ADD)) {

                addAddRequest(line.substring(ADD.length()).trim());
                continue;


            }

            System.err.println("Ignoring invalid line: " + line);

        }
        PcbMergeTool.log("Got " + DEL_REQUESTS.size() + " remove request(s)");
        PcbMergeTool.log("Got " + ADD_REQUESTS.size() + " add request(s)");
    }

    private void addAddRequest(String request) {
        String[] tokens = request.split(" ");
        if (tokens.length == 1) {
            ADD_REQUESTS.add(new AddRequest(tokens[0], 0, 0));
        } else if (tokens.length == 3) {
            double x = Double.parseDouble(tokens[1]);
            double y = Double.parseDouble(tokens[1]);
            ADD_REQUESTS.add(new AddRequest(tokens[0], x, y));
        } else {
            throw new IllegalArgumentException("Invalid: " + request);
        }
    }

    private void addDelRequest(String request) {
        DEL_REQUESTS.add(request);
    }

    public void clear() {
        DEL_REQUESTS.clear();
    }
}
