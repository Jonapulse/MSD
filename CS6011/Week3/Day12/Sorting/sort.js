

function main(){
}
document.onload = main;

let data = [7, 3, 25, -9, 25, 11];

//You can use this function in the findIndexOfSmallest
function compare( a, b) {
    return a < b;
}

function findMinLocation(arr, start)
{
    let minInd = start;
    for(let pos = start + 1; pos < arr.length; pos++){
        if(arr[pos] < arr[minInd]){
            minInd = pos;
        }
    }
    return minInd;
}

function selectionSort(arr){
    for(let i = 0; i < arr.length - 1; i++)
    {
        let minIndex = findMinLocation(arr, i);
        let temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
    return arr;
}

let result = selectionSort(data);
console.log(result);