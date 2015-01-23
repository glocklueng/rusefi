package com.rusefi;

import java.io.*;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

/**
 * (c) Andrey Belomutskiy
 * 1/12/15
 */
public class ConfigDefinition {
    private static final String FILE_NAME = "rusefi_config.ini";
    public static final String STRUCT = "struct ";
    public static final String END_STRUCT = "end_struct";
    public static final String BITS = "bits";
    private static Map<String, Integer> values = new HashMap<>();

    private static Stack<ConfigStructure> stack = new Stack<>();
    public static Map<String, ConfigStructure> types = new HashMap<>();
    public static Map<String, String> tsBits = new HashMap<>();
    public static Map<String, String> tsBitsType = new HashMap<>();

    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.out.println("Please specify path to '" + FILE_NAME + "' file");
            return;
        }

        String path = args[0];
        String fullFileName = path + File.separator + FILE_NAME;
        System.out.println("Reading from " + fullFileName);

        BufferedWriter cHeader = new BufferedWriter(new FileWriter("configuration.h_section"));
        BufferedWriter tsHeader = new BufferedWriter(new FileWriter("configuration.ts_section"));

        BufferedReader br = new BufferedReader(new FileReader(fullFileName));

        processFile(br, cHeader, tsHeader);

        if (!stack.isEmpty())
            throw new IllegalStateException("Unclosed structure: " + stack.peek().name);

        cHeader.close();
        tsHeader.close();
    }

    private static void processFile(BufferedReader br, BufferedWriter cHeader, BufferedWriter tsHeader) throws IOException {
        String line;

        String message = "// this section was generated by config_definition.jar on " + new Date() + "\r\n";
        cHeader.write(message);
        cHeader.write("// begin\r\n");

        while ((line = br.readLine()) != null) {
            line = line.trim();
            line = line.replaceAll("\\s+", " ");
            /**
             * we should ignore empty lines and comments
             */
            if (line.length() == 0 || line.startsWith("!"))
                continue;

            if (line.startsWith(STRUCT)) {
                handleStartStructure(line);
            } else if (line.startsWith(END_STRUCT)) {
                handleEndStruct(cHeader, tsHeader);
            } else if (line.startsWith(BITS + " ") || line.startsWith(BITS + "\t")) {
                line = line.substring(BITS.length() + 1).trim();
                int index = line.indexOf(' ');
                String name = line.substring(0, index);
                line = line.substring(index).trim();
                index = line.indexOf(' ');
                String bitsType = line.substring(0, index);

                String tunerStudioLine = line.substring(index).trim();
                tsBitsType.put(name, bitsType);
                tsBits.put(name, tunerStudioLine);

            } else {
                processLine(line);
            }
        }
        cHeader.write("// end\r\n");
        cHeader.write(message);
    }

    private static void handleStartStructure(String line) {
        line = line.substring(STRUCT.length());
        String name;
        String comment;
        if (line.contains(" ")) {
            int index = line.indexOf(' ');
            name = line.substring(0, index);
            comment = line.substring(index + 1).trim();
        } else {
            name = line;
            comment = null;
        }
        ConfigStructure structure = new ConfigStructure(name, comment);
        stack.push(structure);
        System.out.println("Starting structure " + structure.name);
    }

    private static void handleEndStruct(BufferedWriter cHeader, BufferedWriter tsHeader) throws IOException {
        if (stack.isEmpty())
            throw new IllegalStateException("Unexpected end_struct");
        ConfigStructure structure = stack.pop();
        System.out.println("Ending structure " + structure.name);
        structure.addAlignmentFill();
        structure.write(cHeader);

        if (stack.isEmpty()) {
            structure.writeTunerStudio("", tsHeader, 0);
        }
    }

    private static void processLine(String line) throws IOException {
        /**
         * for example
         * #define CLT_CURVE_SIZE 16
         */
        if (line.startsWith("#define")) {
            processDefine(line);
            return;
        }

        ConfigField cf = ConfigField.parse(line);
        if (cf == null)
            throw new IllegalStateException("Cannot process " + line);

        if (stack.isEmpty())
            throw new IllegalStateException(cf.name + ": Not enclosed in a struct");
        ConfigStructure structure = stack.peek();
        structure.add(cf);
    }

    public static String getComment(String comment, int currentOffset) {
        return "\t/**\r\n" + packComment(comment) + "\t * offset " + currentOffset + "\r\n\t*/\r\n";
    }

    public static String packComment(String comment) {
        if (comment == null)
            return "";
        if (comment.trim().isEmpty())
            return "";
        String result = "";
        for (String line : comment.split("\\\\n")) {
            result += "\t * " + line + "\r\n";
        }
        return result;
    }

    public static int getSize(String s) {
        if (values.containsKey(s))
            return values.get(s);
        return Integer.parseInt(s);
    }

    private static void processDefine(String line) {
        String a[] = line.split(" ");
        String key = a[1];
        int value = Integer.parseInt(a[2]);
        System.out.println("k [" + key + "] value: " + value);
        values.put(key, value);
    }
}
