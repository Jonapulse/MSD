import { useRef } from "react";
import InputWidget from "./InputWidget";

function LoginPage({joinRoom}){
    let userInput = useRef();
    let roomInput = useRef();

    function attemptJoinRoom()
    {
        //todo: validate input.
        joinRoom(userInput.current.value, roomInput.current.value);
    }

    return(
        <div>
            <InputWidget label="Username" valueRef={userInput}></InputWidget>
            <InputWidget label="Room Name" valueRef={roomInput}></InputWidget>
            <button onClick={attemptJoinRoom}>Join Room</button>
        </div>
    );
}

export default LoginPage;