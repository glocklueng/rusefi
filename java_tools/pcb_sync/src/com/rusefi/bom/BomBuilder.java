package com.rusefi.bom;

import com.rusefi.util.FileUtils;

import java.io.IOException;
import java.util.List;

/**
 * (c) Andrey Belomutskiy
 * 2/2/14
 */
public class BomBuilder {
    public static void main(String[] args) throws IOException {
        if (args.length < 2) {

            System.out.println("bom_builder [FILE_NAME_CMP] COMPONENTS.CSV");

            return;
        }
        String cmpFileNae = args[0];

        List<String> list = FileUtils.readFileToList(cmpFileNae);



    }
}
