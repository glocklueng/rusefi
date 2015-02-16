package com.rusefi.config;

import com.rusefi.core.Pair;

import java.util.Objects;

public class Field {
    private static final String INT_VALUE_PREFIX = "int @";

    private final int offset;

    public Field(int offset) {
        this.offset = offset;
    }

    public int getOffset() {
        return offset;
    }

    public static boolean isIntValueMessage(String message) {
        return message.startsWith(INT_VALUE_PREFIX);
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
            return null;
        } catch (NumberFormatException e) {
            return null;
        }
    }
}