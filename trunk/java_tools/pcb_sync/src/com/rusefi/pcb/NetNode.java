package com.rusefi.pcb;

import java.util.List;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class NetNode extends PcbNode {
    public final String net;

    public NetNode(String nodeName, int i, List<Object> children) {
        super(nodeName, i, children);
        net = getChild(0);
    }

    @Override
    public String toString() {
        return "NetNode{" +
                "net='" + net + '\'' +
                '}';
    }
}
