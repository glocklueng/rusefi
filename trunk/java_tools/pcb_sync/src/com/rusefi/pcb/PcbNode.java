package com.rusefi.pcb;

import com.rusefi.util.FileUtils;
import com.sun.istack.internal.NotNull;
import com.sun.istack.internal.Nullable;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
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

    static PcbNode readFromFile(String fileName) throws IOException {
        String content = FileUtils.readFile(fileName);
        return parse(content);
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

    public void setDouble(int i, double value) {
        children.set(i, "" + value);
    }

    public double asDouble(int index) {
        return Double.parseDouble((String) children.get(index));
    }

    public boolean hasChild(String key) {
        return !iterate(key).isEmpty();
    }

    @Nullable
    public PcbNode findIfExists(String key) {
        List<PcbNode> r = iterate(key);
        if (r.isEmpty())
            return null;
        return find(key);
    }

    @NotNull
    public PcbNode find(String key) {
        List<PcbNode> r = iterate(key);
        if (r.size() != 1)
            throw new IllegalStateException("More that one " + key + " in " + nodeName);
        return r.get(0);
    }

    public List<PcbNode> nodes() {
        List<PcbNode> result = new ArrayList<PcbNode>();
        for (Object child : children) {
            if (child instanceof String)
                continue;
            result.add((PcbNode) child);
        }
        return result;
    }

    public List<PcbNode> iterate(String key) {
        List<PcbNode> result = new ArrayList<PcbNode>();
        for (PcbNode p : nodes()) {
            if (p.nodeName.equals(key))
                result.add(p);
        }
        return result;
    }

    public void addChild(PcbNode node) {
        children.add(node);
    }

    public List<Object> getChildren() {
        return Collections.unmodifiableList(children);
    }

    public String getChild(int index) {
        return (String) children.get(index);
    }

    public void setString(int index, String value) {
        children.set(index, value);
    }

    public void setInt(int index, int value) {
        children.set(index, "" + value);
    }
}
