#include "Debug.h"
#include "iFloat.h"

/** @file iFloat.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in iFloat.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Brody Larson</b> goes here
 */

/* declaration for useful function contained in testFloat.c */
const char* getBinary (iFloat_t value);

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetSign (iFloat_t x) {
    return (x >> 15) & 1;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetExp (iFloat_t x) {
    return (x >> 10) & 0x1F;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetVal (iFloat_t x) {
    iFloat_t mantissa = x & 0x3FF;
    mantissa |= 0x400;
    if (floatGetSign(x) == 1) {
        return ~mantissa + 1;
    }
    return mantissa;
}

/** @todo Implement based on documentation contained in iFloat.h */
void floatGetAll(iFloat_t x, iFloat_t* sign, iFloat_t*exp, iFloat_t* val) {
    *sign = floatGetSign(x);
    *exp = floatGetExp(x);
    *val = floatGetVal(x);
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatLeftMost1 (iFloat_t bits) {
  //return the position of the left most 1
    int i;
    for (i = 15; i >= 0; i--) {
        if ((bits >> i) & 1) {
            return i;
        }
    }
    return -1; 
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAbs (iFloat_t x) {
    return x & 0x7FFF;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatNegate (iFloat_t x) {
  if(x != 0){
      return x ^ 0x8000;
  }else{
      return x;
  }
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAdd (iFloat_t x, iFloat_t y) {
      
      if(floatNegate(x) == y || floatNegate(y) == x){
        return (iFloat_t) 0;
      }


    //Debug showing IEEE for both params
    debug("x: %s", getBinary(x));
    debug("y: %s", getBinary(y));
    debug("STEP 1");

    iFloat_t xVal, yVal, xExp, yExp, xSign, ySign;
    //Get all components of each param
    floatGetAll(x, &xSign, &xExp, &xVal);
    floatGetAll(y, &ySign, &yExp, &yVal);
    //Checking that it all worked
    debug("X Sign: %d, X Exp: %d, X Val: %s", xSign, xExp, getBinary(xVal));
    debug("Y Sign: %d, Y Exp: %d, Y Val: %s", ySign, yExp, getBinary(yVal));
    debug("STEP 2");

    //Stores common exponent
    iFloat_t common;
    //Making x and y have common exponents
    if(xExp > yExp){
        common = xExp; 
        yVal >>= (xExp - yExp);
    }
    if(xExp < yExp){
        common = yExp;
        xVal >>= (yExp - xExp);
    }
    //check work
    debug("X Val: %s", getBinary(xVal));
    debug("Y Val: %s", getBinary(yVal));
    debug("common: %d", common);

    debug("STEP 3");

    //The actual line that does the sum
    iFloat_t sum = xVal + yVal;

    //Collecting sign bit from the SUM
    iFloat_t sign = floatGetSign(sum);

    debug("Sum: %s", getBinary(sum));
    debug("STEP 4");


    //if signed, negate
    if(floatGetSign(sum)){
        sum =~ sum + 1;
    }


    debug("Sum After Possible Negation: %s", getBinary(sum));
    debug("STEP 5");

    //Find leftmost 1
    iFloat_t leftMost = floatLeftMost1(sum);
    //normalize
    sum <<= (10 - leftMost);
    common -= (10 - leftMost);
    debug("Leftmost: %d", leftMost);
    debug("Exp After Normalization: %s", getBinary(common));
    debug("Sum After Normalization: %s", getBinary(sum));

    debug("STEP 6");
    debug("sign: %d", sign);
    debug("common: %s", getBinary(common));
    debug("sum: %s", getBinary(sum));


    //combine sign, common and sum and return
    iFloat_t result = (sign << 15) | (common << 10) | (sum & 0x3FF);
    debug("Result: %s", getBinary(result));
    return result;
    
    
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatSub (iFloat_t x, iFloat_t y) {
    if(x == y){
        return (iFloat_t) 0;
    }
	return floatAdd(x, floatNegate(y));
}


