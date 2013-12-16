package com.rusefi.pcb;

import java.io.File;
import java.io.IOException;

/**
 * (c) Andrey Belomutskiy
 * 12/16/13.
 */
public class PcbMergeTool {
    public static void main(String[] args) throws IOException {
        if (args.length < 2) {
            System.out.println("At least two parameters expected: DEST_FILENAME SOURCE1 SOURCE2");
            return;
        }

        String destFileName = args[0];

        PcbNode destNode = PcbNode.readFromFile(destFileName);

        for (int i = 1; i < args.length; i++) {

            PcbNode source = PcbNode.readFromFile(args[i]);

            for (PcbNode module : source.iterate("module")) {
                destNode.addChild(module);

            }


        }


        destNode.write("output" + File.separator + destFileName);
    }

}
