package rusefi;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * (c) Andrey Belomutskiy
 * 12/8/13
 */
public class PcbNode {
    public final String nodeName;
    public final int closingIndex;
    public final List<Object> children;

    public PcbNode(String nodeName, int closingIndex, List<Object> children) {
        this.nodeName = nodeName;
        this.closingIndex = closingIndex;
        this.children = children;
    }

    @Override
    public String toString() {
        return "PcbNode{" +
                nodeName +
                ", children=" + children.size() +
                '}';
    }

    private static PcbNode parse(String s, int index, int depth) {
        log("Reading node from " + index, depth);
        if (s.charAt(index) != '(')
            throw new IllegalStateException();
        index++;
        String nodeName = readToken(s, index, depth);
        index += nodeName.length();

        List<Object> children = new ArrayList<Object>();
        while (true) {
            while (isWhitespace(s.charAt(index)))
                index++;

            char c = s.charAt(index);
            if (c == ')')
                break;

            if (s.charAt(index) == '(') {
                PcbNode child = parse(s, index, depth + 1);
                children.add(child);
                index = child.closingIndex;
                continue;
            }

            String child = readToken(s, index, depth);
            children.add(child);
            index += child.length();
        }
        return new PcbNode(nodeName, index + 1, children);
    }

    private static String readToken(String s, int index, int depth) {
        log("Reading token from " + index, depth);
        if (s.charAt(index) == '"') {
            String result = s.substring(index, s.indexOf('"', index + 1) + 1);
            log("Got quoted token: " + result, depth);
            return result;
        }

        String result = "";
        while (index < s.length()) {
            char c = s.charAt(index);
            if (c == ')' || isWhitespace(c))
                break;
            result += c;
            index++;
        }
        if (result.length() == 0)
            throw new IllegalStateException("Empty token");
        log("Got token: " + result, depth);
        return result;
    }

    private static void log(String s, int depth) {
//        for (int i = 0; i < depth; i++)
//            System.out.print(' ');
//        System.out.println(s);
    }

    private static void log(String s) {
        log(s, 0);
    }

    private static boolean isWhitespace(char c) {
        return c == ' ' || c == '\r' || c == '\n';
    }

    public static PcbNode parse(String content) {
        return parse(content, 0, 0);
    }

    public String pack() {
        StringBuilder sb = new StringBuilder();
        pack(sb, "");
        return sb.toString();
    }

    private void pack(StringBuilder sb, String prefix) {
        sb.append(prefix).append("(").append(nodeName);

        for (Object child : children) {
            if (child instanceof String) {
                sb.append(" ").append(child);
                continue;
            }
            PcbNode p = (PcbNode) child;
            sb.append("\r\n");
            p.pack(sb, prefix + " ");
        }


        sb.append(")\r\n");
    }

    public void write(String fileName) throws IOException {
        String content = pack();
        BufferedWriter bw = new BufferedWriter(new FileWriter(fileName));
        bw.write(content);
        bw.close();
    }

    public void move(double dx, double dy) {
        List<PcbNode> dimensions = iterate("dimension");
        System.out.println("Moving " + dimensions.size() + " dimension");
        for (PcbNode dimension : dimensions) {
            moveAt(dx, dy, dimension.find("gr_text"));
            movePts(dx, dy, dimension.find("feature1"));
            movePts(dx, dy, dimension.find("feature2"));
            movePts(dx, dy, dimension.find("crossbar"));
            movePts(dx, dy, dimension.find("arrow1a"));
            movePts(dx, dy, dimension.find("arrow1b"));
            movePts(dx, dy, dimension.find("arrow2a"));
            movePts(dx, dy, dimension.find("arrow2b"));
        }

        List<PcbNode> gr_lines = iterate("gr_line");
        System.out.println("Moving " + gr_lines.size() + " gr_lines");
        for (PcbNode gr_line : gr_lines)
            moveStartEnd(dx, dy, gr_line);

        List<PcbNode> gr_circles = iterate("gr_circle");
        System.out.println("Moving " + gr_circles.size() + " gr_circles");
        for (PcbNode gr_circle : gr_circles) {
            PcbNode start = gr_circle.find("center");
            moveCoordinatesInFirstChildren(dx, dy, start);

            PcbNode end = gr_circle.find("end");
            moveCoordinatesInFirstChildren(dx, dy, end);
        }

        List<PcbNode> gr_texts = iterate("gr_text");
        System.out.println("Moving " + gr_texts.size() + " gr_texts");
        for (PcbNode gr_text : gr_texts)
            moveAt(dx, dy, gr_text);

        List<PcbNode> zones = iterate("zone");
        System.out.println("Moving " + zones.size() + " zones");
        for (PcbNode zone : zones) {
            PcbNode polygon = zone.find("polygon");
            movePts(dx, dy, polygon);
        }


        List<PcbNode> segments = iterate("segment");
        System.out.println("Moving " + segments.size() + " segments");
        for (PcbNode segment : segments)
            moveStartEnd(dx, dy, segment);

        List<PcbNode> vias = iterate("via");
        System.out.println("Moving " + vias.size() + " vias");
        for (PcbNode via : vias)
            moveAt(dx, dy, via);


        List<PcbNode> modules = iterate("module");
        System.out.println("Moving " + modules.size() + " modules");
        for (PcbNode module : modules)
            moveAt(dx, dy, module);


    }

    private void movePts(double dx, double dy, PcbNode polygon) {
        PcbNode pts = polygon.find("pts");

        for (PcbNode point : pts.nodes())
            moveCoordinates(dx, dy, point, 0);
    }

    private void moveStartEnd(double dx, double dy, PcbNode segment) {
        PcbNode start = segment.find("start");
        moveCoordinatesInFirstChildren(dx, dy, start);

        PcbNode end = segment.find("end");
        moveCoordinatesInFirstChildren(dx, dy, end);
    }

    private void moveAt(double dx, double dy, PcbNode module) {
        PcbNode at = module.find("at");
        moveCoordinatesInFirstChildren(dx, dy, at);
    }

    private void moveCoordinatesInFirstChildren(double dx, double dy, PcbNode at) {
        moveCoordinates(dx, dy, at, 0);
    }

    private void moveCoordinates(double dx, double dy, PcbNode at, int index) {
        double x = at.asDouble(index);
        double y = at.asDouble(index + 1);
        at.setDouble(index, x + dx);
        at.setDouble(index + 1, y + dy);
    }

    private void setDouble(int i, double value) {
        children.set(i, "" + value);
    }

    private double asDouble(int index) {
        return Double.parseDouble((String) children.get(index));
    }

    private PcbNode find(String key) {
        List<PcbNode> r = iterate(key);
        if (r.size() != 1)
            throw new IllegalStateException(key);
        return r.get(0);
    }

    private List<PcbNode> nodes() {
        List<PcbNode> result = new ArrayList<PcbNode>();
        for (Object child : children) {
            if (child instanceof String)
                continue;
            result.add((PcbNode) child);
        }
        return result;
    }

    private List<PcbNode> iterate(String key) {
        List<PcbNode> result = new ArrayList<PcbNode>();
        for (PcbNode p : nodes()) {
            if (p.nodeName.equals(key))
                result.add(p);
        }
        return result;
    }
}
