import logo from './logo.svg';
import './App.css';
import { useState } from 'react';
import { useRef} from 'react';
import ToDoList from './ToDoList';
import InputArea from './InputArea';

function App() {

  const [list, setList] = useState(["Does", "this", "work"]);

  const [count, setCount] = useState(0);

  let addItem = (taskStr) =>
  {
    setList([...list,taskStr]);
  }

  let deleteItem =  (removeIndex) =>
  {
    console.log(removeIndex);
    let tempList = list;
    let removeList = [];
    for(let i = 0; i < tempList.length; i++){
      if(i != removeIndex)
        removeList.push(tempList[i]);
    }
    setList(removeList);
    console.log(list);
  }

  return (
    <div className="App">
      <header className="App-header">
        <p>
          To-Do List:
        </p> 
        <ToDoList list={list} remove={deleteItem}></ToDoList>
        <InputArea add={addItem}></InputArea>
      </header>
    </div>
  );
}

export default App;
