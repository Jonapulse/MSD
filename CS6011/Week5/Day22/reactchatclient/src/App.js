import './App.css';
import LoginPage from './LoginPage';
import Room from './Room';
import { useEffect, useState, useRef } from 'react';

function App() {

  let ws = useRef(null);
  const [joinedRoom, setJoinedRoom] = useState(false);
  const [roomName, setRoomName] = useState("");
  const [chatlog, setChatLog] = useState([]);

  useEffect(() => {
    ws.current = new WebSocket("ws://localhost:8080");
    ws.current.onmessage = handleWsMessage;
  });

  function leaveRoom()
  {
    ws.current.send("leave");
    leaveRoomClient();
  }

  function leaveRoomClient()
  {
    setJoinedRoom(false);
    setChatLog([]);
  }

  function joinRoom(userName, roomName)
  {
    setRoomName(roomName);
    ws.current.send("join " + userName + " " + roomName);
  }

  function joinRoomClient()
  {
    setJoinedRoom(true);
  }

  function sendMessage(message)
  {
    console.log("We's is sending: " + message);
    ws.current.send("message " + message);
  }
  
  function handleWsMessage(msg)
  {
    let msgObj = JSON.parse(msg.data);
    switch(msgObj.type)
    {
      case("join"):
        console.log("We're joining", msgObj);
        joinRoomClient(msgObj);
        break;
      case("message"):
        console.log("Here's a message: ", msgObj);
        let newMessage =  msgObj.user + ": " + msgObj.message;
        setChatLog([...chatlog, newMessage]);
        break;
      default:
        console.log("No appropriate type for msg...");
        console.log(msgObj);
        break;
    }
  }

  return (
    <div className="App">
      {joinedRoom ? <Room roomName={roomName} sendMessage={sendMessage} leaveRoom={leaveRoom} chatlog={chatlog}></Room> : <LoginPage joinRoom={joinRoom}></LoginPage> }
    </div>
  );
}

export default App;
