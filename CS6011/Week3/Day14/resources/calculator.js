
let xInput = document.querySelector("#x_value");
let yInput = document.querySelector("#y_value");
resultInput = document.querySelector("#result_value");
wsResultInput = document.querySelector("#ws_result_value");

xInput.addEventListener('keypress', handleKeyPress);
yInput.addEventListener('keypress', handleKeyPress);

///////////////////////
// create web socket connection
let ws = new WebSocket("ws://localhost:8000");
function handleWsOpen(){
    console.log("ws connected");
}

function handleWsMessage(msg){
    wsResultInput.value = msg.data;
    console.log("We are called");
}

function handleKeyPress(ke){

    if(ke.key === "Enter"){
        let x_val = Number(xInput.value);
        let y_val = Number(yInput.value);
        if(xInput.value === '' || isNaN(x_val)){
            alert("Please enter a valid number for X");
            xInput.value = "<Enter a Number>";
            xInput.select();
            return;
        }

        if(yInput.value === '' || isNaN(y_val)){
            alert("Please enter a valid number for Y");
            yInput.value = "<Enter a Number>";
            yInput.select();
            return;
        }

        if(ke.target === xInput)
        {
            yInput.focus();
        } else if(ke.target === yInput)
        {
            ws.send("" + x_val + ' ' + y_val);

            fetch("http://localhost:8000/calculate?x=" + x_val + "&y=" + y_val)
                .then(
                    response => {
                        if(!response.ok)
                        {
                            throw new Error("server had an issue");
                        }
                        return response.text();
                    }
                )
                .then(
                    text => {resultInput.value = text;}
                )
                .catch(
                    error => { console.log("error: ", error);}
                );
        }
    }
}