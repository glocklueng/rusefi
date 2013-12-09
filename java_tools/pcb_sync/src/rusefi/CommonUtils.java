package rusefi;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

/**
 * 12/9/13
 * (c) Andrey Belomutskiy
 */
public class CommonUtils {
    private CommonUtils() {
    }

    static String readFile(String fileName) throws IOException {
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
}
