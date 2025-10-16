
function notTheBees(){

    //TESTING FIRST
    let canvas = document.querySelector("canvas");
    let ctx = canvas.getContext('2d');
    //Make an image
    //Draw image on canvas
    let bee = {pos:{x:100, y:100}, vel:{x_v:0, y_v:0}};
    bee.img = new Image();
    bee.img.src = "Images/bee1.png";

    bee.img.onload = () =>{
        ctx.drawImage(bee.img, bee.pos.x, bee.pos.y);
    }
    
    //TODO: set up the rest of the game
}


notTheBees();