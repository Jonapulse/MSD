
let canvas;
let ctx;
let bee;
let mousePos = {pos:{x: 0, y: 0}};
let SPEED = 2;

function notTheBees(){

    //TESTING FIRST
    canvas = document.querySelector("canvas");
    ctx = canvas.getContext('2d');
    //Make an image
    //Draw image on canvas
    bee = {pos:{x:100, y:100}, vel:{x_v:0, y_v:0}};
    bee.img = new Image();
    bee.img.src = "Images/bee1.png";

    bee.img.onload = () =>{
        update();
    }
    
    document.addEventListener("mousemove", updateMousePosition);
    
    //TODO: 
    // Get Bees following you...
    // Arrest the game on 'contact'
    // then the cute way...
    // then add bouncing... 
    // then bee animation (w/ random offset)
    // then recognizing the mouse off-screen...
    // then starting w/ random position and velocity
    
    //then start with like 10 bees. 
}

function update()
{
    move(bee);
    draw(bee);
}

function move(thisBee)
{
    let towardsMouse = getNormalVec(thisBee, mousePos);
    if(!isNaN(towardsMouse.x))
    {
      thisBee.pos.x += towardsMouse.x * SPEED;
      thisBee.pos.y += towardsMouse.y * SPEED;
    }
    else
    {
        thisBee.pos.x += 1;
       // console.log(towardsMouse);
    }
}

function getNormalVec(from, to)
{
    console.log("To");
    console.log(to);
    console.log("From");
    console.log(from);
    let dirVec = {x: to.pos.x - from.pos.x, y: to.pos.y - from.pos.y};
    console.log("Dir vec");
    console.log(dirVec);
    let magnitude = Math.sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
    dirVec.x = dirVec.x / magnitude;
    dirVec.y = dirVec.y / magnitude;
    return dirVec;
}

function draw(thisBee)
{
    ctx.clearRect(0, 0, 500, 500);
    ctx.drawImage(thisBee.img, thisBee.pos.x, thisBee.pos.y);
    window.requestAnimationFrame(update);
}

function updateMousePosition(me){
    mousePos.pos.x = me.offsetX;
    mousePos.pos.y = me.offsetY;
}

window.onload = notTheBees;