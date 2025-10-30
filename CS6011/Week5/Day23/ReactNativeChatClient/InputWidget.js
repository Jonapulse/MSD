import { Text, TextInput } from 'react-native';

function InputWidget({label, valueRef, onChangeText, defaultText}){
    return(
        <Text className="inputWidget">
            {label}{(label !== "") && ":"} <TextInput ref={valueRef} onChangeText={onChangeText} placeholder={defaultText}></TextInput>
        </Text>
    );
}

export default InputWidget;