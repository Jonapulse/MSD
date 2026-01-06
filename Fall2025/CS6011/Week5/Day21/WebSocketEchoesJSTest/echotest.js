function main()
{
    ws = new WebSocket("ws://localhost:8080");
    ws.onmessage = handleWsMessage;
    ws.onopen = sendTestMessage;
}
window.onload = main;


function sendTestMessage()
{
    ws.send("Hello, how are you? Echo me back!");
}

function handleWsMessage(msg)
{
    //Test 1 - should include "Hello, how are you? Echo me back."
    console.log(msg);
}