package com.rusefi.pcb;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

/**
 * (c) Andrey Belomutskiy
 * 12/16/13.
 */
public class PcbMergeTool {

    static Networks networks = new Networks();

    public static void main(String[] args) throws IOException {
        if (args.length < 2) {
            System.out.println("At least two parameters expected: DEST_FILENAME SOURCE1 SOURCE2");
            return;
        }

        String destFileName = args[0];

        PcbNode destNode = PcbNode.readFromFile(destFileName);

        for (int i = 1; i < args.length; i++)
             mergePcb(args[i], destNode);

        destNode.write("output" + File.separator + destFileName);
    }

    private static void mergePcb(String fileName, PcbNode destNode) throws IOException {
        PcbNode source = PcbNode.readFromFile(fileName);

        Map<String, String> netNameMapping = new HashMap<String, String>();
        Map<String, Integer> netIdMapping = new HashMap<String, Integer>();

        for (PcbNode net : source.iterate("net")) {
            String netId = net.getChild(0);
            String netName = net.getChild(1);
            String newName = networks.registerNetworkIfPcbSpecific(netName);
            netNameMapping.put(netName, newName);
            netIdMapping.put(netId, networks.getId(newName));
        }

        for (PcbNode module : source.iterate("module")) {
            for (PcbNode pad : module.iterate("pad")) {
                if (!pad.hasChild("net"))
                    continue;

                PcbNode net = pad.find("net");

                String localName = netNameMapping.get(net.getChild(1));

                net.setString(1, localName);

                net.setInt(0, networks.getId(localName));
            }
            destNode.addChild(module);
        }

        for (PcbNode segment : source.iterate("segment")) {
//            if (!segment.hasChild("net"))
//                continue;
            PcbNode net = segment.find("net");

            String originalId = net.getChild(0);
            net.setInt(0, netIdMapping.get(originalId));

            destNode.addChild(segment);
        }

        for (PcbNode via : source.iterate("via")) {
            PcbNode net = via.find("net");
            String originalId = net.getChild(0);
            net.setInt(0, netIdMapping.get(originalId));

            destNode.addChild(via);
        }



    }

    private static class Networks {
        private Map<String, Integer> networks = new HashMap<String, Integer>();

        public String registerNetworkIfPcbSpecific(String name) {
            if (name.startsWith("N-00")) {
                String newName = "F-0000" + networks.size();
                log("Board-specific net: " + name + " would be " + newName);

                networks.put(newName, networks.size());
                return newName;
            } else {
                if (networks.containsKey(name)) {
                    log("Existing global net: " + name);
                    return name;
                }

                log("New global net: " + name);
                networks.put(name, networks.size());
                return name;
            }
        }

        public int getId(String localName) {
            Integer value = networks.get(localName);
            if (localName == null)
                throw new NullPointerException("No id for " + localName);
            return value;
        }
    }

    private static void log(String s) {
        System.out.println(s);
    }
}
