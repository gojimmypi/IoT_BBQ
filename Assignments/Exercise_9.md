
# Exercise 9 algorithms with respect to speed, RAM, and code space


In Quiz 1, multiple different implementations for bit reversal were given and you were asked to
consider the algorithms with respect to speed, RAM, and code space. (You can see the code at
Godbolt.)

Choose a small algorithm to implement in different ways. Describe when/why you might use
each. You can choose any small algorithm.

Some possible options include:
- How many bits are one in a given 32-bit uint?
- How many leading zeros are in a 32-bit uint?
- Trigonometry functions like sin, cos, tan
- Integer division with remainder
- Find the first 100 prime numbers

Turn in your code with notes about the pros and cons of each implementation to Discord
#assignment-submission by 9am on Feb 5th.

## Result

### How many bits are one in a given 32-bit uint

One possible implementation that I came up with:
```
static size_t BitCount(uint32_t n)
{
    size_t res = 0;
    uint32_t pos = 1; // ensure this is the same bit size as parameter!
    for (size_t i = 0; i < 32; i++)
    {
        // if the and operation is non-zero, we found a 1 bit
        if (n & pos)
        {
            res++;  
        }
        
        // get ready to look at the next bit position
        pos = (pos << 1);

        // no sensee in continuing if we found the answer
        if (pos > n)
        {
            break;
        }
    }
    return res;
}
```

I would use the above if I knew most of the data was smaller than 65,536 (1 + 0xFFFF). 
For efficiency, if one new that most data was larger than 0xFFFF, then the bit comparison could start at the left at the MSB instead.

If I _really_ want efficiency, I'd turn to [stackoverflow](https://www.google.com/search?q=How+many+bit+are_set+in+a+32-bit+uint+site%3Astackoverflow.com)
For instance [this clever implementation](https://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer):

```
int numberOfSetBits(uint32_t i)
{
     // Java: use int, and use >>> instead of >>. Or use Integer.bitCount()
     // C or C++: use uint32_t
     i = i - ((i >> 1) & 0x55555555);        // add pairs of bits
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);  // quads
     i = (i + (i >> 4)) & 0x0F0F0F0F;        // groups of 8
     return (i * 0x01010101) >> 24;          // horizontal sum of bytes
}
```

This is certainly not very intutive, at least not to me. Performance gains at the risk of future debugging head-ache.

Some tests:

```
    int n;
    n = BitCount(0xF); // 4
    n = BitCount(0x0); // 0
    n = BitCount(0x1); // 1
    n = BitCount(21);  // 3
    n = BitCount(0xFFFF);  // 16
    n = BitCount(0xFF000000); // 8
    n = BitCount(0xFFFFFFFF); // 32
```    

### How many leading zeros are in a 32-bit uint?

Here's what I cam up with, based on my above code for `BitCount()`:

```
static size_t BitCountLeadingZeros(uint32_t n)
{
    const int BitsToCount = 32;
    size_t res = 0;
    uint32_t pos = 1; // ensure this is the same bit size as parameter!
    
    for (size_t i = 0; i < BitsToCount; i++)
    {
        // get ready to look at the next bit position
        pos = (pos << 1);

        // no sensee in continuing if we found the answer (in this case the mask is larger than our inspection number
        if (pos > n)
        {
            res = (i + 1); // zero based, so we need to add one
            break;
        }
    }
    
    // if we actually found leading zeros, the quantity is the total number of bits minus the position where we stopped looking
    if (res)
    {
        res = BitsToCount - res;  
    }
    
    return res;
}
```
Here again: know your data. I would use the above if I knew most of the data was smaller than 65,536 (1 + 0xFFFF). 
For efficiency, if one new that most data was larger than 0xFFFF, then the bit comparison could start at the left at the MSB instead,
to minimize the number of iterations in the `for` loop.

If I _really_ want efficiency, I'd again turn to [stackoverflow](https://www.google.com/search?q=How+many+leading+zeros+are+in+a+32-bit+uint+site%3Astackoverflow.com). 
For instance, [this clever implementation](https://stackoverflow.com/questions/23856596/how-to-count-leading-zeros-in-a-32-bit-unsigned-integer):

```
x = x | (x >> 1);
x = x | (x >> 2);
x = x | (x >> 4);
x = x | (x >> 8);
x = x | (x >>16);
return pop(~x);
```

I'm not sure this is as intutively obvious as a basic for-loop, and would need some testing. For one, it appears to only be 16 bit. 
Always use care when using copy-paste from stackoverflow. ;)

Some tests:

```
    int n;
    n = BitCountLeadingZeros(0xF); // 28
    n = BitCountLeadingZeros(0x0); // an interesting case that "0" is not counted in the other 31 digits of leading zeros
    n = BitCountLeadingZeros(0x1); // also 31
    n = BitCountLeadingZeros(21);  // 27 leading zeros for 10101
    n = BitCountLeadingZeros(0xFFFF); // 16
    n = BitCountLeadingZeros(0xFF000000); // 0
    n = BitCountLeadingZeros(0xFFFFFFFF); // 0
```

## Trigonometry functions like sin, cos, tan

If `<Math.h>` is too big or not available, I'd probably look into using a lookup table. I would probably not even try to do this on my own, 
instead immediately searching [stackoverflow](https://www.google.com/search?q=implement+sin+in+c+site%3Astackoverflow.com),
such as [this](https://stackoverflow.com/questions/18662261/fastest-implementation-of-sine-cosine-and-square-root-in-c-doesnt-need-to-b):

```
/*
    On [-1000..+1000] range with 0.001 step average error is: +/- 0.000011, max error: +/- 0.000060
    On [-100..+100] range with 0.001 step average error is:   +/- 0.000009, max error: +/- 0.000034
    On [-10..+10] range with 0.001 step average error is:     +/- 0.000009, max error: +/- 0.000030
    Error distribution ensures there's no discontinuity.
*/

const double PI          = 3.141592653589793;
const double HALF_PI     = 1.570796326794897;
const double DOUBLE_PI   = 6.283185307179586;
const double SIN_CURVE_A = 0.0415896;
const double SIN_CURVE_B = 0.00129810625032;

double cos1(double x) {
    if (x < 0) {
        int q = -x / DOUBLE_PI;
        q += 1;
        double y = q * DOUBLE_PI;
        x = -(x - y);
    }
    if (x >= DOUBLE_PI) {
        int q = x / DOUBLE_PI;
        double y = q * DOUBLE_PI;
        x = x - y;
    }
    int s = 1;
    if (x >= PI) {
        s = -1;
        x -= PI;
    }
    if (x > HALF_PI) {
        x = PI - x;
        s = -s;
    }
    double z = x * x;
    double r = z * (z * (SIN_CURVE_A - SIN_CURVE_B * z) - 0.5) + 1.0;
    if (r > 1.0) r = r - 2.0;
    if (s > 0) return r;
    else return -r;
}

double sin1(double x) {
    return cos1(x - HALF_PI);
}
```

This is an interesting implementation. It would likely be slower than a lookup table with all the floating point multiplication and division, but probably much smalling than including `<Math.h>`



<< [Exercise 8](./Exercise_8.md) -- [Assignments](./README.md) --  [TBD]() >>