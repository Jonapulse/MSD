//
//  main.cpp
//  FunctionPractice
//
//  Created by Jonathan Pulsipher on 8/22/25.
//

#include <ctime>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

float GetHypotenuse(float a, float b)
{
    return sqrt(a * a + b * b);
}

float GetXYVel(float speed, float angle, bool doX)
{
    if(doX)
        return speed * cos(angle);
    else
        return speed * sin(angle);
}

bool isCapitalized(string s){
    //Taking advantage of ascii values because 26 if statements would be gross
    return s[0] > 65 && s[0] < (65 + 26);
}

string boolToString(bool val)
{
    if(val)
        return "true";
    else
        return "false";
}


int main(int argc, const char * argv[]) {
    /*
    //Exercise a) Hypotenuse
    float sideA, sideB;
    cout << "Enter the two side-lengths of a right triangle and we will output the hypotenuse for you: \n";
    cin >> sideA >> sideB;
    float hypotenuse = GetHypotenuse(3, 4);
    cout << "\nYour hypotenuse has a length of: " << hypotenuse << '\n';
    
    //Exercise b) X/Y Velocity
    float speed, angle;
    cout << "Enter your speed and your angle (radians), and we'll give you your X and Y velocity: \n";
    cin >> speed >> angle;
    
    float xVel = GetXYVel(speed, angle, true);
    float yVel = GetXYVel(speed, angle, false);
    cout  << "\nYour X velocity is: " << xVel << "\nYour Y velocity is: " << yVel << '\n';

    //Exercise c)
    std::time_t result = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&result))
      << result << " seconds since the Epoch\n";
    */
    //Test for isCapitalized
    string capitalCheck;
    cout << "Enter a work to check if it's capitalized: \n";
    cin >> capitalCheck;
    if(isCapitalized(capitalCheck))
        cout << "This is capitalized.\n";
    else
        cout << "Not capitalized.\n";
    //Oops. I wrote out this stuff before using boolToString to test isCapitalized.
    cout << "Oops, I got ahead of myself (T/F): " << boolToString(true) << '\n';
    
    //Question/Answer section -
    //
    
    //"Which functions are being called in the Example code? "
    //Ans: std::time(), std::asctime(), and std::localtime()
    
    //"Write a function that performs the hypotenuse task described above, but does not read from std::cin. What parameters should it take, and what will it return? Why wouldn't you want to get the input from std::cin inside your function?"
    //Ans: I sent it sideA and sideB and it returned sideC(hypotenuse. We don't want std::cin within the function because it would violate SoC (Seperation of Concern.)
    
    //"Why would it be difficult to turn the speed/velocity task above into a function? What imperfect solutions can you come up with that wrap that code into one (or more) functions?"
    //Ans: It's hard because x and y speed are doing the same things but use different trigonometric functions for their return. I addressed it by taking a 'doX' bool to choose the path. It's imperfect - I don't like that doX is the 'default' when that's not meaningful - but I worry making it more elegant would require making it much more complex.
    
}
