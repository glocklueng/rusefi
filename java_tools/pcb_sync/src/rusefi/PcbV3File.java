package rusefi;

import java.io.File;
import java.io.IOException;

/**
 * (c) Andrey Belomutskiy
 * 12/8/13
 */
public class PcbV3File {
    public static void main(String[] args) throws IOException {
        if (args.length != 3) {
            System.out.println("Three parameters expected: FILENAME X Y");
            return;
        }
        String fileName = args[0];
        double x = Double.parseDouble(args[1]);
        double y = Double.parseDouble(args[2]);


        new File("output").mkdir();

        String content = CommonUtils.readFile(fileName);
        PcbNode node = PcbNode.parse(content);

        System.out.println(node);

        node.move(x, y);
        node.write("output" + File.separator + fileName);
    }
}
