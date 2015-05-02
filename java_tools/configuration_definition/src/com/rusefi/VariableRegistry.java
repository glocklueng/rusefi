package com.rusefi;

import java.util.TreeMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * 3/30/2015
 */
public class VariableRegistry extends TreeMap<String, String> {
    public static final VariableRegistry INSTANCE = new VariableRegistry();

    private final Pattern VAR = Pattern.compile("(@@(.*?)@@)");

    private VariableRegistry() {
    }

    public String processLine(String line) {
        Matcher m;
        while ((m = VAR.matcher(line)).find()) {
            String key = m.group(2);


       //     key =

            if (!containsKey(key))
                throw new IllegalStateException("No such variable: " + key);
            String s = get(key);
            line = m.replaceFirst(s);
        }
        return line;
    }

    public void register(String var, String value) {
        System.out.println("Registering " + var + " as " + value);
        put(var, value);
    }

    public void register(String var, int i) {
        register(var, Integer.toString(i));
        register(var + "_hex", Integer.toString(i, 16));
    }
}
