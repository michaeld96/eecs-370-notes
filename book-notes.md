# EECS 370 Book Notes

## 1.1 Introduction

<img src = "imgs/byte-term-table.png" align = "center">

## 1.2 Eight Great Ideas in Computer Architecture

1. Design for Moore's Law - basically, when building computer architecture we will have to anticipate where the power of hardware will be when the project is finished. 
2. Abstraction - Hide unnecessary things from a user. Think of a "black box."
3. Make the Common Case Fast.
4. Performance via Parallelism.
5. Performance via Pipelining. 
6. Performance via Prediction. 
7. Hierarchy of Memories.
8. Dependability via Redundancy. 

## 1.3 Below your Program

<img src = "imgs/circle-computer.png" align = "center">

There are many types of systems software, but two are critical for computers, an operating system and a compiler.

A operating system is the layer that communicates between software and hardware. Some of the important functions are handling basic input and output, allocating memory, protected sharing of the computer when multiple applications are being run at one time.

A compiler translates high-level programming languages into assembly.

### From a High-Level Language to the Language of Hardware

A 0 or 1 are referred to as a binary digit or bit. Instructions are just a collection of bits that the computer understands.

An *assembler* (a program that translates a symbolic version of instructions into the binary version) can translate `add A,B` into `1000110010100000` which in binary tells the compiler to add two numbers.

Binary is called *machine language*.

Here is an example of swapping two elements in an array. We first show the high-level in C, and then what it looks like in assembly. This is to show the level of abstraction at play.

Below is C:
```C
swap(int v[], int k)
{
    int temp;
    temp = v[k];
    v[k] = v[k+1];
    v[k+1] = temp;
}
```
Below is `asm`.

```asm
swap:
    multi $2, $5,4
    add $2, $4,$2
    lw $15, 0($2)
    lw $16, 4($2)
    sw $16, 0($2)
    sw $15, 4($2)
    jr $31
```

## 1.4 Under the Covers

A *bit map* is a matrix of bits. Pixels are matrices of bits.

Computer hardware for graphics consist mainly of a *raster refresh*, *buffer, or frame buffer* to store the bit map. The image represented onscreen is stored in the frame buffer, and bit pattern per pixel is read out to the graphics display at the refresh rate. The goal a but map is to represent what is on the screen.

The image below is a frame biffer with just 4 bits per pixel.

<img src = "imgs/comp-graphic-ex.png" align = "center">

Each coordinate in the frame buffer determines the shade of the corresponding coordinate for the raster scan CRT display. Pixel $(X_0, Y_0)$ contains the bit pattern `0011`, which is a lighter shade than the pattern `1101` from pixel $(X_1, Y_1)$.

List of Definitions for Hardware:
* Integrated Circuit - Also called a chip. The chip contains millions of transistors usually.
* CPU - Also called a processor. The CPU contains the datapath and control, which adds numbers, test numbers, signals I/O devices to actives, and many other operations.
* Datapath - The component of the processor that performs arithmetic operations.
* Control - The component of the processor that commands the datapath, memory, and I/O devices according to the instructions of the program.
* Memory - The storage area in which programs are kept when they are running and that contains the data needed by the running programs.
* Dynamic Random Access Memory (DRAM) - Memory built as an integrated circuit (chip); it provides random access to any location. 
* Cache Memory - A small fast memory that acts as a buffer for a slower, larger memory.
* Static Random Access Memory (SRAM) - Also memory built as an integrated circuit, but faster and less dense than DRAM (SRAM is more expensive than DRAM).
* Instruction Set Architecture - This is simply referred to as architecture, but it provides an interface between the hardware and the lowest-level software.
* ABI (Application Binary Interface) - This is a combination of the basic instruction set and the operating system interface for application programmers.

An instruction set allows computer designers to talk about functions independently from the hardware that performs them. An example is talking about the function of a digital clock like keeping the time, and not thinking about the clock hardware like the LED display.

### A Safe Place for Data

When talking about a computer *volatile*, this means that when the power of a computer is shut off, all the data is lost. DRAM for example only retains data if the DRAM is receiving power.

