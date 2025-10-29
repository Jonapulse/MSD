import { StatusBar } from 'expo-status-bar';
import { useEffect } from 'react';
import { StyleSheet, Text, View, Button } from 'react-native';
import { useRef } from 'react';

export default function App() {
  
  //CAREFUL! As written, this will happen every time this re-renders.
  //How do we handle this? 'useRef' will not trigger
  // let ws = new WebSocket("ws://localHost:8080");

  let ws = useRef(null);
  //Could also have done let ws = useRef(new WebSocket("ws://localHost:8080"));

  useEffect(() => {
    ws.current = new WebSocket("ws://10.18.239.85:8081");

    ws.current.onopen = () => {ws.current.send("join Ahmad Games");};
    ws.current.onmessage = (e) => {console.log(e);};
    ws.current.onclose = (e) => {console.log(e);};
    ws.current.onerror = (e) => {console.log(e);};
    console.log("Call me once");
  }, []);

  useEffect(() => {
    console.log("Call me neighbor");
  });
  //The thing at the bottom is dependents. If it's empty it meansuseEffect is only 
  //called once. If there is a variable in there, this will be called when it changes.
  //NOTE: You can have multiple useEffect for the same thing.

  return (
    <Text>Jon it is you!</Text>
  );
  
 //The old default return. Left fer notes. Like that button thing.
  // return (
  //   <View style={styles.container}>
  //     <Text>Open up App.js to start working on your app!</Text>
  //     <Button style={styles.button} title="I'm a button"></Button>
  //     <StatusBar style="auto" />
  //   </View>
  // );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  button: { color: '#fff', backgroundColor: '#fff'}
});
