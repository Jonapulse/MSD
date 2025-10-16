
let xInput;
let yInput;

//function main(){
    console.log("We're connected");
    xInput = document.querySelector("#x_value");
    yInput = document.querySelector("#y_value");
    xInput.addEventListener('keypress', handleKeyPress);
    yInput.addEventListener('keypress', handleKeyPress);
//}
//document.onload = main;

//console.log("We're connected a little");

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
            fetch("calculate?x=" + xInput + "&y=" + yInput)
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
                    text => {document.querySelector("result_value").value = text;}
                )
                .catch(
                    error => { console.log("error: ", error);}
                )
        }
    }
}