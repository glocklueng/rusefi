package rusefi;

import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * 12/8/13
 * (c) Andrey Belomutskiy
 */
public class NetListMerge {
    private static final Pattern PATTERN = Pattern.compile("(.*)\\(components(.*)\\)\\).*", Pattern.DOTALL);

    private NetListMerge() {
    }

    public static void main(String[] args) throws IOException {
        if (args.length < 2) {
            System.out.println("This tool takes 'components' sections of multiple KiCad .net files and merges them into one");
            System.out.println("usage:");
            System.out.println("NetListMerge DEST_FILE SOURCE_1 SOURCE_2 [SOURCE_x]*");
            return;
        }

        String destinationFile = args[0];
        NetContent destination = parse(readFile(destinationFile));

        StringBuilder result = new StringBuilder(destination.header);
        result.append("  (components");
        for (int i = 1; i < args.length; i++) {
            String sourceFile = args[i];
            NetContent source = parse(readFile(sourceFile));
            result.append(source.components);
        }
        result.append("))");

        writeResult(result.toString());
    }

    private static void writeResult(String content) throws IOException {
        BufferedWriter bw = new BufferedWriter(new FileWriter("out.txt"));
        bw.write(content);
        bw.close();
    }

    private static String readFile(String fileName) throws IOException {
        checkExistence(fileName);

        System.out.println("Reading " + fileName);
        StringBuilder sb = new StringBuilder();
        String line;
        BufferedReader br = new BufferedReader(new FileReader(fileName));

        while (((line = br.readLine()) != null))
            sb.append(line).append("\r\n");
        return sb.toString();
    }

    private static void checkExistence(String fileName) {
        if (!new File(fileName).isFile()) {
            System.err.println("File not found: " + fileName);
            System.exit(-1);
        }
    }

    private static class NetContent {
        private final String header;
        private final String components;

        private NetContent(String header, String components) {
            this.header = header;
            this.components = components;
        }
    }

    private static NetContent parse(String content) {
        Matcher m = PATTERN.matcher(content);
        m.find();
        System.out.println(m.matches());

        String header = m.group(1);
        System.out.println("Header: " + header);

        String components = m.group(2);
        System.out.println("components: " + components);

        return new NetContent(header, components);
    }
}
