import { useRef } from "react";
import { View, Button, Text } from 'react-native';
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
    console.log("")

    return(
        <View className="Room">
            <View className="roomHeader">
                <Text>{roomName}</Text>
                <Button onClick={leaveRoom} title="Leave Room"></Button>
            </View>
            <View className="chatLog">
                {chatlog.map((msg,index) => (
                    <p key={index}>{msg}</p>
                ))}
            </View>
            <View className="roomFooter">
                <InputWidget label="" valueRef={messageInput} defaultText="Write a message" ></InputWidget>
                <Button onClick={attemptSendMessage} title="Send"></Button>
            </View>
        </View>
    );
}

export default Room;