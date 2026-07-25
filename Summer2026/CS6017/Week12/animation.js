const data = [1,2,3,4]

const svg = d3.select("body").append("svg").attr("width", 500).attr("height",500)

const rects = svg.selectAll("rect")
				.data(data)
				.join("rect")
				.attr("width", 50)
				.attr("height", 50)
				.attr("x", 10)
				.attr("y", (d,i)=> i * 60)
				.transition()
				.duration(1000)
				.attr("x",(d,i) => i * 100)
				.transition()
				.duration(1000)
				.attr("x",(d,i) => (3-i) * 100)
				
async function animateElement(selection){
	await selection.transition()
		.duration(1000)
		.attr("x", 100).end()
	await selection.transition()
		.duration(1000)
		.attr("y", 100).end()
	await selection.transition()
		.duration(1000)
		.attr("x", 10).end()
}

animateElement(rects)