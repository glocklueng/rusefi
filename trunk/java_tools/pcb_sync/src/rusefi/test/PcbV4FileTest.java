package rusefi.test;

import org.junit.Test;
import rusefi.PcbNode;

import static org.junit.Assert.assertEquals;

/**
 * (c) Andrey Belomutskiy
 * 12/8/13
 */
public class PcbV4FileTest {
    @Test
    public void testParser() {
        PcbNode n = PcbNode.parse("(version 3\r\n)");
        assertEquals("version", n.nodeName);
        assertEquals(1, n.children.size());

        assertEquals("(version 3)\r\n", n.pack());


        n = PcbNode.parse("(host pcbnew \"(2013-07-07 BZR 4022)-stable\")");
        assertEquals(2, n.children.size());
        assertEquals("pcbnew", n.children.get(0));
        assertEquals("\"(2013-07-07 BZR 4022)-stable\"", n.children.get(1));


        n = PcbNode.parse("(area 68.835001 116.9924 170.180001 180.5)");
        assertEquals(4, n.children.size());

        n = PcbNode.parse("(kicad_pcb\n (version 3)\r\n (host pcbnew \"(2013-07-07 BZR 4022)-stable\")\n)");
        assertEquals(2, n.children.size());
        assertEquals("(kicad_pcb\r\n" +
                " (version 3)\r\n" +
                "\r\n" +
                " (host pcbnew \"(2013-07-07 BZR 4022)-stable\")\r\n" +
                ")\r\n", n.pack());
    }
}
