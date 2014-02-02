package com.rusefi.bom;

import com.rusefi.util.FileUtils;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * (c) Andrey Belomutskiy
 * 2/2/14
 */
public class BomBuilder {

    private static final Map<String, List<BomComponent>> componentsByKey = new TreeMap<String, List<BomComponent>>();


    public static void main(String[] args) throws IOException {
        if (args.length < 2) {

            System.out.println("bom_builder [FILE_NAME_CMP] COMPONENTS.CSV");

            return;
        }
        String cmpFileNae = args[0];

        readList(FileUtils.readFileToList(cmpFileNae));


        for (Map.Entry<String, List<BomComponent>> e : componentsByKey.entrySet()) {
            String key = e.getKey();

            List<BomComponent> list = e.getValue();

            log(list.size() + " items of " + key);


        }


    }

    private static void readList(List<String> list) throws IOException {

        for (int i = 0; i < list.size(); i++) {
            String line = list.get(i);
            if ("BeginCmp".equals(line)) {
                i += 2; // skipping 'TimeStamp' line

                String referenceLine = list.get(i++);
                String valueLine = list.get(i++);
                String packageLine = list.get(i++);

                String packageName = packageLine.split("=")[1].trim();
                packageName = cutLastSymbol(packageName);

                String value = valueLine.split("=")[1].trim();
                value = cutLastSymbol(value);

                String reference = referenceLine.split("=")[1].trim();
                reference = cutLastSymbol(reference);

                log("Reference: " + reference);
                log("value: " + value);
                log("package: " + packageName);

                String package_value = packageName + "_" + value;


                List<BomComponent> l = componentsByKey.get(package_value);
                if (l == null) {
                    l = new ArrayList<BomComponent>();
                    componentsByKey.put(package_value, l);
                }
                l.add(new BomComponent(reference));


            }


        }
    }

    private static String cutLastSymbol(String reference) {
        return reference.substring(0, reference.length() - 1);
    }

    private static void log(String msg) {
        System.out.println(msg);
    }
}
