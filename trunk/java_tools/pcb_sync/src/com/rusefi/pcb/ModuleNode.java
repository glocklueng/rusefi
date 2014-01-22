package com.rusefi.pcb;

import java.util.List;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class ModuleNode extends PcbNode {

    final List<PadNode> pads;
    public final PointNode at;

    public ModuleNode(String nodeName, int i, List<Object> children) {
        super(nodeName, i, children);
        Object o = iterate("pad");
        pads = (List<PadNode>) o;
        at = (PointNode) find("at");
    }

    @Override
    public String toString() {
        return "ModuleNode{" +
                "pads.size=" + pads.size() +
                '}';
    }

    @Override
    public boolean isConnected(PointNode point) {
        PointNode offsetPoint = point.substract(at);

        for (PadNode pad : pads) {
            if (pad.isConnected(offsetPoint))
                return true;
        }
        return false;
    }
}
