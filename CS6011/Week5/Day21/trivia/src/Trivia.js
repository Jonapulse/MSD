
import { useState } from "react";
import { useRef } from "react";

function Trivia(){

    const [question, setQuestion] = useState("");
    const [answer, setAnswer] = useState("");
    const [displayAnswer, setDisplayAnswer] = useState(false);

    async function handleGetTrivia(){
        setDisplayAnswer(false);

        const response = await fetch('https://opentdb.com/api.php?amount=1');
        console.log("response:", response);
        if(!response.ok){
            console.log("Response error: ", response);
            //return; could do this to abort code, but instead should...
            throw new Error("Need to wait 5 seconds");
        }

        let data = await response.json();
        let result = data.results[0];
        setQuestion(result.question);
        setAnswer(result.correct_answer);
    }

    function showAnswer()
    {
        setDisplayAnswer(true);
    }

    return (
        <div>
            <button onClick={handleGetTrivia}>Trivia</button>
            <p>{question}</p>
            { (question !== "") && <button onClick={showAnswer}>Show Answer</button> }
            { (displayAnswer) && <p>{answer}</p>}
        </div>
    );
}

export default Trivia;