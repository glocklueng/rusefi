package com.rusefi;

/**
 *
 * 1/22/15
 */
public class TypesHelper {
    static int getTsSize(String type) {
        if (type.equals("S16") || type.equals("U16"))
            return 2;
        if (type.equals("S32") || type.equals("U32"))
            return 4;
        throw new IllegalArgumentException("Unexpeted TS bits type: " + type);
    }

    public static int getElementSize(String type) {
        if (ConfigDefinition.types.containsKey(type))
            return ConfigDefinition.types.get(type).totalSize;
        if (type.equals(ConfigStructure.UINT8_T))
            return 1;
        if (type.equals("int16_t") || type.equals("uint16_t")) {
            return 2;
        }
        return 4;
    }
}
