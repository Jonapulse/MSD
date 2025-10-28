import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class ConnectHandler implements Runnable {

    Socket client_;

    @Override
    public void run() {

        MyHTTPResponse httpResponse = new MyHTTPResponse();
        String filePath = "";
        try {
            filePath = parseFileRequest(client_, httpResponse);
        } catch (IOException e) {
            httpResponse.responseCode = 500; //Server issue
        }

        byte[] returnPageBytes = null;
        try {
            httpResponse.httpResponsePayload = new FileInputStream("resources" + filePath).readAllBytes();
        }
        catch (FileNotFoundException e) {
            httpResponse.responseCode = 404;
        }
        catch (IOException e) {
            httpResponse.responseCode = 500;
        }

        try {
            writeResponse(client_.getOutputStream(), httpResponse);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        try {
            client_.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public ConnectHandler(Socket client) {
        client_ = client;
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
        printWriter.flush();
        out.write(response.httpResponsePayload);

        out.flush();
    }
}
