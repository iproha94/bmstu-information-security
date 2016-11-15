import java.util.BitSet;

/**
 * Created by ilyaps on 16.11.16.
 */
public class IOBitSet {
    public static int readFromBitSet(BitSet bs, int startPos, int lengthBlock) {
        int num;

        try {
            num = (int) bs.get(startPos, startPos + lengthBlock).toLongArray()[0];
        } catch (Exception e) {
            num = 0;
        }

        return num;
    }

    public static int writeToBitSet(int num, BitSet out, int lengthBlock, int startPos) {
        for (int j = 0; j < lengthBlock; ++j) {
            if ((num & (1 << j)) > 0) {
                out.set(startPos + j);
            }
        }

        return startPos + lengthBlock;
    }
}
