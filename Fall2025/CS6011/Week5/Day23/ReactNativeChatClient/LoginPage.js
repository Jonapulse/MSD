import { useRef } from "react";
import { View, Button } from 'react-native';
import InputWidget from "./InputWidget";
import { useState } from "react";

function LoginPage({joinRoom}){
    let userInput = useRef();
    let roomInput = useRef();
    const [userName, setUserName] = useState("");
    const [roomName, setRoomName] = useState("");

    function attemptJoinRoom()
    {
        if(userName.trim() === "")
        {
            alert("Please enter a username");
            userInput.current.select();
            return;
        }
        if(roomName.trim() === "")
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
        <View>
            <InputWidget label="Username" valueRef={userInput} onChangeText={setUserName} defaultText="Enter a name"></InputWidget>
            <InputWidget label="Room Name" valueRef={roomInput} onChangeText={setRoomName} defaultText="Enter a room name"></InputWidget>
            <Button onPress={attemptJoinRoom} title="Join Room"></Button>
        </View>
    );
}

export default LoginPage;