
let colLabel = null;
 let rowLabel = null;


function main(){
    
    let mTable = document.createElement('table');
    document.body.appendChild(mTable);

    let multRange = 10;

    for( let i = 0; i <= multRange; i++)
    {
        let mRow = document.createElement('tr');
        
        mTable.appendChild(mRow);
        for( let j = 0; j <= multRange; j++)
        {

            
            let mData = document.createElement('td');
            if(i == 0){
                mData.className = "multLabel";
                mData.textContent = j == 0 ? "" : "* " + String(j); //For i and j both zero, this stays empty 
                colLabel = mData;
            } 
            else if(j == 0){
                mData.className = "multLabel";
                mData.textContent = "* " + String(i);
                rowLabel = mData;
            }
            else {
                mData.className = "multData";
                mData.textContent = String(i * j);
                mData.addEventListener("click", (mData) => {
                      //console.log(colLabel);

                    console.log(j);
                    console.log(i);
                    mData.className += "multDataChange";
                    colLabel.className = "focused";
                    // rowLabel.className = "focused";
                   console.log("Do I even exist?");
                })
            }
            mRow.appendChild(mData);
        }
    }

    let chaosButton = document.createElement('button');
    chaosButton.textContent = "No, not the...";
    document.body.appendChild(chaosButton);
}

main();