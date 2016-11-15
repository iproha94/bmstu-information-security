import java.io.IOException;
import java.util.List;

public class Main {


    public static void main(String[] args) throws Exception {
        LZW lzw = new LZW();

        String addressSource = "../data/bmstu-logo.png";
        List<Integer> in = ConvertFile.readUnByteFile(addressSource);
//        System.out.println(in);

        List<Integer> compress = lzw.compress(in);
//        System.out.println(compress);
        int max = compress.get(0);
        for(int el : compress) {
            if (el > max) {
                max = el;
            }
        }
        System.out.println("Max = " + max);


        String addressCompress = "../data/compress_file";
        ConvertFile.writeMyTypeFile(addressCompress, compress);

        //----------------
        List<Integer> inCompress = ConvertFile.readMyTypeFile(addressCompress);
//        System.out.println(inCompress);

        List<Integer> decompress = lzw.decompress(inCompress);
//        System.out.println(decompress);

        String addressDecompress = "../data/decompress_file";
        ConvertFile.writeByteFile(addressDecompress, decompress);
    }
}
