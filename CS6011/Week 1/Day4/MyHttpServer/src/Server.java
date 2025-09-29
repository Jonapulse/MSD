import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Server {

    static ServerSocket ss;
    boolean stopServer = false;

    public void stop()
    {
        stopServer = true;
    }

    //Runs the server
    //NOTES: I took the loop out of main so theoretically and external program could use Server
    //
    public void run() throws IOException {

        ss = new ServerSocket(8080);

        //Set up listening to and accepting a server.
        //NOTES: Do we ever want this to exit without stopping compilation? I added the 'stop()' functionality for that
        //
        while (stopServer == false) {
            Socket client = null;
            try {
                client = ss.accept();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            String filePath = parseFileRequest(client);

            //NOTES: I wanted to refactor this into a method, but I needed fileFound and returnPageBytes and didn't
            //think of a clean way to get both of those back.
            boolean fileFound = true;
            byte[] returnPageBytes = null;
            try {
                returnPageBytes = new FileInputStream("src" + filePath).readAllBytes();
            } catch (FileNotFoundException e) {
                returnPageBytes = new FileInputStream("src/404.html").readAllBytes();
                fileFound = false;
            }

            writeResponse(client, returnPageBytes, fileFound);

            client.close();
        }
    }

    private void writeResponse(Socket client, byte[] returnPageBytes, boolean fileFound) throws IOException {
        OutputStream out = client.getOutputStream();
        PrintWriter printWriter = new PrintWriter(out, false);

        if (fileFound)
            printWriter.println("HTTP/1.1 200 OK");
        else
            printWriter.println("HTTP/1.1 404 Not Found");
        printWriter.println("Content-Type: text/html");
        printWriter.println("Content-Length: " + returnPageBytes.length);
        printWriter.println();
        printWriter.flush();
        out.write(returnPageBytes);
        out.flush();
    }

    private String parseFileRequest(Socket client) {
        InputStream is = null;
        try {
            is = client.getInputStream();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        //Harvest Filepath
        String filePath = new Scanner(is).nextLine().split(" ")[1];

        if (filePath.equals("/"))
            filePath = "/index.html";

        return filePath;
    }

    public static void main(String[] args) throws IOException {
        Server s = new Server();
        s.run();
    }
}