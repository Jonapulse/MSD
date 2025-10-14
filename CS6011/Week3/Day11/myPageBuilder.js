function main(){
    let bodyElement = document.getElementsByTagName("body");
    let titleHeader = document.createElement("h1");
    titleHeader.textContent = "Look at me! I'm Jon? Jonathan?";
    document.body.appendChild(titleHeader);

    console.log("Hello JS!");
}

main();