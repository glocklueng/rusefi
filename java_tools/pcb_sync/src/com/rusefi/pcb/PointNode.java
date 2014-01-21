package com.rusefi.pcb;

import java.util.List;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class PointNode extends PcbNode {
    public final double x;
    public final double y;

    public PointNode(String nodeName, int i, List<Object> children) {
        super(nodeName, i, children);
        if (children.size() != 2)
            throw new IllegalStateException();
        x = Double.parseDouble((String) children.get(0));
        y = Double.parseDouble((String) children.get(1));
    }
}
