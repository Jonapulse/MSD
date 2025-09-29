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

            if(filePath.equals("/"));
                filePath = "/index.html";
            boolean fileFound = true;

            //TODO: implement alt path for malformed header? I'm not seeing it in the assignment

            FileInputStream webPage;
            try {
                webPage = new FileInputStream(filePath);
            } catch (FileNotFoundException e) {
                webPage = new FileInputStream("404.html");
                fileFound = false;
            }

            OutputStream out = client.getOutputStream();
            webPage.transferTo(out);

            PrintWriter printWriter = new PrintWriter(out);
            if(fileFound)
            {
                printWriter.println("HTTP/1.1 200 OK");
                //Add HTTPHeaders
                for(Map.Entry<String, String> header : httpHeaders.entrySet())
                    printWriter.println(header.getKey() + ": " + header.getValue());
                //Add Other required values
                printWriter.println("\r\n");
            }

            //What else goes into the Response header? We need to send them Content-
            //Type. Some browsers care about this and some don't. The Content-Length
            //is pretty important. Some browsers don't care about some do. Then you
            //do need the empty line.

            out.flush();
            client.close();
        }
    }
}