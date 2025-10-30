function InputWidget({label, valueRef, defaultText}){
    return(
        <div className="inputWidget">
            {label}{(label !== "") && ":"} <textarea ref={valueRef} placeholder={defaultText}></textarea>
        </div>
    );
}

export default InputWidget;