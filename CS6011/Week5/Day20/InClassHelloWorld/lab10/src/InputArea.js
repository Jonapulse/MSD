import { useRef} from 'react';

export default function InputArea({add}){

    let inputRef = useRef();

    function addTaskAndClear()
    {
        add(inputRef.current.value);
        //inputRef.current.value = "";
    }

    return(
            <div>
            <textarea ref={inputRef}></textarea>
            <button onClick={()=>addTaskAndClear()}>Add Task</button>
        </div>
    );
}