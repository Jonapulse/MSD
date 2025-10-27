public class MyHTTPResponse {
    /*
    * Utility class to package elements for the HTTP Response
     */
    public int responseCode = 200; //Default value, changes if error encountered
    public byte[] httpResponsePayload = new byte[0];

    public String getHTTPResponseMessage()
    {
        switch(responseCode){
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
                return "ERROR: Support Code [ " + responseCode + " ] is not supported";
        }
    }

    public String[] getHTTPResponseHeaders() {
        String[] headers = new String[2];
        headers[0] = "Content-Type: text/html";
        headers[1] = "Content-Length: " + httpResponsePayload.length;
        return headers;
    }
}
