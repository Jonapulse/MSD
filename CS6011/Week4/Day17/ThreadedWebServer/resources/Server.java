//Created by Jon Pulsipher
//CS 6011
//u0294347
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
    //NOTES: I took the loop out of main so theoretically an external program could use Server
    //
    public void run() throws IOException {

        ss = new ServerSocket(8080);

        //Set up listening to and accepting a server.
        //
        while (stopServer == false) {
            Socket client = null;
            try {
                client = ss.accept();
            } catch (IOException e) {
                continue;
            }

            MyHTTPResponse httpResponse = new MyHTTPResponse();
            String filePath = "";
            try {
                filePath = parseFileRequest(client, httpResponse);
            } catch (IOException e) {
                httpResponse.responseCode = 500; //Server issue
            }

            byte[] returnPageBytes = null;
            try {
                httpResponse.httpResponsePayload = new FileInputStream("resources" + filePath).readAllBytes();
            } catch (FileNotFoundException e) {
                httpResponse.responseCode = 404;
                httpResponse.httpResponsePayload = new FileInputStream("resources/404.html").readAllBytes();
            }

            writeResponse(client.getOutputStream(), httpResponse);

            client.close();
        }
    }

    private String parseFileRequest(Socket client, MyHTTPResponse response) throws IOException{
        InputStream is = null;
        try {
            is = client.getInputStream();
        } catch (IOException e) {
            throw e;
        }

        //Harvest Filepath
        String filePath = "";
        String [] requestStrings = new Scanner(is).nextLine().split(" ");
        if(requestStrings.length == 0 || !requestStrings[0].equals("GET"))
        {
            response.responseCode = 405; //Method not allowed
            return "";
        } else if (requestStrings.length <= 1)
        {
            response.responseCode = 400; //Bad Request
            return "";
        } else {
            filePath =  requestStrings[1];
        }

        if (filePath.equals("/"))
            filePath = "/index.html";

        return filePath;
    }

    private void writeResponse(OutputStream out, MyHTTPResponse response/*byte[] returnPageBytes, boolean fileFound*/) throws IOException {
        PrintWriter printWriter = new PrintWriter(out, false);

        printWriter.println(response.getHTTPResponseMessage());
        System.out.println(response.getHTTPResponseMessage());
        String[] headers = response.getHTTPResponseHeaders();
        for (String header : headers) {
            printWriter.println(header);
            System.out.println(header);
        }
        printWriter.println();
        out.write(response.httpResponsePayload);
        out.flush();
    }
}