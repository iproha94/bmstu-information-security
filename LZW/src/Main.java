import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {


    public static void main(String[] args) throws IOException {
        String addressSource = "../data/source_file";

        List<Integer> in = ConvertFile.readUnByteFile(addressSource);

        LZW lzw = new LZW();

        List<Integer> compress = lzw.compress(in);

        String addressCompress = "../data/compress_file";
        ConvertFile.writeIntFile(addressCompress, compress);


        //----------------
        List<Integer> inCompress = ConvertFile.readIntFile(addressCompress);

        List<Integer> decompress = lzw.decompress(inCompress);

        String addressDecompress = "../data/decompress_file";
        ConvertFile.writeByteFile(addressDecompress, decompress);
    }
}
