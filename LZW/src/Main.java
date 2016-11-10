import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {


    public static void main(String[] args) {
        List<Integer> in = new ArrayList();
        in.add((int) 'g');
        in.add((int) 'o');
        in.add((int) 'i');
        in.add((int) 'n');
        in.add((int) 'g');
        in.add((int) 'g');
        in.add((int) 'o');
        in.add((int) 'i');
        in.add((int) 'n');
        in.add((int) 'g');
        in.add((int) 'g');
        in.add((int) 'o');
        in.add((int) 'n');
        in.add((int) 'e');

        System.out.println(in);

        LZW lzw = new LZW();

        List<Integer> zip = lzw.compress(in);

        System.out.println(zip);

    }
}
