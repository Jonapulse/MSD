
let canvas;
let ctx;
let theBees = [];
let beeAnim;
let mousePos = {pos:{x: 0, y: 0}};
let mouseCaught = false;

let TOP_SPEED = 10;
let ACC = 0.2;
let BEE_NUM = 10;
let WIDTH = 500;
let HEIGHT = 500;
let HALF_IMAGE_WIDTH = 51;
let START_SPEED_VARIANCE = 3;
let ANIM_FRAMES = 5;

function notTheBees(){

    canvas = document.querySelector("canvas");
    ctx = canvas.getContext('2d');
    
    document.addEventListener("mousemove", updateMousePosition);
    
    beeAnim = [new Image(), new Image(), new Image(), new Image(), new Image()];
    beeAnim[0].src = "Images/bee1.png";
    beeAnim[1].src = "Images/bee2.png";
    beeAnim[2].src = "Images/bee3.png";
    beeAnim[3].src = "Images/bee4.png";
    beeAnim[4].src = "Images/bee5.png";

    for(let i = 0; i < BEE_NUM; i++)
    {
        let aBee = {pos:{x: Math.random() * WIDTH, y: Math.random() * HEIGHT}, 
            vel:{x: Math.random() * START_SPEED_VARIANCE + 1, y: Math.random() * START_SPEED_VARIANCE + 1},  
            animFrame: Math.floor(Math.random() * ANIM_FRAMES)};
        theBees.push(aBee);
    }

    beeAnim[4].onload = () =>{
        update();
    }

    //TODO: 
    // then starting w/ random position and velocity
    // then bee animation (w/ random offset)
    // then fix centering
}

function update()
{
    ctx.clearRect(0, 0, 500, 500);
    for(let i = 0; i < BEE_NUM; i++)
    {
        move(theBees[i]);  
        draw(theBees[i]);
    }

    if(!mouseCaught){
        window.requestAnimationFrame(update);
    }
    else
    {
        ctx.font = "30px serif";
        ctx.textAlign = "center";
        ctx.strokeText("The Bees! You have been stung.", WIDTH/2, HEIGHT/2);

        document.querySelector("#cageslament").play();
    }
}

function move(myBee)
{
    // Update Velocity
    //
    let towardsMouse = getDisplacement(myBee, mousePos);
    let speed = getMagnitude(myBee.vel);

    if(!isNaN(towardsMouse.magnitude)){
        //Check if bee will 'catch' cursor this update
        if(towardsMouse.magnitude < speed)
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

    if(speed > TOP_SPEED)
    {
        myBee.vel.x = (myBee.vel.x * TOP_SPEED) / speed;
        myBee.vel.y = (myBee.vel.y * TOP_SPEED) / speed;
    }

    // Move Bees
    //
    if (!mouseCaught)
    {
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

function draw(myBee)
{
    myBee.animFrame = (myBee.animFrame + 1) % ANIM_FRAMES;
    ctx.drawImage(beeAnim[myBee.animFrame], myBee.pos.x, myBee.pos.y);
}

function updateMousePosition(me){
    mousePos.pos.x = me.offsetX;
    mousePos.pos.y = me.offsetY;
}

window.onload = notTheBees;