*Nonvolatile memory* for example is like a DVD, the DVD doesn't forget what is stored on it when power is out. Nonvolatile memory is used when there is no power, and it is used to store programs between runs.

*Main memory* is also known as *primary memory*, is memory used to hold programs while they're running and is typically stored in the DRAM.

*Secondary memory* is nonvolatile memory used to store programs between runs; typically consists of flash memory or hard drives.

## 1.7 The Power Wall

The dominant technology for integrated circuits (chips) is called CMOS (complementary metal oxid semiconductor). The primary source of energy consumption is when the transistor switches from on (1) to off (0).

## Chapter 2 Instructions: Language of the Computer

## 2.2 Operations of the Computer Hardware

Every computer has the ability to perform arithmetic; the LEGv8 assembly language notation

```asm
Add a, b, c
```

instructs to computer to add the two variables `b` and `c`, and to put their sum in `a`. In each LEGv8 arithmetic instruction performs only one operation and must have exactly three values.

Suppose we want to have the sum of four variables `b`, `c`, `d`, and `e` into variable `a`. We would do the following sequence of instructions:

```asm
ADD a, b, c     // The sum of b and c is placed into a.
ADD a, a, d     // The sum of b, c, and d is now placed into a.
ADD a, a, e     // The sum of b, c, d, and e is now placed into a.
```

<img src = "imgs/LEGv8-chart.png" align = "center">

<img src = "imgs/LEGv8-chart-cont.png" align = "center">

Let's show two quick examples from C to LEGv8.

First one, we will show the difference of executing two lines from C to LEGv8. We'll perform an addition operation and a subtraction operation.

```c
int main()
{
    a = b + c;
    d = a - e;
}
```
```asm
ADD a, b, c     // adding b and c, and storing it into a.
SUB d, a, e     // subtracting a from e and storing the result in d.
```

Now we will evaluate this complex expression from C to LEGv8.

```c
int main()
{
    f = (g + h) - (i + j);
}
```
```asm
ADD t0, g, h
ADD t1 i, j
SUB f, t0, t1
```

## Operands of the Computer Hardware

The operands of arithmetic instructions are restricted; they must be from a limited number of special locations built directly in hardware called *registers.* 

Registers are primitives in hardware design that are also visible to the programmer when the computer is completed. The size of a register in LEGv8 is 64 bits; groups of 64 bits occur so frequently that they are given the name *doubleword*. One major difference between variables of a programming language and registers is the limited number of registers, typically 32 on current computers like LEGv8.

### Register Example: Compiling a C assignment using registers

It's the compiler's job to assoicate program variables to register. The code from C:
```c
f = (g + h) - (i + j);
```
The variables `f,g,h,i,j` are assigned to registers `X19, X20, X21, X22, X23`. The compiled programmer is very similar to the code written in LEGv8 from the last example except the variable names are replaced with the registers. Note: `X9, X10` correspond to the variables `t0, t1`. 

Therefore, the code from c `f = (g + h) - (i + j);` turns into 

```asm 
ADD X9, X20, X21
ADD X10, X22, X23
SUB X19, X9, X10
```

### Memory Operands

Let's start this discussion with a definition, *data transfer instructions*, which is a command that moves data between memory and registers. Since we have only 32 of them in LEGv8 we need to reuse these registers for other uses.

To access a word (32 bit) or a doubleword, the instruction must supply the memory *address* (a value used to delineate the location of specific data elements within a memory array).

The data transfer instruction that copies data from memory to a register is traditionally called *load*. The format of the load instruction is the name of the operation followed by the register to be loaded, then register and a constant used to access memory. The sum of the constant portion of the instruction and the contents of the second register forms the memory address. The LEGv8 instruction for this is `LDUR` standing for *load register.*

### Example: Compiling an assignment when an operand is in memory.

Let's say that `A` is an array of 100 doublewords and the compiler has associated the variables `g` and `h` with the registers `X20` and `X21`. Let's also say that the starting address, or *base address*, of the array is `X22`. Compile the following C assignment statement:

```c
g = h + A[8]
```
To convert the following C code to LEGv8, we need must transfer `A[8]` to a register. The address of this array element is the sum of the base of the array `A`, found at register `X22` plus the number to select element 8. This data should be placed into a temporary register. In the code below, we put make `X9` the temporary register.

