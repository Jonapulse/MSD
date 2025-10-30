import java.util.HashMap;

public class MyHTTPResponse {
    /*
    * Utility class to package elements for the HTTP Response
     */
    public int responseCode_ = 200; //Default value, changes if error encountered
    public byte[] httpResponsePayload = new byte[0];

    public String getHTTPResponseMessage()
    {
        switch(responseCode_){
            case 101:
                return "HTTP/1.1 101 Switching Protocols";
            case 200:
                return "HTTP/1.1 200 OK";
            case 400:
                return "HTTP/1.1 400 Bad Request";
            case 404:
                return "HTTP/1.1 404 Not Found";
            case 405:
                return "HTTP/1.1 405 Method Not Allowed";
            case 500:
                return "HTTP/1.1 500 Internal Server Error";
            default:
                return "ERROR: Support Code [ " + responseCode_ + " ] is not supported";
        }
    }

    public String[] getHTTPResponseHeaders(MyHTTPRequest request) {
        String[] headers = null;
        if(request.isWebSocket()){
            headers = new String[3];
            headers[0] = "Upgrade: websocket";
            headers[1] = "Connection: Upgrade";
            //todo: Encode the key?
            headers[2] = "Sec-Websocket-Accept: " + request.headers.get("Sec-WebSocket-Key");
        }
        else
        {
            //Standard file request
            headers = new String[2];
            headers[0] = "Content-Type: text/html";
            headers[1] = "Content-Length: " + httpResponsePayload.length;
        }
        return headers;
    }



    public int getResponseCode_() {
        return responseCode_;
    }
    public void setResponseCode_(int responseCode) {
        responseCode_ = responseCode;
    }
}
