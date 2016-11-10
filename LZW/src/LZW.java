import java.util.ArrayList;
import java.util.List;

/**
 * Created by ilyaps on 11.11.16.
 */
public class LZW {
    private static final int R = 256;        // number of input chars
    private static final int L = 4096;       // number of codewords = 2^W
    private static final int W = 12;         // codeword width


    public List<Integer> compress(List<Integer> in) {
        List<ElementOfTable> table = new ArrayList();

        for (int i = 0; i < R; ++i) {
            List<Integer> string = new ArrayList();
            string.add(i);

            ElementOfTable element = new ElementOfTable(string, -1);
            table.add(element);
        }

        List<Integer> string = new ArrayList();
        string.add(in.get(0));

        for (int i = 1; i < in.size(); ++i) {
            List stringPlusSymbol = new ArrayList(string);
            stringPlusSymbol.add(in.get(i));

            if (getCodeByString(stringPlusSymbol, table) != -1) {
                string = stringPlusSymbol;
            } else {
                ElementOfTable element = new ElementOfTable(stringPlusSymbol, getCodeByString(string, table));
                table.add(element);

                string = new ArrayList();
                string.add(in.get(i));
            }
        }

        ElementOfTable element = new ElementOfTable(null, getCodeByString(string, table));
        table.add(element);


        List<Integer> out = new ArrayList();

        for (ElementOfTable el: table) {
            if (el.out != -1) {
                out.add(el.out);
            }
        }

        return out;
    }

    private int getCodeByString(List stringPlusSymbol, List<ElementOfTable> table) {
        for (int i = 0; i < table.size(); ++i) {
            if (stringPlusSymbol.equals(table.get(i).element)) {
                return i;
            }
        }

        return -1;
    }

    public static void main(String[] args) {

    }
}