```asm
LDUR X9, [X22, #8]  \\ temporary register x9 gets A[8].
ADD X20, X21, X9 // g = h + A[8].
```

*Note:* `X22` is the base register, and the constant in a data transfer instruction `8` is called the offset.

Computers divide into those that use the address of the leftmost or "big end" buts as the doubleword address versus those that use the rightmost or "little end" byte. LEGv8 can work either as *big-endian* or *little-endian*. Since the order matters only if we access the identical data both as a doubleword and as eight bytes, few need to be aware of the "endianess."

Byte addressing also affects the array index. To get the proper byte address  in the code that we used for the example, *the offset to be added to the base register `X22` must be $8 \times 8$, or 64*, so that the load address will select `A[8]` and not `A[8/8]`.

The instruction to copy data from a register to memory is called *store*. The operation is similar to load as we put the operation name, followed by the register to be stored, then the base register, and finally the offset to select the array element. The LEGv8 command for store is `STUR`, standing for *store register*.

<img src = "imgs/memory-for-doublewords.png" align = "center">

In the picture above, it stresses the idea of doublewords must start at addresses that are multiples of 8. This requirement is called *alignment restriction*.

### Example: Compiler using load and store

Assume variable `h` is associated with register `X21` and the base address of the array `A` is `X22`. What is the LEGv8 assemly code for the C assignment statement below?

```c
A[12] = h + A[8]
```

We first load the array from memory from base address `X22`, but we use the proper offset of byte addressing in the load register. Then we add, just like we did before. Now we store the sum into `A[12]`, using $8 \times 12 = 96$, as the offset and register `X22` to be the base register.

```asm
// first, load the array form memory into a temporary register.
LDUR X9, [X22, #64]
// perform the addition, and store into the same register.
ADD X9, X21, X1
// store the sum into base register X22 with offset of 96.
STUR X9, [X22, #96]
```

Many programs have more variables than the computer has registers so the compiler tries to keep the most frequently used variables in registers and place the rest in memory, using loads and stores to move variables between registers and memory. The process is called *spilling* registers. LEGv8 data transfer instruction only reads one operand or write one operand, without operating on it. Thus, registers take less time to access and have higher throughput than memory, making data in registers both considerably faster to access and simpler to use.

### Constant or Immediate Operands

MAny times a program will use a constant in an operation, for example incrementing an index to point to the next element of an array.

To add a constant 4 to register `X22`:

```asm
LDUR X9, [X20, AddrConstant4] // X( = constant 4)
ADD X22, X9, X22 // X22 = X9 + X22 (X9 == 4)
```

This is assuming that `X20 + AddrConstant4` is the memory address of the constant 4.

A way that would avoid load instructions is to offer versions of the arithmetic instructions in which one operand is a constant. This quick add instruction with one constant operand is called `add immediate` or `ADDI`. To add 4 to register X22:

```asm 
ADDI X22, X22, #4
```
*Note* `XZR` is hard-wired to be the value 0 and corresponds to register number 31.

## 2.4 Signed and Unsigned Numbers

To start off, let's look at the following equation:

$$d \times \text{Base}^i$$

$d$ is the digit, $i$ starts at 0 and increases right to left. Base is what base-system we are using. 

For example, $1011_{\text{two}}$ is:

$$(1 \times 2^3) + (0 \times 2^2) + (1 \times 2^1) + (1 \times 2^0) = 11$$

<img src = "imgs/64-split-32-for-1011.png" align = "center">

*Least significant bit* is used to refer to the rightmost bit (bit 0 above), and *most significant bit* to the leftmost bit (bit 63).

In binary, leading `0`s means positive, and leading `1`'s means negative.

Below is an image of positive and negative numbers:

<img src = "imgs/negative-number-example.png" align = "center">

All negative numbers have a 1 in the most significant bit (the right most). This is usually called the *sign bit* (right most bit).

### Example: Binary to Decimal Conversion

What is the decimal value of this 64-bit two;s complement number?

`11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111100`

To answer this question, we will put the leading bit to be negative and the rest of the following bits positive because the first will evaluation to large negative number and the rest will be a large positive number leaving us with the negative result we want. 

