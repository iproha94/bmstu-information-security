import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by ilyaps on 11.11.16.
 */
public class ConvertFile {
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

    public static final void writeIntFile(String address, List<Integer> listFile) throws IOException {
        DataOutputStream douts = new DataOutputStream(
                new FileOutputStream(address));


        for (Integer el : listFile) {
            douts.writeInt(el);
        }

        douts.close();
    }

    public static final List<Integer> readIntFile(String address) throws FileNotFoundException {
        List<Integer> listFile = new ArrayList<>();

        DataInputStream dins = new DataInputStream(
                new BufferedInputStream(
                        new FileInputStream(new File(address))));

        try {
            while (true) {
                listFile.add(dins.readInt());
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

        douts.close();
    }

    public static void main(String[] args) throws IOException {

    }
}
