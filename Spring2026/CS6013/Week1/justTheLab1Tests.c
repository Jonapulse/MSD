
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
  if(byte_sort(0x019fa51283104cac) != 0xaca59f834c121001)
    return 0;

  //Simple Variation 2
  if(byte_sort(0x000333111222ccca) != 0xccca332212110300)
    return 0;

  //Simple Variation 3
  if(byte_sort(0xbabababaabababff) != 0xffbabababaababab)
    return 0;

  return 1;
}

int testNibbleSort()
{
  //Duplicates of ByteSort tests w/ Nibble result
  //Sort from Example
  if(nibble_sort(0x0403deadbeef0201) != 0xfeeeddba43210000)
    return 0;

  //Simple Variation 1
  if(nibble_sort(0x019fa51283104cac) != 0xfccaa98543211100)
    return 0;

  //Simple Variation 2
  if(nibble_sort(0x000333111222ccca) != 0xccca333222111000)
    return 0;

  //Simple Variation 3
  if(nibble_sort(0xbabababaabababff) != 0xffbbbbbbbaaaaaaa)
    return 0;

  return 1;
}

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
  printf(testByteSort() == 0 ? "ByteSort fails" : "ByteSort succeeds"); 
  printf("\n");
  printf(testNibbleSort() == 0 ? "NibbleSort fails" : "NibbleSort succeeds"); 
  printf("\n");
  
  char *my_name = "Jonathan"; 
  Elt *my_name_list = name_list(my_name);
  printf("Jonathan should match ");
  print_list(my_name_list);

  printf("\nAn ASCII self-portrait should be available in me.txt\n");
  free_list(my_name_list);
  draw_me();
}
