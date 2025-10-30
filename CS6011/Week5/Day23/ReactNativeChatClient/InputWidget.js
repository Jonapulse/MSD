import { Text, TextInput } from 'react-native';

function InputWidget({label, valueRef, defaultText}){
    return(
        <Text className="inputWidget">
            {label}{(label !== "") && ":"} <TextInput ref={valueRef} placeholder={defaultText}></TextInput>
        </Text>
    );
}

export default InputWidget;