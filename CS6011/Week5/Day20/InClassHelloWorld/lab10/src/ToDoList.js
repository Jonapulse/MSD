export default function ToDoList({list, remove}){

    console.log("rendering ToDoList");

    return(
        <ul>
            {list.map((name,index) => (<li key={index} onDoubleClick={(e)=>remove(index)}>{name}</li>))}
        </ul>
    );
}
