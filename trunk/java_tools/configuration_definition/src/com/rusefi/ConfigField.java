package com.rusefi;

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

    private ConfigField(String name, String comment) {
        this.name = name;
        this.comment = comment;
    }

    public static ConfigField parse(String line) {
        String[] a = line.split(";");
        if (a.length != 2 && a.length != 3) {
            System.err.println("Tow or three semicolon-separated elements expected");
            return null;
        }

        String name = a[1];
        String comment = a.length == 3 ? a[2] : "";
        ConfigField field = new ConfigField(name, comment);
        int arraySize;

        String type = a[0];
        if (type.startsWith("array ")) {
            a = type.split(" ");
            type = a[1];
            field.arraySizeAsText = a[2];
            arraySize = ConfigDefinition.getSize(field.arraySizeAsText);
        } else {
            arraySize = 1;
        }
        field.arraySize = arraySize;
        field.elementSize = ConfigDefinition.getElementSize(type);

        System.out.println("type " + type);
        System.out.println("name " + name);
        System.out.println("comment " + comment);

        return field;
    }

    int getSize() {
        return elementSize * arraySize;
    }

    String getText() {
        String cEntry = ConfigDefinition.getComment(comment);

        if (arraySize == 1) {
            // not an array
            cEntry += "\t" + type + " " + name + ";\r\n";
        } else {
            cEntry += "\t" + type + " " + name + "[" + arraySizeAsText + "];\n";
        }
        return cEntry;
    }
}
