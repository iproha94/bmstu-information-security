import java.util.ArrayList;
import java.util.BitSet;
import java.util.List;

public class Main {


    public static void main(String[] args) throws Exception {
        int startLengthOutBlock = 8;
        int resetLengthOutBlock = 12;

        LZW lzw = new LZW(startLengthOutBlock, resetLengthOutBlock);

        String addressSource = "../data/source_file.txt";
        List<Integer> in = IOFile.readUnByteFile(addressSource);

        BitSet compress = lzw.compress(in);
//        System.out.println(compress);

        String addressCompress = "../data/compress_file";
        IOFile.writeBitSetToFile(addressCompress, compress);

        //----------------
        BitSet inCompress = IOFile.readFileToBitSet(addressCompress);
//        System.out.println(inCompress);

        List<Integer> decompress = lzw.decompress(inCompress);
//        System.out.println(decompress);

        String addressDecompress = "../data/decompress_file";
        IOFile.writeByteFile(addressDecompress, decompress);
    }
}
