
let data = [1, 10, -3, 27, 45];
let data2 = ["Blob", "blob", "candy", "art"];
let dataNames = [{firstName: "Jon", lastName: "Pulsipher"}, {firstName: "Danny", lastName: "Zephyr"}, {firstName: "Tiny", lastName: "Apples"}];

function main(){
    let result = selectionSort(data, sortDefault);
    console.log(result);
    let result2 = selectionSort(data2, sortDefault);
    console.log(result2);
    let resultLastNames = selectionSort(dataNames, sortByFirstName);
    console.log(resultLastNames);
    resultLastNames = selectionSort(dataNames, sortByLastName);
    console.log(resultLastNames);
}
window.onload = main;


//You can use this function in the findIndexOfSmallest
function compare( a, b) {
    return a < b;
}

function findMinLocation(arr, start, compareTo)
{
    let minInd = start;
    for(let pos = start + 1; pos < arr.length; pos++){
        if(compareTo(arr[pos], arr[minInd]) < 0){
            minInd = pos;
        }
    }
    return minInd;
}

function selectionSort(arr, compare){
    for(let i = 0; i < arr.length - 1; i++)
    {
        let minIndex = findMinLocation(arr, i, compare);
        let temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
    return arr;
}

function sortDefault(a, b)
{
    if(a === b){
        return 0;
    }
    else{
        return a < b ? -1 : 1;
    }
}

function sortByLastName(nameA, nameB)
{
    if(nameA.lastName === nameB.lastName){
        return 0;
    }
    else{
        return nameA.lastName < nameB.lastName ? -1 : 1;
    }
}

function sortByFirstName(nameA, nameB)
{
    if(nameA.firstName === nameB.firstName){
        return 0;
    }
    else{
        return nameA.firstName < nameB.firstName ? -1 : 1;
    }
}
