let mTable;
function main(){ 
    mTable = document.createElement('table');
    document.body.appendChild(mTable);

    const MULT_RANGE = 10;

    for( let i = 0; i <= MULT_RANGE; i++)
    {
        let mRow = document.createElement('tr');
        
        mTable.appendChild(mRow);
        for( let j = 0; j <= MULT_RANGE; j++)
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
                mData.addEventListener("click", (event) => {
                    const prevIDHaver = document.querySelector("#myHighlightedElement");
                    if(prevIDHaver != null){
                        prevIDHaver.removeAttribute("id");
                    }
                    event.target.id = "myHighlightedElement";
                    mData.id = "myHighlightedElement";
                })
            }
            mRow.appendChild(mData);
        }
    }

    let chaosButton = document.createElement('button');
    chaosButton.textContent = "Initiate chaos";
    chaosButton.addEventListener("click", causeChaos);
    document.body.appendChild(chaosButton);
}

main();

const startColor = [0, 0, 255]
const endColor = [255, 0, 0];
let timer;
const timerStep = 20;
const colorTransitionTime = 2000;

function causeChaos() {
    timer = 0;
    const interval = setInterval(() => {
        timer += timerStep;
        const t = Math.min(timer / colorTransitionTime, 1);
        const [r, g, b] = [
            Math.round(startColor[0] + (endColor[0] - startColor[0]) * t),
            Math.round(startColor[1] + (endColor[1] - startColor[1]) * t),
            Math.round(startColor[2] + (endColor[2] - startColor[2]) * t)
        ];
        document.body.style.backgroundColor = `rgb(${r}, ${g}, ${b})`;
        if (t >= 1) clearInterval(interval);
    }, timerStep);
}