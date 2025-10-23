let usernameInput;
let roomnameInput;
let chatInput;
let roomLoginWindow;
let roomTitle;
let chatWindow;
let ws = new WebSocket("ws://localhost:8080");
ws.onmessage = handleWsMessage;

function setupServer()
{
    usernameInput = document.querySelector("#user_name_entry");
    roomnameInput = document.querySelector("#room_name_entry");
    chatInput = document.querySelector("#chat_input");
    roomLoginWindow = document.querySelector("#room_login");
    chatWindow = document.querySelector("#room_chat");
    roomTitle = document.querySelector("#room_title");
    
    //Set up Join room
    let joinButton = document.querySelector("#join_room_button");
    joinButton.addEventListener("click", joinRoom);
    let leaveButton = document.querySelector("#room_leave_button");
    leaveButton.addEventListener("click", ()=>{ws.send("leave")});

    //Set up Chat send
}
window.onload = setupServer;

function joinRoom()
{
    //TODO: Validate input
    ws.send("join " + usernameInput.value + " " + roomnameInput.value);
}

function handleWsMessage(msg)
{
    let msgObj = JSON.parse(msg.data);
    console.log(msgObj);
    switch(msgObj.type)
    {
        case("join"):
            joinRoomClient(msgObj);
            break;
        case("leave"):
            leaveRoomClient();
            break;
        default:
            console.log("No appropriate type for msg...");
            console.log(msgObj);
            break;
    }
}

function joinRoomClient(msgObj)
{
    roomTitle.textContent = msgObj.room;
    roomLoginWindow.style = "display: none";
    chatWindow.style = "display: block";

}

function leaveRoomClient()
{
    roomLoginWindow.style = "display: block";
    chatWindow.style = "display: none";
}