package com.rusefi.bom;

import com.rusefi.util.FileUtils;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

/**
 * (c) Andrey Belomutskiy
 * 2/2/14
 */
public class BomBuilder {

    private static final Map<String, List<BomComponent>> componentsByKey = new TreeMap<String, List<BomComponent>>();
    private static final String DELIMITER = ",";


    public static void main(String[] args) throws IOException {
        if (args.length < 2) {

            System.out.println("bom_builder [FILE_NAME_CMP] COMPONENTS.CSV");

            return;
        }
        String cmpFileName = args[0];
        String bomDictionaryName = args[1];

        readList(FileUtils.readFileToList(cmpFileName));

        Map<String, BomRecord> bomDictionary = readBomDictionary(FileUtils.readFileToList(bomDictionaryName));


        BufferedWriter bw = new BufferedWriter(new FileWriter("output.csv"));

        for (Map.Entry<String, List<BomComponent>> e : componentsByKey.entrySet()) {
            String key = e.getKey();

            List<BomComponent> list = e.getValue();

            log(list.size() + " items of " + key);

            BomRecord bomRecord = bomDictionary.get(key);
            if (bomRecord == null) {
                log("No BOM record for " + key);
                continue;
            }
            bw.write(list.size() + DELIMITER +
                    bomRecord.getStorePart() + DELIMITER +
                    bomRecord.getCustomerRef() + "\r\n");


        }


        bw.close();

    }

    private static Map<String, BomRecord> readBomDictionary(List<String> strings) {
        Map<String, BomRecord> result = new HashMap<String, BomRecord>();
        for (String line : strings) {
            line = line.trim();
            if (line.isEmpty())
                continue;

            String[] tokens = line.split(";");

            if (tokens.length != 4) {
                log("Unexpected line: " + line);
                System.exit(-1);
            }

            String ref = tokens[0];
            String mfgPart = tokens[1];
            String storePart = tokens[2];
            String customerRef = tokens[3];
            result.put(ref, new BomRecord(mfgPart, storePart, customerRef));


            log("BOM key: " + ref);
            log("mfgPartNo: " + mfgPart);
            log("storePartNo: " + storePart);
        }

        log("Got " + result + " entries in BOM dictionary");

        return result;
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
