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