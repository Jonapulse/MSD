import { useRef } from "react";

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
            <div>Username: <input ref={userInput}></input></div>
            <div>Room Name: <input ref={roomInput}></input></div>
            <button onClick={attemptJoinRoom}>Join Room</button>
        </div>
    );
}

export default LoginPage;