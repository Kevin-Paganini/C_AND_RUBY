// String10 implementation

// do not add other includes
#include "sstring.h"
#include <stdio.h>

String10* make_string_10(const char *src) {
  
  String10 *s_10;

  //   1. allocate space on the heap using malloc
  s_10 = (String10 *)malloc(sizeof(s_10));

  //   2. set the len field to the number of characters in the source
  //      up to 10 characters
 
  int i = 0;
  //   3. copy len characters from src to the String10 value
  while(*src != '\0' && i < 10)
    s_10->text[i++] = *src++;

  s_10->len = i; 
  //   4. return the pointer
  return s_10;
}

bool string_10_equal(const String10 *a, const String10 *b)
{
  if ( a->len != b->len )
    return false;
  for(int i = 0; i < a->len; ++i)
    if ( a->text[i] != b->text[i] )
      return false;
  return true;
}

// prints string to standard output, no newlines
void print_string_10(const String10 *src) 
{
  for(int i = 0; i < src->len; ++i){
    printf("%c", src->text[i]);
  }
    // FIXME: write character i from the src's text
    
    
}

// deallocates space for the given item
void delete_string_10(String10 *item)
{
  // FIXME: implement this
  free(item);

}
