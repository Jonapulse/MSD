
let canvas;
let ctx;
let bee;
let mousePos = {pos:{x: 0, y: 0}};
let mouseCaught = false;

let SPEED = 3;
let TOP_SPEED = 10;
let ACC = 0.2;
let WIDTH = 500;
let HEIGHT = 500;

function notTheBees(){

    //TESTING FIRST
    canvas = document.querySelector("canvas");
    ctx = canvas.getContext('2d');
    //Make an image
    //Draw image on canvas
    bee = {pos:{x:100, y:100}, vel:{x:0, y:0}};
    bee.img = new Image();
    bee.img.src = "Images/bee1.png";

    bee.img.onload = () =>{
        update();
    }
    
    document.addEventListener("mousemove", updateMousePosition);
    
    //TODO: 
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
    if(!mouseCaught){
        window.requestAnimationFrame(update);
    }
    else
    {
        ctx.font = "30px serif";
        ctx.textAlign = "center";
        ctx.strokeText("The Bees! You have been stung.", WIDTH/2, HEIGHT/2);
    }
}

function move(myBee)
{
    // Update Velocity
    //
    let towardsMouse = getDisplacement(myBee, mousePos);
    if(!isNaN(towardsMouse.magnitude)){
        //Check if bee will 'catch' cursor this update
        if(towardsMouse.magnitude < SPEED)
        {
            mouseCaught = true;
            return;
        }
        else
        {
            myBee.vel.x += towardsMouse.direction.x * ACC;
            myBee.vel.y += towardsMouse.direction.y * ACC;
        }
    }
    //Check bounce
    if(myBee.pos.x < 0 || myBee.pos.x > WIDTH)
    {
        myBee.vel.x *= -1;
        myBee.pos.x += myBee.vel.x; //Nudge so it doesn't get stuck
    }
    if(myBee.pos.y < 0 || myBee.pos.y > HEIGHT)
    {
        myBee.vel.y *= -1;
        myBee.vel.y += myBee.vel.y; //Nudge so it doesn't get stuck
    }

    let speed = getMagnitude(myBee.vel);
    if(speed > TOP_SPEED)
    {
        myBee.vel.x = (myBee.vel.x * TOP_SPEED) / speed;
        myBee.vel.y = (myBee.vel.y * TOP_SPEED) / speed;
    }

    // Move Bees
    //
    if (!mouseCaught)
    {
       // console.log(thisBee);
        myBee.pos.x += myBee.vel.x;
        myBee.pos.y += myBee.vel.y;
    }
}

// Returns direction and magnitude of vector from 'from' to 'to
//
function getDisplacement(from, to)
{
    let dirVec = {x: to.pos.x - from.pos.x, y: to.pos.y - from.pos.y};
    let magnitude = getMagnitude(dirVec);
    dirVec.x = dirVec.x / magnitude;
    dirVec.y = dirVec.y / magnitude;
    return {direction: dirVec, magnitude: magnitude};
}

function getMagnitude(vec){
    return Math.sqrt(vec.x * vec.x + vec.y * vec.y);
}

function draw(thisBee)
{
    ctx.clearRect(0, 0, 500, 500);
    ctx.drawImage(thisBee.img, thisBee.pos.x, thisBee.pos.y);
}

function updateMousePosition(me){
    mousePos.pos.x = me.offsetX;
    mousePos.pos.y = me.offsetY;
}

window.onload = notTheBees;