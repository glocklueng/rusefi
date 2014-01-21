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
        if (children.size() == 1) {
            // xyz use-case
            x = 0;
            y = 0;
            return;
        }

        if (children.size() != 2 && children.size() != 3)
            throw new IllegalStateException("Unexpected children count");
        x = Double.parseDouble((String) children.get(0));
        y = Double.parseDouble((String) children.get(1));
    }

    @Override
    public String toString() {
        return "PointNode{" +
                "x=" + x +
                ", y=" + y +
                '}';
    }

    public boolean isSameLocation(PointNode point) {
        return x == point.x && y == point.y;
    }
}
