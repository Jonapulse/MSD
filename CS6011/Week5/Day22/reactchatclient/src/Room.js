import { useRef } from "react";
import InputWidget from "./InputWidget";

function Room({roomName, sendMessage, leaveRoom, chatlog}){

    let messageInput = useRef(); 

    function attemptSendMessage()
    {
        let message = messageInput.current.value;
        if(message === "")
        {
            alert("Enter a message to send");
            messageInput.current.select();
            return;
        }

        sendMessage(message);
        messageInput.current.value = "";
    }

    return(
        <div className="Room">
            <div className="roomHeader">
                <h1>{roomName}</h1>
                <button onClick={leaveRoom}>Leave Room</button>
            </div>
            <div className="chatLog">
                {chatlog.map((msg,index) => (
                    <p key={index}>{msg}</p>
                ))}
            </div>
            <div className="roomFooter">
                <InputWidget label="" valueRef={messageInput} defaultText="Write a message" ></InputWidget>
                <button onClick={attemptSendMessage}>Send</button>
            </div>
        </div>
    );
}

export default Room;