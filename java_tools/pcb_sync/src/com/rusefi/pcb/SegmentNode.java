package com.rusefi.pcb;

import java.util.List;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class SegmentNode extends PcbNode {
    public final NetNode net;
    public final PointNode start;
    public final PointNode end;

    public SegmentNode(String nodeName, int closingIndex, List<Object> children) {
        super(nodeName, closingIndex, children);
        net = (NetNode) find("net");
        start = (PointNode) find("start");
        end = (PointNode) find("end");
    }

    public boolean isConnected(PointNode point) {
        return start.isSameLocation(point) || end.isSameLocation(point);
    }

    @Override
    public String toString() {
        return "SegmentNode{" +
                "net=" + net +
                ", start=" + start +
                ", end=" + end +
                '}';
    }
}
