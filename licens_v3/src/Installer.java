import java.io.*;

/**
 * Created by ilyap on 10.09.2016.
 */
public class Installer {
    public static void main(String[] args) {
        String diskId = DiskUtils.getSerialNumber("C");

        Writer writer = null;

        try {
            writer = new BufferedWriter(new OutputStreamWriter(
                    new FileOutputStream("file.txt"), "utf-8"));
            writer.write(diskId);
        } catch (IOException ex) {
            // report
        } finally {
            try {
                if (writer != null) {
                    writer.close();
                }
            } catch (Exception ex) {/*ignore*/}
        }

        System.out.println("Install complate.");
        try {
            System.out.println("Press ENTER!");
            System.in.read();
        } catch (IOException e) {

        }
    }
}
