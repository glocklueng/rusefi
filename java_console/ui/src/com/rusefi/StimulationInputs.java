package com.rusefi;

import com.irnems.Launcher;

import javax.swing.*;
import java.awt.*;

/**
 * 8/13/14
 * (c) Andrey Belomutskiy
 */
public class StimulationInputs {

    private final JPanel content = new JPanel(new GridLayout(12, 1));

    private final JSpinner loadEngineMin = new JSpinner(new SpinnerNumberModel(1.0, 0.0, 5.0, 0.1));
    private final JSpinner loadEngineMax = new JSpinner(new SpinnerNumberModel(4.0, 0.0, 5.0, 0.1));

    public StimulationInputs(EcuStimulator ecuStimulator) {
        content.add(new JLabel("Engine load from"));
        content.add(wrap(loadEngineMin));

        content.add(new JLabel("Engine load to"));
        content.add(wrap(loadEngineMax));

        JButton button = ecuStimulator.createButton();
        if (Launcher.SHOW_STIMULATOR)
            content.add(wrap(button));
    }

    public double getEngineLoadMin() {
        return (Double) loadEngineMin.getValue();
    }

    public double getEngineLoadMax() {
        return (Double) loadEngineMax.getValue();
    }

    private static Component wrap(JComponent component) {
        JPanel result = new JPanel();
        result.add(component);
        return result;
    }

    public JPanel getContent() {
        return content;
    }
}

