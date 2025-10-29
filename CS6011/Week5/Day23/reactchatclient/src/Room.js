function Room({leaveRoom}){

    return(
        <div>
            We are in Room
            <button onClick={leaveRoom}>Leave Room</button>
        </div>
    );
}

export default Room;