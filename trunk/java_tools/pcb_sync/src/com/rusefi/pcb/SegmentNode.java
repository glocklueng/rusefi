package com.rusefi.pcb;

import java.util.List;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class SegmentNode extends PcbNode {
    public final String net;
    //private final PointNode start;

    public SegmentNode(String nodeName, int closingIndex, List<Object> children) {
        super(nodeName, closingIndex, children);
        net = find("net").getChild(0);
     //   start = getPoint("start");)
    }
}
