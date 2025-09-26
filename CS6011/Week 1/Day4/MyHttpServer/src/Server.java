import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
public class Server{

    static ServerSocket ss;

    //Below is pseudo code for the beginnings of a basic webserver.
    public static void main(String[] args) : throws IOException{


        while(true){
            Socket client = null;
            try {
                client = ss.accept();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            //read 1st line of request: "GET filename http1.1"
            InputStream is = null;
            try {
                is = client.getInputStream();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            Scanner s = new Scanner(is);

            String line = s.nextLine(); // Get / http1.1
            String filename; // split line[1] -> line.get(1) in java.

            //Then grab the rest of the lines until you hit a blankline
            while(!line.equals("\r\n"){
                //store key/value pairs. Optional for this assignment but do it.
            }
            //open filename
            OutputStream out = socketToClient.getOutputStream();
            PrintWriter writer = new PrintWriter(out);

            // send response header
            writer.print("HTTP1.1 200 OK");
            //print size
            //print type "Content-Type: text/html; charset=UTF-8" //This will change if you're returning .css. We'll hardcode it the first time and then get more sophisticated.
            //print new line "\r\n";

            //What else goes into the Response header? We need to send them Content-
            //Type. Some browsers care about this and some don't. The Content-Length
            //is pretty important. Some browsers don't care about some do. Then you
            //do need the empty line.

            //read file
            //write to socket

            //InputStream.transferTo();
		/* But instead of doing this use transferTo();
		    while(file not done being read ){
                writer.print(/*/*1st line of index.html);
            }
            */
            //Don't close the socket yet. Do that as the last thing.
           // client.close();
        }
    }