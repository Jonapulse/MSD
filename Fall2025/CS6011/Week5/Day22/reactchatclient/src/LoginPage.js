import { useRef } from "react";
import InputWidget from "./InputWidget";

function LoginPage({joinRoom}){
    let userInput = useRef();
    let roomInput = useRef();

    function attemptJoinRoom()
    {
        let userName = userInput.current.value;
        let roomName = roomInput.current.value;
        if(userName === "")
        {
            alert("Please enter a username");
            userInput.current.select();
            return;
        }
        if(roomName === "")
        {
            alert("Please enter a room name");
            roomInput.current.select();
            return;
        }

        //Swap out spaces with '_' to sanitize input for websocket command
        //
        joinRoom(userName.replaceAll(' ', '_'), roomName.replaceAll(' ', '_'));
    }

    return(
        <div>
            <InputWidget label="Username" valueRef={userInput} defaultText="Enter a name"></InputWidget>
            <InputWidget label="Room Name" valueRef={roomInput} defaultText="Enter a room name"></InputWidget>
            <button onClick={attemptJoinRoom}>Join Room</button>
        </div>
    );
}

export default LoginPage;