$$(1 \times -2^{63}) + (1 \times 2^{62}) + (1 \times -2^{61}) + \cdots + (1 \times 2^1) + (0 \times 2^0)$$

$$ = -4$$

When loading a 64-bit doubleword into a 64-bit register, the signed and unsigned loads are identical. ARMv8 does offer two flavors of byte loads: *load byte,* `LDURB` treats the bute as an unsigned number and thus zero-extend to fill the leftmost bits of the register. *Load byte signed* `LDURSB` works with signed integers.

There is a short cut when working with complement numbers. First is to negate a two's complementary binary number, then add one to the result.

## 2.5 Representing Instructions in the Computer

Instructions are kept in the computer as a series of high and low electronic signals and may be represented as numbers. Each piece of an instruction can be considered as an individual number, and placing these numbers side by side forms the instruction. The 32 registers of LEGv8 are just referred to by their number, from 0 to 31.

### Example: Translating a LEGv8 Assembly Instruction into a Machine Instruction

We'll show the LEGv8 language version of instruction represented below as a combination of decimal numbers and then binary numbers.

```asm
ADD X9, X20, X21
```
The decimal numbers are show below:

$$\fbox{1112}\fbox{21}\fbox{0}\fbox{20}\fbox{9}$$


Each of the segments of the instruction is called a *field*. The first field $\fbox{1112}$ tells the LEGv8 computer that this instruction performs addition. The second field gives the number of the register that is second source operand for the addition (20 for `X20`). Each of the decimal numbers like 9 correspond with the register number like `X9` (register number corresponds to decimal number without `X` in front). The third field is $\fbox{0}$ because it is unused. Each field corresponds to the binary numbers in the image below:

<img src = "imgs/example-bit-result.png" align = "center">

This layout of the instruction is called the *instruction format*. We can see that the bits add up to 32 bits (that is why 0 is 6 bits).

We will use hexadecimal (base 16) to read binary numbers. As base 16 is a power of 2, we can convert by replacing each group of binary digits by a single hexadecimal digit.

### Example: Binary to Hexadecimal and Back

Covert the following 8-digit hexadecimal and 32-bit binary numbers into other base:

```
eca8 6420 (base-hex)
0001 0011 0101 0111 1001 1011 1101 1111 (base-two)
```
Let's solve the hex first. We will break down each number into a four bit groups.
```
eca8 6420
1110 1100 1010 1000 0110 0100 0010 0000
```

The other, we will convert each four chunk into hex:

```
0001 0011 0101 0111 1001 1011 1101 1111 (base-two)
1357 9bdf
```

### LEGv8 Fields

<img src = "imgs/LEGv8-fields.png" align = "center">

Below is the fields in LEGv8 instructions:

* opcode: Basic operation of the instruction, and this abbreviation is
* Rm: The second register source operand.
* shamt: Shift amount.
* Rn: The first register source operand.
* Rd: The register designation operand. It gets the result of the operation.

### Example: translating LEGv8 Assembly Language into Machine Language

If `X10` has the base of the array `A` and `X21` corresponds to `h`. What is the C code to LEGv8?

```c
A[30] = h + A[30] + 1;
```

```
LDUR X9 [X10, #240] // load in A[30] to X9
ADD X9, X21, X9 // h + A[30]
ADDI X9, X9, #1 // h + A[30] + 1
STUR X9 [X10, #240] // stores h + A[30] + 1 back into A[30]
```
## 2.6 Logical Operations

<img src = "imgs/LEGv8-bit-ops.png" align = "center">

The table above is a list of bit operations. 

To bit shift left or right in LEGv8, there is a shift instructions for it! *Logical shift left* is denoted at `LSL`, and *logical shift right* is denoted as `LSR`

Lets look at simple example of bit shifting in LEGv8:

```asm
LSL X11, X19, #4 // X11 = X19 << 4 bits
```

What the code block above is saying is we take register 19 shift it left 4 bits and store the result in register 11.

Shifting is known as the *shamt* field in the R-format. Here is what the code block looks like in R-format:

<img src = "imgs/shift-left-example.png" align = "center">


