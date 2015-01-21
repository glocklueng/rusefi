package com.rusefi;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * (c) Andrey Belomutskiy
 * 1/15/15
 */
public class ConfigStructure {
    public static final String UINT8_T = "uint8_t";
    public final String name;
    private final String comment;
    private final List<ConfigField> fields = new ArrayList<>();
    private int currentOffset;
    public int totalSize;

    public ConfigStructure(String name, String comment) {
        this.name = name;
        this.comment = comment;
    }

    public void write(BufferedWriter cHeader) throws IOException {
        if (comment != null) {
            cHeader.write("\t/**\r\n" + ConfigDefinition.packComment(comment) + "\r\n\t*/\r\n");
        }
        cHeader.write("typedef struct {\r\n");

        for (ConfigField cf : fields) {
            cHeader.write(cf.getText(currentOffset));
            currentOffset += cf.getSize();
        }

        cHeader.write("/** total size " + currentOffset + "*/\r\n");
        cHeader.write("} " + name + ";\r\n\r\n");
    }

    public void add(ConfigField cf) {
        fields.add(cf);
    }

    public void addAlignmentFill() {
        for (ConfigField cf : fields)
            totalSize += cf.getSize();

        int fillSize = totalSize % 4 == 0 ? 0 : 4 - (totalSize % 4);

        if (fillSize != 0) {
            ConfigField fill = new ConfigField("alignmentFill", "need 4 byte alignment");
            fill.arraySize = fillSize;
            fill.setType(UINT8_T);
            fill.arraySizeAsText = "" + fillSize;
            add(fill);
        }
        totalSize += fillSize;

        ConfigDefinition.types.put(name, this);
    }
}
