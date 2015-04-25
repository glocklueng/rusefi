package com.rusefi.config;

import com.rusefi.core.Pair;

/**
 * @see com.rusefi.config.Fields
 */

public class Field {
    private static final String BIT_VALUE_PREFIX = "bit @";
    private static final String INT_VALUE_PREFIX = "int @";
    private static final String FLOAT_VALUE_PREFIX = "float @";
    public static final int NO_BIT_OFFSET = -1;

    private final int offset;
    private final FieldType type;
    private final int bitOffset;
    private final String[] options;

    public Field(int offset, FieldType type) {
        this(offset, type, NO_BIT_OFFSET);
    }

    public Field(int offset, FieldType type, String... options) {
        this(offset, type, NO_BIT_OFFSET, options);
    }

    public Field(int offset, FieldType type, int bitOffset) {
        this(offset, type, bitOffset, null);
    }

    public Field(int offset, FieldType type, int bitOffset, String[] options) {
        this.offset = offset;
        this.type = type;
        this.bitOffset = bitOffset;
        this.options = options;
    }

    public String setCommand() {
        if (type == FieldType.BIT)
            return "set_bit " + getOffset() + " " + bitOffset;
        return getType().getStoreCommand() + " " + getOffset();
    }

    public String getCommand() {
        if (type == FieldType.BIT)
            return "get_bit " + getOffset() + " " + bitOffset;
        return type.getLoadCommand() + " " + getOffset();
    }

    public int getOffset() {
        return offset;
    }

    public String[] getOptions() {
        return options;
    }

    public int getBitOffset() {
        return bitOffset;
    }

    public FieldType getType() {
        return type;
    }

    public static boolean isIntValueMessage(String message) {
        return message.startsWith(INT_VALUE_PREFIX);
    }

    public static boolean isBitValueMessage(String message) {
        return message.startsWith(BIT_VALUE_PREFIX);
    }

    public static boolean isFloatValueMessage(String message) {
        return message.startsWith(FLOAT_VALUE_PREFIX);
    }

    public static Pair<Integer, ?> parseResponse(String message) {
        try {
            if (isIntValueMessage(message)) {
                message = message.substring(INT_VALUE_PREFIX.length());
                String[] a = message.split(" is ");
                if (a.length != 2)
                    return null;
                int index = Integer.parseInt(a[0]);
                int value = Integer.parseInt(a[1]);
                return new Pair<>(index, value);
            }
            if (isFloatValueMessage(message)) {
                message = message.substring(FLOAT_VALUE_PREFIX.length());
                String[] a = message.split(" is ");
                if (a.length != 2)
                    return null;
                int index = Integer.parseInt(a[0]);
                double value = Double.parseDouble(a[1]);
                return new Pair<>(index, value);
            }
            return null;
        } catch (NumberFormatException e) {
            return null;
        }
    }
}