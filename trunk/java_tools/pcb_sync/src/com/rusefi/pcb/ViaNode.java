package com.rusefi.pcb;

import java.util.List;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class ViaNode extends PcbNode {
    private final PointNode location;
    final SizeNode size;

    public ViaNode(String nodeName, int i, List<Object> children) {
        super(nodeName, i, children);
        location = (PointNode) find("at");
        size = (SizeNode) find("size");
    }

    @Override
    public String toString() {
        return "ViaNode{" +
                "location=" + location +
                '}';
    }

    @Override
    public boolean isConnected(PointNode point) {
        return point.isConnected(location, size);
    }
}
