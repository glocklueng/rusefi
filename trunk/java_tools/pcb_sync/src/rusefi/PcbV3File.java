package rusefi;

import java.io.File;
import java.io.IOException;

/**
 * (c) Andrey Belomutskiy
 * 12/8/13
 */
public class PcbV3File {
    public static void main(String[] args) throws IOException {
        new File("output").mkdir();

        String content = CommonUtils.readFile("inj_6ch.kicad_pcb");
        PcbNode node = PcbNode.parse(content);

        System.out.println(node);

        node.move(97.917, -5.207);

        node.write("output" + File.separator + "inj_6ch.kicad_pcb");
    }
}
