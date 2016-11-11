import java.util.ArrayList;
import java.util.List;

/**
 * Created by ilyaps on 11.11.16.
 */
public class LZW {
    private static final int R = 256;        // number of input chars

    public static final void initTable(List<List<Integer>> table) {
        for (int i = 0; i < R; ++i) {
            List<Integer> string = new ArrayList();
            string.add(i);

            table.add(string);
        }
    }

    public List<Integer> compress(List<Integer> in) {
        List<List<Integer>> table = new ArrayList();

        initTable(table);

        List<Integer> out = new ArrayList();

        List<Integer> string = new ArrayList();
        string.add(in.get(0));

        for (int i = 1; i < in.size(); ++i) {
            List stringPlusSymbol = new ArrayList(string);
            stringPlusSymbol.add(in.get(i));

            if (table.indexOf(stringPlusSymbol) != -1) {
                string = stringPlusSymbol;
            } else {
                out.add(table.indexOf(string));
                table.add(stringPlusSymbol);

                string = new ArrayList();
                string.add(in.get(i));
            }
        }

        out.add(table.indexOf(string));

        return out;
    }

    public List<Integer> decompress(List<Integer> in) {
        List<List<Integer>> table = new ArrayList();

        initTable(table);

        List<Integer> out = new ArrayList();

        int oldCode = in.get(0);
        out.add(oldCode);

        for (int i = 1; i < in.size(); ++i) {
            int newCode = in.get(i);
            List<Integer> string = table.get(newCode);

            for (int j = string.size() - 1; j >= 0; --j ) {
                out.add(string.get(j));
            }

            int symbol = string.get(string.size() - 1);

            List<Integer> oldCodePlusSymbol = new ArrayList<>();
            oldCodePlusSymbol.add(symbol);
            oldCodePlusSymbol.add(oldCode);

            table.add(oldCodePlusSymbol);

            oldCode = newCode;
        }

        return out;
    }

}
