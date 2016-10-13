import java.io.*;

public class Main {

    public static void main(String[] args) {
        System.out.println(System.getProperty("user.dir"));

        String line = "";
        try {
            File file = new File("file.txt");
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            line = bufferedReader.readLine();
            fileReader.close();
        } catch (IOException e) {
            System.out.println("ERROR. File license not found");
            try {
                System.out.println("Press ENTER!");
                System.in.read();
            } catch (IOException ignore) {

            }
            System.exit(-1);
        }

        String diskId = DiskUtils.getSerialNumber("C");

        if (!line.equals(diskId)) {
            System.out.println("ERROR. You are bad hacker");
            try {
                System.out.println("Press ENTER!");
                System.in.read();
            } catch (IOException e) {

            }
            System.exit(-2);
        }

        System.out.println("Program run!");

        try {
            System.out.println("Press ENTER!");
            System.in.read();
        } catch (IOException e) {

        }
    }
}
