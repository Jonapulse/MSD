function main(){
    
    let mTable = document.createElement('table');
    document.body.appendChild(mTable);

    let multRange = 10;
    for( let i = 1; i <= multRange; i++)
    {
        let mRow = document.createElement('tr');
        mTable.appendChild(mRow);
        for( let j = 1; j <= multRange; j++)
        {
            let mData = document.createElement('td');
            mData.textContent = String(i * j);
            mRow.appendChild(mData);
        }
    }

    console.log("Hello JS!");
}

main();