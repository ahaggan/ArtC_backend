/* Need to: 

Validate challenge is completed (look at parser for ways to validate).

Create tutorial pop-ups: when user presses help, statements become highlighted, eg. if-statement highlighted. User hovers over if-statement and an
explanation of how it works is given.

Create a message that is shown when user completes challenge eg. "Well Done! Challenge completed. Move onto the next level."

Create an arrow to move from one challenge to the other. Only becomes clickable once challenge is completed.*/

//CHALLENGE EXAMPLES

//EXAMPLE CODE: Changing variables, Easy Mode. Start example:
run{
fractal tree {
	iterations 10;
	shape line;
	colour red;
    if iterations 5 
	then {
		colour blue;
	    }
    }
}

//Challenge 1: Change the colour of the fractal after 3 iterations
run{
fractal tree {
	iterations 10;
	shape line;
	colour red;
    if iterations 3
	then {
		colour <VARCOL>;
	    }
    }
}

//Challenge 2: Change the total number of iterations and the type of fractal.
run{
fractal <VARFRAC> {
	iterations <VARNUM>;
	shape line;
	colour red;
    if iterations 5
	then {
		colour <VARCOL>;
	    }
    }
}

//Challenge 3: Change shape after 4 iterations and the colour after 6 iterations.
run{
fractal tree {
	iterations 10;
	shape line;
	colour red;
    if iterations 4
	then {
		shape <VARSHAPE>;
	    }
	if iterations 6
	then {
		shape <VARCOL>;
	    }
    }
}

// Conditional statements/boolean logic, Medium Mode. Starting example:
run{
fractal tree {
	iterations 10;
	shape line;
	colour red;
    if iterations 5 
	then {
		colour blue;
	    }
    }
}


//Challenge 1: Start with one colour, switch to another at the third iteration for 2 iterations, then back to original.
run{
fractal tree {
	iterations 10;
	shape line;
	colour red;
    from iterations 3
	to iterations 5 {
		colour <VARCOL>;
	    }
    }
}


//Challenge 2: Switch first and second colour around.
run{
fractal tree {
	iterations 10;
	shape line;
	colour <VARCOL>;
    if NOT iterations <VARNUM> 
	then {
		colour <VARCOL>;
	    }
    }
}
