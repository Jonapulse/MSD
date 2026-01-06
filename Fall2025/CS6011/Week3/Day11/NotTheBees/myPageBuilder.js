function main(){
    let bodyElement = document.getElementsByTagName("body");

    //Title
    let titleElem = document.createElement("h1");
    titleElem.textContent = "Jon Pulsipher - Website Lab";
    document.body.appendChild(titleElem);

    //Intro w/ link
    let pElem = document.createElement("p");
    const textBefore = document.createTextNode("I made a website before, which you can see ");
    const textAfter = document.createTextNode("  I wanted to teach myself some React. I never got around to making it display correctly on mobile, and I'm unsure whether it helped or hurt my job search. (Shrug emoticon.)");
    let myLink = document.createElement("a");
    myLink.href = "https://www.jonahpulsipher.com";
    myLink.textContent = "here.";
    pElem.appendChild(textBefore);
    pElem.appendChild(myLink);
    pElem.appendChild(textAfter);
    document.body.appendChild(pElem);

    //div with two lists
    //List 1
    let listDiv = document.createElement("div");
    let orderedList = document.createElement("ol");
    orderedList.textContent = "Top three works of art: ";
    let ol1 = document.createElement("li");
    ol1.textContent = "Outer Wilds (a nice video game.)";
    orderedList.appendChild(ol1);
    let ol2 = document.createElement("li");
    let a_ol2 = document.createElement("a");
    a_ol2.textContent = "These dogs";
    a_ol2.href = "httsp://omfgdogs.com";
    ol2.appendChild(a_ol2);
    orderedList.appendChild(ol2);
    let ol3 = document.createElement("li");
    ol3.textContent = "Chicken Katsu Curry";
    orderedList.appendChild(ol3);
    listDiv.appendChild(orderedList);
    //List 2
    let unorderedList = document.createElement("ul");
    unorderedList.textContent = "Why I'm submitting this as a zipped file rather than uploading it online.";
    let ul1 = document.createElement("li");
    ul1.textContent = "I requested a username and password from Tech Support and they never sent me a password.";
    unorderedList.appendChild(ul1);
    let ul2 = document.createElement("li");
    ul2.textContent = "I followed up that request by re-requesting the password, and they did not respond.";
    unorderedList.appendChild(ul2);
    let ul3 = document.createElement("li");
    ul3.textContent = "We are mortal and will, one day, die, and I don't want to keep making requests to tech support.";
    unorderedList.appendChild(ul3);
    listDiv.appendChild(unorderedList);
    document.body.appendChild(listDiv);
    
    //Little nonsense table
    let myTable = document.createElement("table");
    let caption = document.createElement("caption");
    caption.textContent="My precious table";
    myTable.appendChild(caption);
    //Row 1
    let tr1 = document.createElement("tr");
    let th1 = document.createElement("th");
    th1.textContent = "My beautiful row";
    let td1a = document.createElement("td");
    td1a.textContent = "My beloved data element";
    let td1b = document.createElement("td");
    td1b.textContent = "A data element I don't like.";
    let td1c = document.createElement("td");
    td1c.textContent = "This data element is okay";
    myTable.appendChild(tr1);
    tr1.appendChild(th1);
    tr1.appendChild(td1a);
    tr1.appendChild(td1b);
    tr1.appendChild(td1c);
    //Row 2
    let tr2 = document.createElement("tr");
    let th2 = document.createElement("th");
    th2.textContent = "This row is phoning it in";
    let td2a = document.createElement("td");
    td2a.textContent = "1";
    let td2b = document.createElement("td");
    td2b.textContent = "2";
    let td2c = document.createElement("td");
    td2c.textContent = "3";
    myTable.appendChild(tr2);
    tr2.appendChild(th2);
    tr2.appendChild(td2a);
    tr2.appendChild(td2b);
    tr2.appendChild(td2c);
    document.body.appendChild(myTable);

    //Image
    let myImg = document.createElement("img");
    myImg.src = "bee1.png";
    document.body.appendChild(myImg);
}

main();