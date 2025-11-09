import { useRef } from "react";
import { View, Button, Text, ScrollView } from 'react-native';
import InputWidget from "./InputWidget";
import { useState } from "react";

function Room({roomName, sendMessage, leaveRoom, chatlog}){

    let messageInput = useRef(); 
    const [message, setMessage] = useState("");

    function attemptSendMessage()
    {
        if(message === "")
        {
            alert("Enter a message to send");
            messageInput.current.select();
            return;
        }

        sendMessage(message);
        setMessage("");
    }

    return(
        <View className="Room">
            <View className="roomHeader">
                <Text>{roomName}</Text>
                <Button onPress={leaveRoom} title="Leave Room"></Button>
            </View>
            <ScrollView className="chatLog">
                {chatlog.map((msg,index) => (
                    <Text key={index}>{msg}</Text>
                ))}
            </ScrollView>
            <View className="roomFooter">
                <InputWidget label="" valueRef={messageInput} onChangeText={setMessage} defaultText="Write a message" ></InputWidget>
                <Button onPress={attemptSendMessage} title="Send"></Button>
            </View>
        </View>
    );
}

export default Room;