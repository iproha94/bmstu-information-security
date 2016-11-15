import java.io.*;
import java.util.ArrayList;
import java.util.BitSet;
import java.util.List;

/**
 * Created by ilyaps on 11.11.16.
 */
public class IOFile {
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

    public static final void writeByteFile(String address, List<Integer> listFile) throws IOException {
        DataOutputStream douts = new DataOutputStream(
                new FileOutputStream(address));


        for (Integer el : listFile) {
            douts.writeByte(el);
        }

        System.out.println("File write");
        douts.close();
    }

    public static void writeBitSetToFile(String address, BitSet bs) throws IOException {
        DataOutputStream douts = new DataOutputStream(
                new FileOutputStream(address));

        douts.write(bs.toByteArray());

        System.out.println("File write");
        douts.close();
    }

    public static BitSet readFileToBitSet(String address) throws FileNotFoundException {
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

        return BitSet.valueOf(bb);
    }
}
