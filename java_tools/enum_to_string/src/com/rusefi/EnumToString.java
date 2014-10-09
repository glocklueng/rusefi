package com.rusefi;

import java.io.*;
import java.util.HashSet;
import java.util.Set;

/**
 * (c) Andrey Belomutskiy
 * <p/>
 * 10/6/14
 */
@SuppressWarnings("StringConcatenationInsideStringBufferAppend")
public class EnumToString {
    private final static Set<String> currentValues = new HashSet<String>();

    private final static StringBuilder result = new StringBuilder();
    private final static StringBuilder header = new StringBuilder();

    public static void main(String[] args) throws IOException {
        header.append("#ifndef _A_H_HEADER_\r\n");
        header.append("#define _A_H_HEADER_\r\n");

        process("../../firmware/controllers/algo/io_pins.h");
        process("../../firmware/controllers/algo/rusefi_enums.h");

        header.append("#endif /*_A_H_HEADER_ */\r\n");

        writeResult("auto_generated_enums");
    }

    private static void writeResult(String outFileName) throws IOException {
        BufferedWriter bw = new BufferedWriter(new FileWriter(outFileName + ".cpp"));
        bw.write(result.toString());
        bw.close();

        bw = new BufferedWriter(new FileWriter(outFileName + ".h"));
        bw.write(header.toString());
        bw.close();
    }

    private static void process(String inFileName) throws IOException {
        BufferedReader reader;

        result.append("// auto-generated from" + inFileName + "\r\n\r\n\r\n");
        header.append("// auto-generated from" + inFileName + "\r\n\r\n\r\n");

        boolean isInsideEnum = false;

        File f = new File(inFileName);
        String simpleFileName = f.getName();

        result.append("#include \"main.h\"\r\n");
        result.append("#include \"" + simpleFileName + "\"\r\n");
        header.append("#include \"" + simpleFileName + "\"\r\n");

        reader = new BufferedReader(new FileReader(inFileName));
        String line;
        while ((line = reader.readLine()) != null) {
            line = line.replaceAll("\\s+", "");

            if (line.startsWith("typedefenum{")) {
                System.out.println("Entering enum");
                currentValues.clear();
                isInsideEnum = true;
            } else if (line.startsWith("}") && line.endsWith(";")) {
                isInsideEnum = false;
                line = line.substring(1, line.length() - 1);
                System.out.println("Ending enum " + line);
                result.append(makeCode(line));
                header.append(getMethodSignature(line) + ";\r\n");
            } else {
                line = line.replaceAll("//.+", "");
                if (isInsideEnum) {
                    if (line.matches("[a-zA-Z_$][a-zA-Z\\d_$]*[\\=a-zA-Z\\d_*]*,?")) {
                        line = line.replace(",", "");
                        int index = line.indexOf('=');
                        if (index != -1)
                            line = line.substring(0, index);
                        System.out.println("Line " + line);
                        currentValues.add(line);
                    }
                }
            }
        }
    }

    private static String makeCode(String enumName) {
        StringBuilder sb = new StringBuilder();
        sb.append(getMethodSignature(enumName) + "{\r\n");

        sb.append("switch(value) {\r\n");

        for (String e : currentValues) {
            sb.append("case " + e + ":\r\n");
            sb.append("  return \"" + e + "\";\r\n");
        }

        sb.append("  }\r\n");
        sb.append(" return NULL;\r\n");
        sb.append("}\r\n");

        return sb.toString();
    }

    private static String getMethodSignature(String enumName) {
        return "const char *get" + capitalize(enumName) + "(" + enumName + " value)";
    }

    private static String capitalize(String enumName) {
        return Character.toUpperCase(enumName.charAt(0)) + enumName.substring(1);
    }
}
