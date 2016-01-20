package com.rusefi.ui.config;

import java.util.ArrayList;
import java.util.List;

/**
 * (c) Andrey Belomutskiy
 * 1/17/2016.
 */
public class DialogModel {
    private final String key;
    private final String uiName;
    private final List<Field> fields;

    public DialogModel(String key, String uiName, List<Field> fields) {
        this.key = key;
        this.uiName = uiName;
        this.fields = new ArrayList<>(fields);
    }

    public List<Field> getFields() {
        return fields;
    }

    @Override
    public String toString() {
        return "DialogModel{" +
                "key='" + key + '\'' +
                ", uiName='" + uiName + '\'' +
                ", fields=" + fields.size() +
                '}';
    }

    public static class Field {
        private final String key;
        private final String uiName;

        public Field(String key, String uiName) {
            this.key = key;
            this.uiName = uiName;
        }

        public String getKey() {
            return key;
        }

        public String getUiName() {
            return uiName;
        }

        @Override
        public String toString() {
            return "Field{" +
                    "key='" + key + '\'' +
                    ", uiName='" + uiName + '\'' +
                    '}';
        }
    }
}
