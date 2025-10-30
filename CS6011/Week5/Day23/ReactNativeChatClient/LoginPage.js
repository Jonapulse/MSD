import { useRef } from "react";
import { View, Button } from 'react-native';
import InputWidget from "./InputWidget";

function LoginPage({joinRoom}){
    let userInput = useRef();
    let roomInput = useRef();

    function attemptJoinRoom()
    {
        let username = "";
        let roomName = "";
        userName = userInput.current.value;
        roomName = roomInput.current.value;
        console.log("TEST username: " , userName);
        console.log("TEST roomName: ", roomName);
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
        <View>
            <InputWidget label="Username" valueRef={userInput} defaultText="Enter a name"></InputWidget>
            <InputWidget label="Room Name" valueRef={roomInput} defaultText="Enter a room name"></InputWidget>
            <Button onPress={attemptJoinRoom} title="Join Room"></Button>
        </View>
    );
}

export default LoginPage;