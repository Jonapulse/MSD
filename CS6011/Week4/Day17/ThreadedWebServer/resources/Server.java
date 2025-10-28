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
                ConnectHandler clientRunner =  new ConnectHandler(client);
                Thread t = new Thread(clientRunner);
                t.start();
            } catch (IOException e) {
                continue;
            }

        }
    }
}