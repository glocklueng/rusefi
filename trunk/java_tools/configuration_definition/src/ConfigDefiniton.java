import java.io.*;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * (c) Andrey Belomutskiy
 * 1/12/15.
 */
public class ConfigDefiniton {
    private static final String FILE_NAME = "rusefi_config.ini";
    private static Map<String, Integer> values = new HashMap<>();
    private static int currentOffset;

    public static void main(String[] args) throws IOException {
        currentOffset = 0;
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

        cHeader.close();
        tsHeader.close();

    }

    private static void processFile(BufferedReader br, BufferedWriter cHeader, BufferedWriter tsHeader) throws IOException {
        String line;

        String message = "// this section was generated by config_definition.jar on " + new Date() + "\r\n";
        cHeader.write(message);
        cHeader.write("// begin\r\n");


        while ((line = br.readLine()) != null) {
            processLine(cHeader, line);

        }
        cHeader.write("// end\r\n");
        cHeader.write(message);
    }

    private static void processLine(BufferedWriter cHeader, String line) throws IOException {
        line = line.trim();
        line = line.replaceAll("\\s+", " ");
        if (line.startsWith("!"))
            return;
        if (line.length() == 0)
            return;

        if (line.startsWith("#define")) {
            processDefine(line);
            return;
        }


        String[] a = line.split(";");
        if (a.length != 2 && a.length != 3) {
            System.err.println("Tow or three semicolon-separated elements expected");
            return;
        }
        String type = a[0];
        String name = a[1];
        String comment = a.length == 3 ? a[2] : "";
        int arraySize = 1;
        System.out.println("type " + type);
        System.out.println("name " + name);
        System.out.println("comment " + comment);

        int elementSize = getElementSize(type);
        String arraySizeAsText = "";

        if (type.startsWith("array ")) {
            a = type.split(" ");
            type = a[1];
            arraySizeAsText = a[2];
            arraySize = getSize(arraySizeAsText);
        }


        String cEntry = getComment(comment);

        if (arraySize == 1) {
            // not an array
            cEntry += "\t" + type + " " + name + ";\r\n";
        } else {
            cEntry += "\t" + type + " " + name + "[" + arraySizeAsText + "];\n";
        }

        cHeader.write(cEntry);

        currentOffset += elementSize * arraySize;
    }

    private static int getElementSize(String type) {
        if (type.equals("int16_t")) {
            return 2;
        }
        return 4;
    }

    private static String getComment(String comment) {
        return "\t/**\r\n\t * " + comment + "\r\n\t * offset " + currentOffset + "\r\n\t*/\r\n";
    }

    private static int getSize(String s) {
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
