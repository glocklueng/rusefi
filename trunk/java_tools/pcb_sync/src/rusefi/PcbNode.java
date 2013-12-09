package rusefi;

import java.util.ArrayList;
import java.util.List;

/**
 * User: user
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

    public static PcbNode parse(String s, int index) {
        char c = s.charAt(index);
        if (c != '(')
            throw new IllegalStateException();
        index++;
        String nodeName = readToken(s, index);
        index += nodeName.length();

        List<Object> children = new ArrayList<Object>();
        while (true) {
            c = s.charAt(index);
            if (c == ')')
                break;

            if (!isWhitespace(c))
                throw new IllegalStateException();
            if (isWhitespace(s.charAt(index)))
                index++;

            if (s.charAt(index) == '(') {
                PcbNode child = parse(s, index);
                children.add(child);
                index = child.closingIndex;
                continue;
            }

            String child = readToken(s, index);
            children.add(child);
            index += child.length();
        }
        return new PcbNode(nodeName, index + 1, children);
    }

    private static String readToken(String s, int index) {
        if (s.charAt(index) == '"')
            return s.substring(index, s.indexOf('"', index + 1) + 1);

        String result = "";
        while (index < s.length()) {
            char c = s.charAt(index);
            if (c == ')' || isWhitespace(c))
                break;
            result += c;
            index++;
        }
        return result;
    }

    private static boolean isWhitespace(char c) {
        return c == ' ' || c == '\r' || c == '\n';
    }
}
