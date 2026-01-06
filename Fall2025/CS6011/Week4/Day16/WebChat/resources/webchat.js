let usernameInput;
let roomnameInput;
let chatInput;
let roomLoginWindow;
let roomTitle;
let chatRoomWindow;
let chatLogContainer;
let ws = new WebSocket("ws://localhost:8080");
ws.onmessage = handleWsMessage;

function setupServer()
{
    usernameInput = document.querySelector("#user_name_entry");
    roomnameInput = document.querySelector("#room_name_entry");
    chatInput = document.querySelector("#chat_input");
    roomLoginWindow = document.querySelector("#room_login");
    chatRoomWindow = document.querySelector("#room_chat");
    chatLogContainer = document.querySelector("#chat_window")
    roomTitle = document.querySelector("#room_title");
    
    //Set up Join room
    let joinButton = document.querySelector("#join_room_button");
    joinButton.addEventListener("click", joinRoom);
    let leaveButton = document.querySelector("#room_leave_button");
    leaveButton.addEventListener("click", leaveRoom);
    let chatButton = document.querySelector("#chat_send_button");
    chatButton.addEventListener("click", sendMessage);

    //Set up Chat send
}
window.onload = setupServer;

function joinRoom()
{
    ws.send("join " + usernameInput.value + " " + roomnameInput.value);
}

function leaveRoom()
{
    ws.send("leave");
    leaveRoomClient();
}

function handleWsMessage(msg)
{
    let msgObj = JSON.parse(msg.data);
    switch(msgObj.type)
    {
        case("join"):
            joinRoomClient(msgObj);
            break;
        case("leave"):
            leaveRoomClient();
            break;
        case("message"):
            let chatMessage = document.createElement("p");
            chatMessage.textContent = msgObj.user + ": " + msgObj.message;
            chatLogContainer.appendChild(chatMessage);
            //TODO: Do we need to check for it being the right room?
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
    chatRoomWindow.style = "display: block";

}

//This is separate from leaveRoom() in prep for if server
//updates allow us to get a message from the server confirming 
//we have left the room
//
function leaveRoomClient()
{
    roomLoginWindow.style = "display: block";
    chatRoomWindow.style = "display: none";
    chatLogContainer.replaceChildren(); //clear children
}

function sendMessage()
{
    ws.send("message " + chatInput.value);
    chatInput.value = "";
}