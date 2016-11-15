import java.io.*;
import java.util.ArrayList;
import java.util.BitSet;
import java.util.List;

/**
 * Created by ilyaps on 11.11.16.
 */
public class ConvertFile {
    public static final int lengthOutBlock = 16;

    public static final List<Integer> readUnByteFile(String address) throws FileNotFoundException {
        List<Integer> listFile = new ArrayList<>();

        DataInputStream dins = new DataInputStream(
                new BufferedInputStream(
                        new FileInputStream(new File(address))));

        try {
            while (true) {
                listFile.add(dins.readUnsignedByte());
            }
        } catch (IOException e) {
            System.out.println("File read");
        }

        return listFile;
    }

    public static final void writeMyTypeFile(String address, List<Integer> listFile) throws IOException {
        DataOutputStream douts = new DataOutputStream(
                new FileOutputStream(address));

        BitSet bs = new BitSet();

        for (int i = 0; i < listFile.size(); ++i) {
            for (int j = 0; j < lengthOutBlock; ++j) {
                if ((listFile.get(i) & (1 << j)) > 0) {
                    bs.set(i * lengthOutBlock + j);
                }
            }
        }

        douts.write(bs.toByteArray());

        System.out.println("File write");
        douts.close();
    }

    public static final void writeIntFile(String address, List<Integer> listFile) throws IOException {
        DataOutputStream douts = new DataOutputStream(
                new FileOutputStream(address));

        for (Integer el : listFile) {
            douts.writeShort(el);
        }

        System.out.println("File write");
        douts.close();
    }

    public static final List<Integer> readMyTypeFile(String address) throws IOException {

        DataInputStream dins = new DataInputStream(
                new BufferedInputStream(
                        new FileInputStream(new File(address))));

        List<Integer> listFile = new ArrayList<>();

        try {
            while (true) {
                listFile.add(dins.readUnsignedByte());
            }
        } catch (IOException e) {
            System.out.println("File read");
        }


        byte[] bb = new byte[listFile.size()];

        for (int i = 0; i < listFile.size(); ++i) {
            bb[i] = listFile.get(i).byteValue();
        }

        BitSet bs = BitSet.valueOf(bb);

        List<Integer> listFileConvert = new ArrayList<>();

        int amount = listFile.size() * 8 / lengthOutBlock;

        for (int i = 0; i < amount; ++i) {
            int num;
            try {
                num = (int) bs.get(lengthOutBlock * i, lengthOutBlock * (i + 1)).toLongArray()[0];
            } catch (Exception e) {
                num = 0;
            }

            listFileConvert.add(num);
        }

        return listFileConvert;
    }

    public static final List<Integer> readIntFile(String address) throws FileNotFoundException {
        List<Integer> listFile = new ArrayList<>();

        DataInputStream dins = new DataInputStream(
                new BufferedInputStream(
                        new FileInputStream(new File(address))));

        try {
            while (true) {
                listFile.add((int)dins.readShort());
            }
        } catch (IOException e) {
            System.out.println("File read");
        }

        return listFile;
    }

    public static final void writeByteFile(String address, List<Integer> listFile) throws IOException {
        DataOutputStream douts = new DataOutputStream(
                new FileOutputStream(address));


        for (Integer el : listFile) {
            douts.writeByte(el);
        }

        System.out.println("File write");
        douts.close();
    }

    public static void main(String[] args) throws IOException {


    }
}
