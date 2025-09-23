//
//  main.cpp
//  ForLoopPractice
//
//  Created by Jonathan Pulsipher on 8/20/25.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    
    //Printing with For and While loops
    //
    cout << "Printing 1 - 10 with for loop:\n";
    for(int i = 1; i <= 10; i++){
        cout << i << "\n";
    }
    
    cout << "Printing 1 - 10 with while loop:\n";
    int counter = 1;
    while (counter <= 10){
        cout << counter++ << "\n";
    }
    
    //THOUGHTS: For loop is more appropriate because we know the number of iterations beforehand and it is very readable. This is a standard use-case for the for loop.
    
    //Printing a user-submitted range
    //
    int start, end;
    cout << "Enter two numbers to print the range between them:\n";
    cin >> start >> end;
    cout << "Range:\n";
    if(start < end)
    {
        for(int i = start + 1; i < end; i++)
        {
            cout << i << "\n";
        }
    }
    else
    {
        for(int i = start - 1; i > end; i--)
        {
            cout << i << "\n";
        }
    }
    
    // Printing Odds 1-20 in two ways
    //
    cout << "Printing Odds 1-20 with 'if'\n";
    for(int i = 1; i < 20; i++)
    {
        if(i % 2 != 0)
            cout << i << "\n";
    }
    
    // Without if
    cout << "Printing Odds 1-20 without 'if' using +2 increment\n";
    for(int i = 1; i < 20; i += 2)
    {
        cout << i << "\n";
    }
    
    //THOUGHTS: If I had to choose, I would say incrementing by 2 is better because it is clear, skips a repeated calculation, and does half as many loops. One argument for the version that checks every time is that you're guaranteed odd print-outs, but for such a simple calculation it probably doesn't matter.
    
    //Adding up Positive numbers
    //
    cout << "Enter numbers for us to sum. End by entering any negative number:\n";
    int sum = 0;
    int input;
    while(true){
        cin >> input;
        if(input >= 0)
            sum += input;
        else
            break;
    }
    cout << "Your sum is: " << sum << "\n";
        
    // Multiplication Table
    //
    for(int i = 1; i <= 5; i++)
    {
        cout << i << "x*:";
        for(int j = 1; j <= 5; j++)
        {
            int product = i * j;
            if (product < 10)
                cout << "  " << product;
            else
                cout << " " << product;
        }
        cout << "\n";
    }
     
    return 0;
}
