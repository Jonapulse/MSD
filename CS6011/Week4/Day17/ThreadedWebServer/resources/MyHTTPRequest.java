import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.HashMap;
import java.util.Scanner;

public class MyHTTPRequest {

    String version_;
    String method_;
    String url_;
    public HashMap<String, String> headers;

    public MyHTTPRequest(Socket client) throws IOException {
        InputStream is = null;
        try {
            is = client.getInputStream();
        } catch (IOException e) {
            throw e;
        }

        Scanner sc = new Scanner(is);
        String[] requestLine = sc.nextLine().split(" ");
        try {
            method_ = requestLine[0];
            url_ = requestLine[1];
            version_ = requestLine[2];
            headers = new HashMap<>();
            String line = sc.nextLine();
            while(line != ""){
                String[] header = line.split(":");
                headers.put(header[0], header[1]);
                line = sc.nextLine();
            }

            if(url_.equals("/"))
            {
                url_ = "/index.html";
            }
        } catch (Exception e) {
            throw e;
        }
    }

    public boolean isWebSocket(){
        return headers.containsKey("Upgrade") && headers.get("Upgrade").equals("websocket");
    }
    public String getURL() { return url_; }
}
