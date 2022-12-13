/**
 *  @author  Brody Larson
 */

#include <stdio.h>

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
char int_to_char (int value, int radix) {
    if(radix < 0 || value < 0 || radix <= value){
      return '?';
    } 
      if(radix == 10 && value < radix){
        return value + '0';
      }
     if(radix <= 9 && value <= 9){
     return (char)value + '0';
     }else{
     return (char)value + '0' + 7;
     }
     if(radix <= 9 && value >= radix){
     return (char)value + '0' + 1;
     }
     return (char)value + '0' + 10;
  
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char_to_int (char digit, int radix) {
  int check;
  if(digit < 0 || digit < '0'){
    return -1;
  } 
  else if(digit > '9' && digit < 'a'){
	 check =  digit - '0' - 7;
	  }
	else if(digit >= 'a'){
		check = digit - '0' - 32 - 7;
	}else{
    check = digit - '0';
  }

  if(check >= radix){
    return -1;
  }
  return check; 
}


/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void div_rem (int numerator, int divisor, int* remainder, int* quotient) {
    int loops = 0; 
    while (numerator >= divisor){
        loops++;
        numerator = numerator - divisor;
    }
    
    *remainder = numerator;
    *quotient = loops;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii_to_int (int valueOfPrefix, int radix) {
  char curr = getchar();
  if(curr == '\n'){
    return valueOfPrefix;
  }
  return ascii_to_int(valueOfPrefix + char_to_int(curr, radix), radix);
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int_to_ascii (int value, int radix) {
    if(radix > value){
      putchar(int_to_char(radix,value));  
    }
  int r = value / radix;
  int val = value % radix;
  int_to_ascii(radix, r);
  putchar(int_to_char(radix, val));
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double frac_to_double (int radix) {
  return -1.0;
}
