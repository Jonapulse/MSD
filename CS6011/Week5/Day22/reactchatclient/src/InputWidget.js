function InputWidget({label, valueRef}){
    return(
        <div>
            {label}: <input ref={valueRef}></input>
        </div>
    );
}

export default InputWidget;