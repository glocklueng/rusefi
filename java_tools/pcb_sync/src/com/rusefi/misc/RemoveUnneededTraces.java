package com.rusefi.misc;

import com.rusefi.pcb.PcbNode;
import com.rusefi.pcb.PointNode;
import com.rusefi.pcb.SegmentNode;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class RemoveUnneededTraces {
    private final static Set<String> alreadyRemoved = new HashSet<String>();

    public static void main(String[] args) throws IOException {
        PcbNode destNode = PcbNode.readFromFile("test.kicad_pcb");

        List<PcbNode> modules = destNode.iterate("module");
        List<PcbNode> stuff = new ArrayList<PcbNode>(modules);
        stuff.addAll(destNode.iterate("via"));

        while (removeUnusedSegments(destNode, stuff)) {
            System.out.println("Still removing...");
        }

        destNode.write("output.kicad_pcb");
    }

    private static boolean removeUnusedSegments(PcbNode destNode, List<PcbNode> modules) {
        Object o = destNode.iterate("segment");
        List<SegmentNode> segments = (List<SegmentNode>) o;
        System.out.println(segments.size() + " segment(s)");

        List<SegmentNode> unused = findUnusedSegments(segments, modules);
        for (SegmentNode segment : unused) {
            boolean removed = destNode.removeChild(segment);
            if (!removed)
                throw new IllegalStateException();
            String netName = segment.net.id;
            if (!alreadyRemoved.contains(netName)) {
                alreadyRemoved.add(netName);
                System.out.println("Unused segment in network " + netName + ": " + segment);
            }
        }
        return !unused.isEmpty();
    }

    private static List<SegmentNode> findUnusedSegments(List<SegmentNode> segments, List<PcbNode> modules) {
        List<SegmentNode> unused = new ArrayList<SegmentNode>();
        for (SegmentNode segment : segments) {
            if (isUnused(segments, segment, modules)) {
//                System.out.println("Unused on " + segment.net.id + ": " + segment);
                unused.add(segment);
            }
        }
        return unused;
    }

    public static boolean isUnused(List<SegmentNode> segments, SegmentNode segment, List<PcbNode> modules) {
        PointNode start = segment.start;
        PointNode end = segment.end;
        if (isConnected(start, segments, segment) == null && isConnected(start, modules, null) == null) {
            System.out.println("Not connected start: " + segment);
            return true;
        }

        PcbNode endModule = isConnected(end, modules, null);
        if (isConnected(end, segments, segment) == null && endModule == null) {
            System.out.println("Not connected end: " + segment);
            return true;
        }
        return false;
    }

    private static PcbNode isConnected(PointNode point, List<? extends PcbNode> elements, SegmentNode parent) {
        for (PcbNode segmentNode : elements) {
            if (segmentNode == parent)
                continue;

            if (segmentNode.isConnected(point))
                return segmentNode;
        }
        return null;
    }
}
