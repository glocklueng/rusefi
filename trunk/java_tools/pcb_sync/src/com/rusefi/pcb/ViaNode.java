package com.rusefi.pcb;

import java.util.List;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class ViaNode extends PcbNode {
    private final PointNode point;
    final SizeNode size;

    public ViaNode(String nodeName, int i, List<Object> children) {
        super(nodeName, i, children);
        point = (PointNode) find("at");
        size = (SizeNode) find("size");
    }

    @Override
    public String toString() {
        return "ViaNode{" +
                "point=" + point +
                '}';
    }

    @Override
    public boolean isConnected(PointNode point) {
        return point.isConnected(point, size);
    }
}
