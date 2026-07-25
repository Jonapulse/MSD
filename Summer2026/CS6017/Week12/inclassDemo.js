const pEl = d3.select("p").text("hello from D3!!!");

console.log(pEl);

const data = [
    { name: "chilis", rating: 2.5 },
    { name: "applebees", rating: 2.4 },
    { name: "waffle house", rating: 4.9 },
    { name: "golden corral", rating: 0.3 }
];


//We can override the elements of the join
// const unorderedlist = d3.select("ul")
    // .selectAll("li")
    // .data(data)
    // .join( enter => {
		// enter.append("li").attr("text", d=>d.name)
	// },
	// update => {
		// console.log(update.nodes().length)
		
		// return update.text(d=>d.name)
	// },
	// exit => {
		// exit.remove()
	// })

d3.select("#rating").on("click", function(event){
	const newRestaurantRating = {name: "taco bell", rating: 3.0}
	data.push(newRestaurantRating);
	render(data)
})

const svg = d3.select("body").append("svg");
svg.attr("width",500).attr("height",500).attr("backgroundcolor","blue");

xScale = d3.scaleLinear([.3,4.9],[0,500]).nice()
const colorCat = d3.scaleOrdinal(d3.schemeCategory10) //10 colors d3 considers good mix
svg.append("g").attr("transform","translate(0,300)").call(d3.axisTop(xScale)) //"g" means group, d3 approximate of div

render(data)
	
function render(data){
	const unorderedlist = d3.select("ul")
    .selectAll("li")
    .data(data)
    .join("li")
    .text(d => d.name);
	
	
	let rects = svg.selectAll("rect").data(data)
	.join("rect")
	.attr("x", 10)
	.attr("y", (d, i) => i * 60)
	.attr("height", 50)
	.attr("fill", (d,i) => colorCat(d))
	.attr("width", 0)
	.on("click", function (event, d){
		d3.select(this).transition().duration(1000).attr("fill", "black")
	})
	.transition()
	.duration(1000)
	.attr("width", (d,i) => xScale(d.rating))
	
	// let barGroup = svg.selectAll("rect").data(data)
						// .join("rect")

	// let barGroupRects = barGroup.append("rect")
						// .attr("x", 10)
						// .attr("y",(d,i)=> i*70)
						// .attr("fill", (d,i)=>colorCat(d))
						// .attr("height", 50)
						// .attr("width"), 0)
						// .on("click", function(event, d){
							// d3.select(this).transition().duration(1000).attr("fill","black")
						// }).transition()
						// .duration(1000)
						// .attr("width",d=>xScale(d.rating))
	
	// let barGroupText = barGroup.append("text")
						// .text( (d)=> d.name)
						// .style("font-size", "20px")
						.attr("transform", (d,i)=> 'translate(20,${i * 70 + 25})')
}
	


//Another approach we ain't doin?
// function* stateGenerator(){
	// const data=[10,20,30]
	
	// for(i =0; i < data.length; i++)
	// {
		// yield {items:data, activeIndex:i}
	// }
// }

//render(step.next.value())