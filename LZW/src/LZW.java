import java.util.ArrayList;
import java.util.BitSet;
import java.util.List;

/**
 * Created by ilyaps on 11.11.16.
 */
public class LZW {
    private int startLengthOutBlock;

    public LZW(int startLengthOutBlock) {
        this.startLengthOutBlock = startLengthOutBlock;
    }

    private List<List<Integer>> initTable() {
        List<List<Integer>> table = new ArrayList();

        for (int i = 0; i < Math.pow(2, startLengthOutBlock); ++i) {
            List<Integer> string = new ArrayList();
            string.add(i);

            table.add(string);
        }

        return table;
    }

    public BitSet compress(List<Integer> in) {
        int startPos = 0;
        int lengthBlock = startLengthOutBlock;

        List<List<Integer>> table = initTable();

        BitSet bs = new BitSet();

        List<Integer> string = new ArrayList();
        string.add(in.get(0));

        for (int i = 1; i < in.size(); ++i) {
            List stringPlusSymbol = new ArrayList(string);
            stringPlusSymbol.add(0, in.get(i));

            if (table.indexOf(stringPlusSymbol) != -1) {
                string = stringPlusSymbol;
            } else {
                if (table.size() >= Math.pow(2, lengthBlock)) {
                    ++lengthBlock;
                    System.out.println("compress: lengthBlock up to " + lengthBlock);
                }

                startPos = IOBitSet.writeToBitSet(table.indexOf(string), bs, lengthBlock, startPos);

                table.add(stringPlusSymbol);


                string = new ArrayList();
                string.add(in.get(i));
            }
        }

        IOBitSet.writeToBitSet(table.indexOf(string), bs, lengthBlock, startPos);

        return bs;
    }



    public List<Integer> decompress(BitSet bs) {
        int startPos = 0;
        int lengthBlock = startLengthOutBlock + 1;

        List<List<Integer>> table = initTable();

        List<Integer> out = new ArrayList();

        int oldCode = IOBitSet.readFromBitSet(bs, startPos, lengthBlock);
        startPos += lengthBlock;

        out.add(oldCode);
        int symbol = oldCode;

        while (startPos < bs.length()) {
            int newCode = IOBitSet.readFromBitSet(bs, startPos, lengthBlock);
            startPos += lengthBlock;

            List<Integer> string;

            if (table.size() > newCode) {
                string = table.get(newCode);
            } else {
                string = new ArrayList<>(table.get(oldCode));
                string.add(symbol);
            }

            out.addAll(string);

            symbol = string.get(0);

            List<Integer> oldCodePlusSymbol = new ArrayList<>(table.get(oldCode));
            oldCodePlusSymbol.add(symbol);


            table.add(oldCodePlusSymbol);
            if (table.size() + 1 >= Math.pow(2, lengthBlock)) {
                ++lengthBlock;
                System.out.println("decompress: lengthBlock up to " + lengthBlock);
            }

            oldCode = newCode;
        }

        return out;
    }

}
