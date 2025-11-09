import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class ConnectHandler implements Runnable {

    Socket client_;

    @Override
    public void run() {

        MyHTTPRequest httpRequest = null;
        MyHTTPResponse httpResponse = new MyHTTPResponse();
        String fileName = "";
        try {
            httpRequest = new MyHTTPRequest(client_);
            if(!httpRequest.method_.equals("GET")){
                httpResponse.responseCode_ = 405; //Method not allowed
            }
        } catch (IOException e) {
            httpResponse.responseCode_ = 500; //Server issue
        }

        //PSEUDOCODE
        //Check if this is a websocket
        //If it is, make this into a new WebSocketHandler that will
        //send and recieve messages. When they receive messages, they
        //will speak to a static ChatRoomHandler class that will maintain
        //a list of rooms, users in those rooms, and message logs
        //will
        //Else do the rest of this and end by closing the connection
        //Or, for our websocket do we... questions
            //Should WebsocketHandler be in a new class?
            //Should I be maintaining this with a while(true) or something
                //...event driven?
            //How do I know when the client has new information? Need to ask.
        //From Owen - when do I know I've received a new message?
        if(httpRequest.isWebSocket()){
            // WebSocket path
             //
            httpResponse.responseCode_ = 101;
            try {
                writeResponse(client_.getOutputStream(), httpResponse, httpRequest);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        } else {
            // Look up the file
             //
            byte[] returnPageBytes = null;
            try {
                httpResponse.httpResponsePayload = new FileInputStream("resources" + httpRequest.getURL()).readAllBytes();
            }
            catch (FileNotFoundException e) {
                httpResponse.responseCode_ = 404;
            }
            catch (IOException e) {
                httpResponse.responseCode_ = 500;
            }

            // Write
             //
            try {
                writeResponse(client_.getOutputStream(), httpResponse, httpRequest);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            try {
                client_.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
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
            response.responseCode_ = 405; //Method not allowed
            return "";
        } else if (requestStrings.length <= 1)
        {
            response.responseCode_ = 400; //Bad Request
            return "";
        } else {
            filePath =  requestStrings[1];
        }

        if (filePath.equals("/"))
            filePath = "/index.html";

        return filePath;
    }

    private void writeResponse(OutputStream out, MyHTTPResponse response, MyHTTPRequest request) throws IOException {
        PrintWriter printWriter = new PrintWriter(out, false);

        printWriter.println(response.getHTTPResponseMessage());
        String[] headers = response.getHTTPResponseHeaders(request);
        for (String header : headers) {
            printWriter.println(header);
        }
        printWriter.println();
        printWriter.flush();

        // Standard file write to out
        //
        out.write(response.httpResponsePayload);
        out.flush();

        //Artificially slowed down write to out
        //
//        for(int i = 0 ; i < response.httpResponsePayload.length; i++){
//            out.write(response.httpResponsePayload[i]);
//            out.flush();
//            //Thread.sleep(10); //to add if imgs loading too quickly
//        }
    }
}
