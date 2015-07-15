package com.rusefi.ui.config;

import com.rusefi.ConfigurationImage;
import com.rusefi.config.Field;
import com.rusefi.core.MessagesCentral;
import com.rusefi.core.Pair;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class EnumConfigField extends BaseConfigField {
    private final JComboBox<String> view = new JComboBox<>();
    private boolean ec;
    private final Map<String, Integer> ordinals = new HashMap<>();
    private final String[] options = field.getOptions();

    public EnumConfigField(final Field field, String caption) {
        super(field);
        if (options == null)
            throw new NullPointerException("options for " + field);
        createUi(caption, view);

        int ordinal = 0;
        for (String option : options) {
            ordinals.put(option, ordinal++);

            if (!"invalid".equalsIgnoreCase(option))
                view.addItem(option);
        }

        requestInitialValue(field); // this is not in base constructor so that view is created by the time we invoke it

        MessagesCentral.getInstance().addListener(new MessagesCentral.MessageListener() {
            @Override
            public void onMessage(Class clazz, String message) {
                if (Field.isIntValueMessage(message)) {
                    Pair<Integer, ?> p = Field.parseResponse(message);
                    if (p != null && p.first == field.getOffset()) {
                        int ordinal = (Integer) p.second;
                        setValue(ordinal);
                    }
                }
            }
        });

        view.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (ec)
                    return;
                String value = (String) view.getSelectedItem();
                int ordinal = ordinals.get(value);
                sendValue(field, Integer.toString(ordinal));
            }
        });
    }

    private void setValue(int ordinal) {
        String item;
        if (ordinal >= options.length) {
            item = "unexpected_" + ordinal;
            view.addItem(item);
        } else {
            item = options[ordinal];
        }

        ec = true;
        view.setEnabled(true);
        view.setSelectedItem(item);
        onValueArrived();
        ec = false;
    }

    @Override
    protected void loadValue(ConfigurationImage ci) {
        int ordinal = getByteBuffer(ci).getInt();
        setValue(ordinal);
    }
}