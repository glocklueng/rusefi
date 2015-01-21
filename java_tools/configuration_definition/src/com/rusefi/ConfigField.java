package com.rusefi;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * (c) Andrey Belomutskiy
 * 1/15/15
 */
public class ConfigField {
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
        String typePattern = "[\\w\\d\\s_]+";
        String namePattern = "[[\\w\\d\\s_]]+";
        String commentPattern = "\\;([\\w\\d\\s_]*)";

        Pattern FIELD = Pattern.compile("(" + typePattern + ");(" + namePattern + ")(" + commentPattern + ")?");
        Matcher matcher = FIELD.matcher(line);
        if (!matcher.matches())
            return null;


        String[] b = line.split(";");
//        if (a.length != 2 && a.length != 3) {
//            System.err.println("Tow or three semicolon-separated elements expected");
//            return null;
//        }

        String name = matcher.group(2);
        String comment = matcher.group(4);
        ConfigField field = new ConfigField(name, comment);
        int arraySize;

        String type = matcher.group(1);
        if (type.startsWith("array ")) {
            String[] a = type.split(" ");
            type = a[1];
            field.arraySizeAsText = a[2];
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
        elementSize = ConfigDefinition.getElementSize(type);
    }
}
