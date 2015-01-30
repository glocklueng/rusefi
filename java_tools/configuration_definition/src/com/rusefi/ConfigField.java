package com.rusefi;

import com.rusefi.test.ConfigDefinitionTest;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * (c) Andrey Belomutskiy
 * 1/15/15
 */
public class ConfigField {
    public static final ConfigField VOID = new ConfigField(null, null, false, null, null, 1, null, false);

    private static final String typePattern = "([\\w\\d_]+)(\\[([\\w\\d]+)(\\s([\\w\\d]+))?\\])?";
    private static final String namePattern = "[[\\w\\d\\s_]]+";
    private static final String commentPattern = ";([^;]*)";

    private static final Pattern FIELD = Pattern.compile(typePattern + "\\s(" + namePattern + ")(" + commentPattern + ")?(;(.*))?");
    public static final int LENGTH = 24;

    public final String name;
    public final String comment;
    public final boolean isBit;
    public final String arraySizeAsText;
    public final String type;
    public final int arraySize;

    public final String tsInfo;
    public final int elementSize;
    public final boolean isIterate;

    public ConfigField(String name, String comment, boolean isBit, String arraySizeAsText, String type,
                       int arraySize, String tsInfo, boolean isIterate) {
        this.name = name;
        this.comment = comment;
        this.isBit = isBit;
        this.arraySizeAsText = arraySizeAsText;
        this.type = type;
        if (type == null) {
            elementSize = 0;
        } else {
            elementSize = TypesHelper.getElementSize(type);
        }
        this.arraySize = arraySize;
        this.tsInfo = tsInfo;
        this.isIterate = isIterate;
    }

    /**
     * @see ConfigDefinitionTest#testParseLine()
     */
    public static ConfigField parse(String line) {
        Matcher matcher = FIELD.matcher(line);
        if (!matcher.matches())
            return null;

        String name = matcher.group(6);
        String comment = matcher.group(8);
        String type = matcher.group(1);
        int arraySize;
        String arraySizeAsText;
        if (matcher.group(3) != null) {
            arraySizeAsText = matcher.group(3);
            arraySize = ConfigDefinition.getSize(arraySizeAsText);
        } else {
            arraySize = 1;
            arraySizeAsText = null;
        }
        String tsInfo = matcher.group(10);

        boolean isIterate = "iterate".equalsIgnoreCase(matcher.group(5));
        ConfigField field = new ConfigField(name, comment, false, arraySizeAsText, type, arraySize,
                tsInfo, isIterate);
        System.out.println("type " + type);
        System.out.println("name " + name);
        System.out.println("comment " + comment);

        return field;
    }

    int getSize(ConfigField next) {
        if (isBit && next.isBit)
            return 0;
        if (isBit)
            return 4;
        return elementSize * arraySize;
    }

    String getText(int currentOffset, int bitIndex) {
        if (isBit) {
            String comment = "\t/**\r\n" + ConfigDefinition.packComment(this.comment, "\t") + "\toffset " + currentOffset + " bit " + bitIndex + " */\r\n";
            return comment + "\tbool_t " + name + " : 1;\r\n";
        }

        String cEntry = ConfigDefinition.getComment(comment, currentOffset);

        if (arraySize == 1) {
            // not an array
            cEntry += "\t" + type + " " + name + ";\r\n";
        } else {
            cEntry += "\t" + type + " " + name + "[" + arraySizeAsText + "];\n";
        }
        return cEntry;
    }

    @Override
    public String toString() {
        return "ConfigField{" +
                "name='" + name + '\'' +
                ", type='" + type + '\'' +
                ", arraySize=" + arraySize +
                ", elementSize=" + elementSize +
                '}';
    }

    public int writeTunerStudio(String prefix, BufferedWriter tsHeader, int tsPosition, ConfigField next) throws IOException {
        ConfigStructure cs = ConfigDefinition.structures.get(type);
        if (cs != null) {
            String extraPrefix = cs.withPrefix ? name + "_" : "";
            return cs.writeTunerStudio(prefix + extraPrefix, tsHeader, tsPosition);
        }

        if (isBit) {
            tsHeader.write(";");
            tsHeader.write("\t" + addTabsUpTo(prefix + name, LENGTH));
            tsHeader.write("= bits,    U32,   ");
            tsHeader.write("\t" + tsPosition + ", [");
//            tsHeader.write(isBit);

            tsHeader.write("], \"false\", \"true\"");

            tsPosition += getSize(next);


        } else if (ConfigDefinition.tsCustomLine.containsKey(type)) {
            String bits = ConfigDefinition.tsCustomLine.get(type);
            tsHeader.write("\t" + addTabsUpTo(prefix + name, LENGTH));
            int size = ConfigDefinition.tsCustomSize.get(type);
//            tsHeader.write("\t" + size + ",");
            //          tsHeader.write("\t" + tsPosition + ",");
            bits = bits.replaceAll("@OFFSET@", "" + tsPosition);
            tsHeader.write("\t = " + bits);

            tsPosition += size;
        } else if (tsInfo == null) {
            tsHeader.write(";skipping " + prefix + name + " offset " + tsPosition);
            tsPosition += arraySize * TypesHelper.getElementSize(type);
        } else if (arraySize != 1) {
            tsHeader.write("\t" + addTabsUpTo(prefix + name, LENGTH) + "\t\t= array, ");
            tsHeader.write(TypesHelper.convertToTs(type) + ",");
            tsHeader.write("\t" + tsPosition + ",");
            tsHeader.write("\t[" + arraySize + "],");
            tsHeader.write("\t" + tsInfo);

            tsPosition += arraySize * elementSize;
        } else {
            tsHeader.write("\t" + addTabsUpTo(prefix + name, LENGTH) + "\t\t= scalar, ");
            tsHeader.write(TypesHelper.convertToTs(type) + ",");
            tsHeader.write("\t" + tsPosition + ",");
            tsHeader.write("\t" + tsInfo);
            tsPosition += elementSize;
        }
        tsHeader.write("\r\n");
        return tsPosition;
    }

    private String addTabsUpTo(String name, int length) {
        StringBuilder result = new StringBuilder(name);
        int currentLength = name.length();
        while (currentLength < length) {
            result.append("\t");
            currentLength += 4;
        }
        return result.toString();
    }
}
