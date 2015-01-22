package com.rusefi;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * (c) Andrey Belomutskiy
 * 1/15/15
 */
public class ConfigField {
    private static final String typePattern = "([\\w\\d_]+)(\\[([\\w\\d]+)\\])?";
    private static final String namePattern = "[[\\w\\d\\s_]]+";
    private static final String commentPattern = "\\;(.*)";

    private static final Pattern FIELD = Pattern.compile(typePattern + "\\s(" + namePattern + ")(" + commentPattern + ")?");

    public String type;
    public final String name;
    public final String comment;
    public String arraySizeAsText;
    public int arraySize;
    public int elementSize;

    public ConfigField(String name, String comment) {
        this.name = name;
        this.comment = comment;
    }

    public static ConfigField parse(String line) {
        Matcher matcher = FIELD.matcher(line);
        if (!matcher.matches())
            return null;

        String name = matcher.group(4);
        String comment = matcher.group(6);
        ConfigField field = new ConfigField(name, comment);
        int arraySize;

        String type = matcher.group(1);
        if (matcher.group(3) != null) {
            field.arraySizeAsText = matcher.group(3);
            arraySize = ConfigDefinition.getSize(field.arraySizeAsText);
        } else {
            arraySize = 1;
        }
        field.setType(type);
        field.arraySize = arraySize;

        System.out.println("type " + type);
        System.out.println("name " + name);
        System.out.println("comment " + comment);

        return field;
    }

    int getSize() {
        return elementSize * arraySize;
    }

    String getText(int currentOffset) {
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

    public void setType(String type) {
        this.type = type;
        elementSize = TypesHelper.getElementSize(type);
    }

    public int writeTunerStudio(BufferedWriter tsHeader, int tsPosition) throws IOException {
        tsHeader.write(name + "\t\t = ");

        if (ConfigDefinition.tsBits.containsKey(type)) {
            String bits = ConfigDefinition.tsBits.get(type);
            tsHeader.write("bits,\t");
            String type = ConfigDefinition.tsBitsType.get(this.type);
            tsPosition += TypesHelper.getTsSize(type);
            tsHeader.write(type);
            tsHeader.write(bits);
        }


        tsHeader.write("\r\n");

        return tsPosition;

    }

}
