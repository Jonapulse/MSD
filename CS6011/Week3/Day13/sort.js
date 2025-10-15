

function main(){
}
document.onload = main;

let data = [7, 3, 25, -9, 25, 11];

function findSmallestIndex(array)
{
    let minInd = 0;
    for(let pos = 1; pos < array.length; pos++){
        if(array[pos] < array[minInd]){
            minInd = pos;
        }
    }
    return minInd;
}

let result = findSmallestIndex(data);
console.log("smallest: " + result);