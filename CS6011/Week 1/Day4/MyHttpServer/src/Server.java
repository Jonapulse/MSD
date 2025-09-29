import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Server {

    static ServerSocket ss;

    public static void main(String[] args) throws IOException {

        ss = new ServerSocket(8080);

        //Set up listening to and accepting a server.
        //
        while (true) {
            Socket client = null;
            try {
                client = ss.accept();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            //Put input stream into Scanner
            //
            InputStream is = null;
            try {
                is = client.getInputStream();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            Scanner s = new Scanner(is);

            //Harvest Filepath and HTTP Headers
            //
            String filePath = s.nextLine().split(" ")[1];
            Map<String, String> httpHeaders = new HashMap<>();
            while(true){
                System.out.println();
                String line = s.nextLine();
                if(line.equals("\r\n") || line.equals(""))
                    break;
                else {
                    String[] split = line.split(" ");
                    String headerKey = split[0].substring(0, split[0].length() - 1); //Drop trailing ":"
                    httpHeaders.put(headerKey, split[1]);
                }
            }

            if(filePath.equals("/"))
                filePath = "/index.html";
            boolean fileFound = true;

            //TODO: implement alt path for malformed header? I'm not seeing it in the assignment

            byte[] webPageBytes = null;
            try {
                webPageBytes = new FileInputStream("src" + filePath).readAllBytes();
            } catch (FileNotFoundException e) {
                webPageBytes = new FileInputStream("src/404.html").readAllBytes();
                fileFound = false;
            }

            OutputStream out = client.getOutputStream();
            PrintWriter printWriter = new PrintWriter(out, false);

            if(fileFound)
                printWriter.println("HTTP/1.1 200 OK");
            else
                printWriter.println("HTTP/1.1 404 Not Found");
            //TODO: Check the type because I've got html and txt
            printWriter.println("Content-Type: text/html");
            printWriter.println("Content-Length: " + webPageBytes.length);
            printWriter.println();
            printWriter.flush();
            out.write(webPageBytes);
            out.flush();
            client.close();
        }
    }
}