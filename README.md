# Full Cross Correlation
System Programming

## Asm function call implementation
NASM on 32-bit Linux

Full cross correlation on two 1-D arrays.
Returns number of non-zero elements in the output arrays.


## Cross Correlation

![crossCorrelation](https://user-images.githubusercontent.com/32519328/66757561-1b818b80-eea5-11e9-8527-c491a97119b1.png)


## Linking & Compiling

  nasm -f elf32 -g cross_correlation_asm_full.asm

  gcc -c -g main_asm.c

  gcc -g cross_correlation_asm_full.o main_asm.o -o testCrosCorrelation

  ./testCrosCorrelation



