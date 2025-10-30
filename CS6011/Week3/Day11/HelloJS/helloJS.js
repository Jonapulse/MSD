function main()
{
    document.writeln("hello world");
    console.log("hello world");
    
    //Q: What's the difference (between these methods of writing hello world?)
    //A: the 1st writes to the html, the second writes to the console.

    let testArr = ["fish", false, 67, 96.3, {purpose:"Being an object"}];
    console.log(testArr);
    testArr[2] += 33;
    console.log(testArr);

    //Q: What do you notice (about printing out testArr)?
    //A: Well in Safari the array printed out just as expected, the 2nd time with 67 updated to 100. Clicking to 
    // 'open' the console output did nothing. Chrome allowed me to 'open' the array, getting more information from
    // the object. When opened, it displayed the 'purpose' property but also a "[[Prototype]]:Array" that listed 
    // ~50 functions.

    console.log("4 + 5 using f: ", f(4, 5));
    console.log("4 + 5 using myFunction: ", myFunction(4, 5));
    console.log("1.3 + 3.7 using f: ", f(1.3, 3.7));
    console.log("1.3 + 3.7 using myFunction: ", myFunction(1.3, 3.7));
    console.log("hello + World using f: ", f("hello", "World"));
    console.log("hello + World using myFunction: ", myFunction("hello", "World"));
    console.log("4 + 3.7 using f: ", f(4, 3.7));
    console.log("4 + 3.7 using myFunction: ", myFunction(4, 3.7));
    console.log("1.3 + World using f: ", f(1.3, "World"));
    console.log("1.3 + World using myFunction: ", myFunction(1.3, "World"));

    //Q: Which syntax do you prefer (of the function definitions?) Can you detect any difference between the two 
    // ways of declaring functions?
    //A: Would I choose a favorite child? Both methods of declaration are beautiful in their own way. The second 
    // method, where a variable name is assigned to the function, may be more intuitive when passing functions
    // as arguments. I cannot detect a difference between the two ways of declaring functions beyond the 
    // syntactical difference.

    //Q: Test your functions. What do you observe?
    //A: The adding proceeds as expected, though floats summing to whole numbers display without decimal points. 
    // Adding floats and ints results in a float. Adding numbers to strings concatenates them.
}

function f(a, b){
    return a + b;
}

let myFunction = function(a, b){
    return a + b;
}
window.onload = main;