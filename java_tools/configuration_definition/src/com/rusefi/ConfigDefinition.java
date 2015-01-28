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
    public static final String CUSTOM = "custom";
    public static final String BIT = "bit";
    private static Map<String, Integer> values = new HashMap<>();

    private static Stack<ConfigStructure> stack = new Stack<>();
    public static Map<String, ConfigStructure> structures = new HashMap<>();
    public static Map<String, String> tsCustomLine = new HashMap<>();
    public static Map<String, Integer> tsCustomSize = new HashMap<>();

    public static void main(String[] args) throws IOException {
        if (args.length != 2) {
            System.out.println("Please specify path to '" + FILE_NAME + "' file and destination folder");
            return;
        }

        String path = args[0];
        String dest = args[1];
        String fullFileName = path + File.separator + FILE_NAME;
        System.out.println("Reading from " + fullFileName);
        String destCHeader = dest + File.separator + "engine_configuration_generated_structures.h";
        System.out.println("Writing C header to " + destCHeader);

        BufferedWriter cHeader = new BufferedWriter(new FileWriter(destCHeader));
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
        cHeader.write("#include \"rusefi_types.h\"\n");

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
            } else if (line.startsWith(BIT)) {
                line = line.substring(BIT.length() + 1).trim();

                String bitName;
                String comment;
                if (!line.contains(";")) {
                    bitName = line;
                    comment = "";
                } else {
                    int index = line.indexOf(";");
                    bitName = line.substring(0, index);
                    comment = line.substring(index + 1);
                }

                ConfigField cf = new ConfigField(bitName, comment);
                cf.isBit = true;
                stack.peek().add(cf);

            } else if (line.startsWith(CUSTOM + " ") || line.startsWith(CUSTOM + "\t")) {
                line = line.substring(CUSTOM.length() + 1).trim();
                int index = line.indexOf(' ');
                String name = line.substring(0, index);
                line = line.substring(index).trim();
                index = line.indexOf(' ');
                String customSize = line.substring(0, index);

                String tunerStudioLine = line.substring(index).trim();
                int size;
                try {
                    size = Integer.parseInt(customSize);
                } catch (NumberFormatException e) {
                    throw new IllegalStateException("Size in " + line);
                }
                tsCustomSize.put(name, size);
                tsCustomLine.put(name, tunerStudioLine);

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

        ConfigDefinition.structures.put(structure.name, structure);

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
        return "\t/**\r\n" + packComment(comment, "\t") + "\t * offset " + currentOffset + "\r\n\t */\r\n";
    }

    public static String packComment(String comment, String linePrefix) {
        if (comment == null)
            return "";
        if (comment.trim().isEmpty())
            return "";
        String result = "";
        for (String line : comment.split("\\\\n")) {
            result += linePrefix + " * " + line + "\r\n";
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
