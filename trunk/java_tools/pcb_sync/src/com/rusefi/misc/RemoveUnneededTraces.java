package com.rusefi.misc;

import com.rusefi.pcb.PcbNode;
import com.rusefi.pcb.PointNode;
import com.rusefi.pcb.SegmentNode;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class RemoveUnneededTraces {
    public static void main(String[] args) throws IOException {
        PcbNode destNode = PcbNode.readFromFile("test.kicad_pcb");

        Object o = destNode.iterate("module");
        List<PcbNode> modules = (List<PcbNode>) o;

        while (removeUnusedSegments(destNode, modules)) {
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
        }
        return !unused.isEmpty();
    }

    private static List<SegmentNode> findUnusedSegments(List<SegmentNode> segments, List<PcbNode> modules) {
        List<SegmentNode> unused = new ArrayList<SegmentNode>();
        for (SegmentNode segment : segments) {
            if (isUnused(segments, segment, modules))
                unused.add(segment);
        }
        return unused;
    }

    private static boolean isUnused(List<SegmentNode> segments, SegmentNode segment, List<PcbNode> modules) {
        PointNode start = segment.start;
        if (!isConnected(start, segments, segment) && !isConnected(start, modules, null)) {
            System.out.println("Not connected start: " + segment);
            return true;
        }

        PointNode end = segment.end;
        if (!isConnected(end, segments, segment) && !isConnected(end, modules, null)) {
            System.out.println("Not connected end: " + segment);
            return true;
        }
        return false;
    }

    private static boolean isConnected(PointNode point, List<? extends PcbNode> elements, SegmentNode parent) {
        for (PcbNode segmentNode : elements) {
            if (segmentNode == parent)
                continue;

            if (segmentNode.isConnected(point))
                return true;
        }
        return false;
    }
}
