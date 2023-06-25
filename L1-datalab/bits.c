/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    // 1 0 1
    // 0 1 1
    // 1 1 0
    // 0 0 0
    // ~x&y | x&~y
    int a = ~x & y;
    int b = x & ~y;
    return ~(~a & ~b);  // = a | b
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return 1 << 31;
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    // regular case
    // only when x = 0x7ffffff, (x + 1)  ~ x = 0xffffffff
    // + 1 makes overflow to 0
    int f1 = ((x + 1) ^ x) + 1;
    // special case, when x = 0xffffffff
    // 0xffffffff + 1 = 0
    int f2 = x + 1;
    return !!f2 & !f1;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    // f1 to f4 is four segments of x
    int f1 = (x & 0xaa);
    int f2 = ((x >> 8) & 0xaa);
    int f3 = ((x >> 16) & 0xaa);
    int f4 = ((x >> 24) & 0xaa);
    // only if f5 = f1 & f2 & f3 & f4 = 0xaa makes f5 ^ 0xaa 0
    int f5 = f1 & f2 & f3 & f4;
    return !(f5 ^ 0xaa);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return ~x + 1;
}
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    int rest = (x >> 4) ^ 3;  // rest should be 3, so 3 ^ 3 makes 0
    int masked = x & 0xf;
    int l8 = !(masked & 0x8);   // check if 4th digit is 1
    int le2 = !(masked & 0x6);  // check if 2rd and 3th digit is 1
    return (!rest) & (l8 | (le2));
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int neg_1 = ~1 + 1;
    int cond_mask = (!!x) + neg_1;
    // if !!x = 0, cond_mask = 0xffffffff
    // if !!x = 1, cond_mask = 0x0
    return (z & cond_mask) | ((~cond_mask) & y);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int is_x_neg = x >> 31;
    int is_y_neg = y >> 31;
    int unsign_mask = ~(0x1 << 31);
    int unsigned_x = x & unsign_mask;
    int unsigned_y = y & unsign_mask;
    // if x y has different sign, just return
    // x_neg  1 1 0 0
    // y_neg  1 0 1 0
    // result 0 1 0 1
    int case2 = is_x_neg & (!is_y_neg);

    // if all positive, compare ux and uy
    // if all negative, reverse comparing result
    int neg_unsigned_y = ~unsigned_y + 1;
    // x - y < 0
    int x_minus_y = unsigned_x + neg_unsigned_y;
    int smaller_than_zero = (x_minus_y >> 31) & 0x1;
    int case3 = (!(is_x_neg ^ is_y_neg)) & smaller_than_zero;
    // if x y equal, return 1
    int case4 = !(x ^ y);
    // printf("$$$$$$$$$%d$$$$$$$$$\n", x_minus_y);
    return case2 | case3 | case4;
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
    int all_ones = ~x;
    int sign_mask = 1 << 31;  // 0x10000000
    // int unsign_mask = sign_mask + (~0);  // 0x7ffffffff
    // // printf("unsign_mask:%x\n", unsign_mask);
    // int t1 = all_ones & unsign_mask;
    int t1 = all_ones ^ sign_mask;
    int t2 = t1 + 1;
    // printf("x:%d ----- %x %x %x %x\n", x, (~x) >> 31, t1, t2, t2 >> (15 + 16));
    // int k = -2147483648;
    // int k2 = 0x80000000;
    // printf("x:%d ----- %x\n", x, k ==);
    // printf("x:%d t1: %x t2:%x (~x):%x,  t2:%x\n", x, t1, t2, ~x, t2 >> 31);
    return (((~x) & t2) >> 31) & 0x1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    // convert negative to positive
    int sign_bit = (x >> 31) & 0x1;
    int all_ones = ~0;
    // printf("sign bit:%x\n", sign_bit);
    // if negative, 0xffffffff, if positive, 0x0
    int pos_mask = sign_bit + all_ones;
    // if negative, x = ~x + 1. If positive, x = x
    int transformed_x = ((~pos_mask) & (~x)) | ((pos_mask)&x);
    int mask = 0x55;
    int sum1 = 0;
    int mask2 = 0x33;
    int sum2 = 0;
    int mask3 = 0x0f;  // 0x0f0f0f0f
    int sum3 = 0;
    int mask4 = 0xff;  // 0x00ff00ff
    int mask5 = 0xff;  // 0x0000ffff
    // bit smearing
    mask = (mask << 8) | mask;
    mask = (mask << 16) | mask;
    mask2 = (mask2 << 8) | mask2;
    mask2 = (mask2 << 16) | mask2;
    mask3 = (mask3 << 8) | mask3;
    mask3 = (mask3 << 16) | mask3;
    mask4 = (mask4 << 16) | mask4;
    mask5 = (mask4 >> 8) | mask5;
    // printf("%x %x %x %x %x\n", mask, mask2, mask3, mask4, mask5);
    transformed_x = transformed_x | (transformed_x >> 16);
    transformed_x = transformed_x | (transformed_x >> 8);
    transformed_x = transformed_x | (transformed_x >> 4);
    transformed_x = transformed_x | (transformed_x >> 2);
    transformed_x = transformed_x | (transformed_x >> 1);
    // count bits
    // printf("x: %x, transformedx:%x\n", x, transformed_x);
    // 1010

    sum1 = (transformed_x & mask) + ((transformed_x >> 1) & mask);
    // printf("sum1:%x\n", sum1);
    // printf("(sum1 & mask2):%x ((sum1 >> 2) & mask2):%x\n", (sum1 & mask2), ((sum1 >> 2) & mask2));
    sum2 = (sum1 & mask2) + ((sum1 >> 2) & mask2);
    // printf("sum2:%x\n", sum2);
    // 0x0100 0100 0100 0100
    sum3 = (sum2 & mask3) + ((sum2 >> 4) & mask3);
    // printf("sum3:%x\n", sum3);
    sum3 = (sum3 & mask4) + ((sum3 >> 8) & mask4);
    // printf("sum3:%x\n", sum3);
    sum3 = (sum3 & mask5) + ((sum3 >> 16) & mask5);
    // printf("sum3:%x\n", sum3);

    // if (sum3 < 32 && x != -1 && (transformed_x - 1) != ((~transformed_x) & (0x7fffffff))) {
    //     sum3 += 1;
    // }
    // special case:0?
    // don't worry 0x80000000, it transforms to 0xffffffff
    return sum3 + 1;
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp_mask = 0x7f800000;
    unsigned frac_mask = 0x007fffff;
    unsigned max_minus_one_exp = 0x7f000000;
    unsigned exp_part = uf & exp_mask;
    unsigned frac_part = uf & frac_mask;
    unsigned sign_part = uf & 0x80000000;
    // unsigned isnegative = uf >> 31;
    unsigned frac_only_leftmost_1 = 0x00400000;
    if ((exp_part == exp_mask) || ((uf << 1) == 0)) {
        // if uf overflow(inf)
        // if nan, return nan
        return uf;
    }

    // if uf * 2overflow
    if (exp_part == max_minus_one_exp) {
        // return +/- inf
        return sign_part | exp_mask;
    }
    // if denormalized(exp == 0 and uf *2 not denormalized)
    if (exp_part == 0) {
        // if not overflow to normal float
        if (frac_part < frac_only_leftmost_1) {
            frac_part *= 2;
            return sign_part | frac_part;
        }
        // if overflow to normal case, same as normal case
        frac_part = (frac_part << 1) & frac_mask;
    }
    // normal
    // printf("%x\n", exp_part);
    exp_part += 0x800000;
    // printf("%x\n", exp_part);
    return sign_part | exp_part | frac_part;
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    unsigned exp_mask = 0x7f800000;
    unsigned frac_mask = 0x007fffff;
    // unsigned max_minus_one_exp = 0x7f000000;
    unsigned exp_part = uf & exp_mask;
    unsigned frac_part = uf & frac_mask;
    unsigned sign_part = uf & 0x80000000;  // not zero means negative
    unsigned out_of_range_ret_val = 0x80000000u;
    unsigned exp_part_val = exp_part >> 23;
    unsigned exp_val = exp_part_val - 127;
    // unsigned normal_move_amount =
    unsigned normal_val = 0;

    // if +/-zero
    // if ((uf & 0x7fffffff) == 0) {
    //     return 0;
    // }
    // if abs(uf) < 1
    // printf("%x\n", uf);
    // printf("%d\n", exp_part_val);
    if (exp_part_val < 127) {
        // printf("%x\n", 1);
        return 0;
    }

    // if out of range or uf = 0x80000000
    if (exp_part_val >= 159) {
        return out_of_range_ret_val;
    }
    // if NaN and inf
    if ((exp_part == exp_mask)) {
        return out_of_range_ret_val;
    }
    // normal case
    if (exp_val < 23) {
        normal_val = frac_part >> (23 - exp_val);
    } else {
        normal_val = frac_part << (exp_val - 23);
    }
    // printf("normal: %x\n", normal_val);
    // printf("exp_val: %d\n", exp_val);
    normal_val += 1 << exp_val;
    // printf("normal: %d\n", normal_val);
    if (sign_part != 0) {
        normal_val = ~normal_val + 1;
    }
    return normal_val;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    // if too small
    // -126 - 23 = -149
    // printf("%x\n", exp_val);
    unsigned max_val = 255 << 23;
    unsigned exp_val = x + 127;
    if (x < -149) {
        return 0;
    } else if (x < -126) {      // if denormalized
        return 1 << (x + 149);  // -149 << 1, -148 << 2
    } else if (x <= 127) {      // if not overflow
        return exp_val << 23;
    } else {  // overflow
        return max_val;
    }
}
