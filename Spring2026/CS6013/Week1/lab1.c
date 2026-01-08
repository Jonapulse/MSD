/*********************************************************************
 *
 * File header comments go here... including student name, class, date, 
 * assignment, description, etc.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // For strlen()

/*********************************************************************
 *
 * The C functions in this lab use patterns and functionality often
 * found in operating system code. Your job is to implement them.
 * Additionally, write some test cases for each function (stick them in
 * functions [called xyzTests(), etc or similar]) Call your abcTests(),
 * etc functions in main().
 *
 * Write your own tests for each function you are testing, then
 * share/combine tests with a classmate.  Try to come up with tests that
 * will break people's code!  Easy tests don't catch many bugs! [Note
 * this is one specific case where you may share code directly with
 * another student.  The test function(s) from other students must be
 * clearly marked (add '_initials' to the function name) and commented
 * with the other student's name.
 *
 * Note: you may NOT use any global variables in your solution.
 * 
 * Errata:
 *   - You can use global vars in your testing functions (if necessary).
 *   - Don't worry about testing the free_list(), or the draw_me() functions.
 *
 * You must compile in C mode (not C++).  If you compile from the
 * commandline run clang, not clang++. Submit your solution files on
 * Canvas.
 *
 *********************************************************************/

unsigned long variable_bit_sort(unsigned long arg, int num_bits)
{
  unsigned int bottom_byte = 0x00ff;
  unsigned int sorted_byte = 0;
  int bit_groups = 64 / num_bits;
  for(int i = 0; i < bit_groups; i++)
  {
    unsigned int max = 0;
    int max_index = -1;
    for(int j = 0; j < bit_groups; j++)
    {
      unsigned int byte_val = (arg >> j * num_bits) & bottom_byte;
      if(byte_val > max){
        max = byte_val;
        max_index = j;
      }
    }
    //push the latest max onto the lower end of the sorted byte
    sorted_byte <<= num_bits; 
    sorted_byte |= max;

    //Zero out the max num_bits using a left and right mask of 1s.
    unsigned long left_mask = ~0;
    int shiftLeft = max_index + 1;
    left_mask <<= shiftLeft * num_bits;
    unsigned long right_mask = ~0;
    int shiftRight = bit_groups - max_index;
    right_mask >>= num_bits * shiftRight;
    arg &= left_mask | right_mask;
  }
  return sorted_byte;
}

/*********************************************************************
 *
 * byte_sort()
 *
 * specification: byte_sort() treats its argument as a sequence of
 * 8 bytes, and returns a new unsigned long integer containing the
 * same bytes, sorted numerically, with the smaller-valued bytes in
 * the lower-order byte positions of the return value
 * 
 * EXAMPLE: byte_sort (0x0403deadbeef0201) returns 0xefdebead04030201
 * Ah, the joys of using bitwise operators!
 *
 * Hint: you may want to write helper functions for these two functions
 *
 *********************************************************************/

 /**
  * 
  */
unsigned long byte_sort( unsigned long arg )
{
  return variable_bit_sort(arg, 8);
}

/*********************************************************************
 *
 * nibble_sort()
 *
 * specification: nibble_sort() treats its argument as a sequence of 16 4-bit
 * numbers, and returns a new unsigned long integer containing the same nibbles,
 * sorted numerically, with smaller-valued nibbles towards the "small end" of
 * the unsigned long value that you return
 *
 * the fact that nibbles and hex digits correspond should make it easy to
 * verify that your code is working correctly
 * 
 * EXAMPLE: nibble_sort( 0x0403deadbeef0201 ) returns 0xfeeeddba43210000
 *
 *********************************************************************/

unsigned long nibble_sort( unsigned long arg )
{
  return variable_bit_sort(arg, 4);
}

/*********************************************************************/

typedef struct elt {
  char val;
  struct elt *link;
} Elt;

/*********************************************************************/

/* Forward declaration of "free_list()"...
 *    This allows you to call free_list() in name_list() [if you'd like].
 */

void free_list( Elt* head ); // [No code goes here!]

/*********************************************************************
 *
 * name_list( name )
 *
 * specification: allocate and return a pointer to a linked list of
 * struct elts
 *
 * - the first element in the list should contain in its "val" field the
 *   first letter of the passed in 'name'; the second element the second
 *   letter, etc.;
 *
 * - the last element of the linked list should contain in its "val" field
 *   the last letter of the passed in name and its "link" field should be a
 *   null pointer.
 *
 * - each element must be dynamically allocated using a malloc() call
 * 
 * - you must use the "name" variable (change it to be your name).
 *
 * Note, since we're using C, not C++ you can't use new/delete!
 * The analog to delete is the free() function
 *
 * - if any call to malloc() fails, your function must return NULL and must
 *   also free any heap memory that has been allocated so far; that is, it
 *   must not leak memory when allocation fails.
 *
 * Implement print_list and free_list which should do what you expect.
 * Printing or freeing a nullptr should do nothing.
 *
 * Note: free_list() might be useful for error handling for name_list()... 
 *
 *********************************************************************/

Elt *name_list( char * name )
{
   return NULL;
}

/*********************************************************************/

void print_list( Elt* head )
{
  //TODO: Step through printing name
}

/*********************************************************************/

void free_list( Elt* head )
{
  //TODO: Step through printing list
}

/*********************************************************************
 *
 * draw_me()
 *
 * This function creates a file called 'me.txt' which contains an ASCII-art
 * picture of you (it does not need to be very big).
 * 
 * Use the C stdlib functions: fopen, fclose, fprintf, etc which live in stdio.h
 * - Don't use C++ iostreams
 *
 *********************************************************************/

void draw_me()
{
}

/*********************************************************************
 *
 * Test Code - Place your test functions in this section:
 *
 *     Remember, when testing name_list(), you should create a 'myName'
 *     variable and pass it in.
 */
int testByteSort(){
  //Sort from Example
  if(byte_sort(0x0403deadbeef0201) != 0xefdebead04030201)
    return 0;

  //Simple Variation 1
  if(byte_sort(0x019fa51283104cac) != 0xfccaa98543211100)
    return 0;

  //Simple Variation 2
  if(byte_sort(0x000333111222ccca) != 0xccca333222111000)
    return 0;

  //Simple Variation 3
  if(byte_sort(0xbabababababababa) != 0xbbbbbbbbaaaaaaaa)
    return 0;

  return 1;
}
// ...
// ...

/*********************************************************************
 *
 * main()
 *
 * The main driver program.  You can place your main() method in this
 * file to make compilation easier, or have it in a separate file.
 *
 *********************************************************************/

int main()
{
  printf("Hello World\n");
  printf(testByteSort() == 0 ? "ByteSort fails" : "ByteSort succeeds"); 


  //Testing default behavior
  unsigned int test = 0xffffffff;
  // test <<= 8;
  // test <<= 8;
  // test <<= 8;
  // test <<= 8;
  // test = ~0;
  // unsigned int alt = (~0) >> 8;
  // test >>= 8;
  // test >>= 8;
  // test >>= 8;
  // test >>=8;


  printf("and done");
}
