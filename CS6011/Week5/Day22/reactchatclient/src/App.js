import './App.css';
import LoginPage from './LoginPage';
import Room from './Room';
import { useState } from 'react';

function App() {

  const [joinedRoom, setJoinedRoom] = useState(false);

  function leaveRoom(){
    console.log("Attempting leave room")
    //todo: wait for confirmation
    setJoinedRoom(false);
  }

  function joinRoom(userName, roomName){
    console.log("Attempting join for " + userName + " to " + roomName);
    //todo: wait for confirmation
    setJoinedRoom(true);
  }

  return (
    <div className="App">
      {joinedRoom ? <Room leaveRoom={leaveRoom}></Room> : <LoginPage joinRoom={joinRoom}></LoginPage> }
    </div>
  );
}

export default App;
