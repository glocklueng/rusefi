package com.rusefi.misc;

import com.rusefi.pcb.PcbNode;

import java.io.IOException;
import java.util.List;

/**
 * @author Andrey Belomutskiy
 *         1/21/14
 */
public class RemoveUnneededTraces {
    public static void main(String[] args) throws IOException {

        PcbNode destNode = PcbNode.readFromFile("test.kicad_pcb");

        List<PcbNode> segments = destNode.iterate("segment");

        System.out.println(segments.size() + " segment(s)");

        for (PcbNode segment : segments) {

        }


        // for(PcbNode segment : )


    }
}
