package com.rusefi.misc;

import com.rusefi.pcb.PcbNode;
import com.rusefi.pcb.PointNode;
import com.rusefi.pcb.SegmentNode;

import java.io.IOException;
import java.util.List;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class RemoveUnneededTraces {
    public static void main(String[] args) throws IOException {

        PcbNode destNode = PcbNode.readFromFile("test.kicad_pcb");

        Object o = destNode.iterate("segment");
        List<SegmentNode> segments = (List<SegmentNode>) o;

        System.out.println(segments.size() + " segment(s)");

        for (SegmentNode segment : segments) {

            if (!isConnected(segment.start, segments, segment))
                System.out.println("Not connected: " + segment);


        }


        // for(PcbNode segment : )


    }

    private static boolean isConnected(PointNode point, List<SegmentNode> segments, SegmentNode parent) {
        for (SegmentNode segmentNode : segments) {
            if (segments == parent)
                continue;

            if (segmentNode.start.isSameLocation(point) || segmentNode.end.isSameLocation(point))
                return true;
        }


        return false;
    }
}
