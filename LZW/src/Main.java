import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Main {


    public static void main(String[] args) throws IOException {
        String addressSource = "../data/app.js";

        List<Integer> in = ConvertFile.readUnByteFile(addressSource);

//        System.out.println(in);

        LZW lzw = new LZW();

        List<Integer> compress = lzw.compress(in);
//        System.out.println(compress);

        String addressCompress = "../data/compress_file";
        ConvertFile.writeIntFile(addressCompress, compress);


        //----------------
        List<Integer> inCompress = ConvertFile.readIntFile(addressCompress);
//        System.out.println(inCompress);


        List<Integer> decompress = lzw.decompress(inCompress);
//        System.out.println(decompress);

        String addressDecompress = "../data/decompress_file";
        ConvertFile.writeByteFile(addressDecompress, decompress);
    }
}
