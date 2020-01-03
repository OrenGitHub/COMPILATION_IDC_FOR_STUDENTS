# Compilation
###### Exercise 5, Due 2/2/2020 before 14:00

## Introduction
Congratulations, you have made it to the final step of our compilation course.
In this last exercise you will translate the input Poseidon program to MIPS assembley.
[MIPS][MIPS-link] is a general purpose [RISC][RISC-link] instruction set architecture.
It was rather popular during the 1980s, but is mostly used now for specific 32-bit microcontrollers.
This architecture was chosen as the destination laguage of our compiler for its simplicity,
availabale documentation and complete toolchain (which even contains a graphic debugger).
There are essentially two steps for this exercise.
The first step is to translate the LLVM bitcode from the previous exercise.
The second step is to perform liveness analysis and register allocation
so that each temporary is assigned a physical register.
Note that you will ony be able to check your work after completing both steps.
Unilke LLVM bitcode, MIPS does not have the ability to execute a program
with an unbounded number of temporaries.

[MIPS-link]:https://en.wikipedia.org/wiki/MIPS_architecture
[RISC-link]:https://en.wikipedia.org/wiki/Reduced_instruction_set_computer

### LLVM bitcode to MIPS
The first step of this exercise is to translate the LLVM bitcode to MIPS.
This step ends with a MIPS file that has an unbounded number of temporaries.
Roughly speaking, translation is done one command at a time.
Translation of *some* commands is traightforward. For example, binary operations,
labels, jumps, conditional jumps, pointer arithmetic operations, casting and more.
The following table lists some examples:

```
        | LLVM bitcode example          | MIPS equivalent  |
--------+-------------------------------+------------------+
Binops  | %t3 = add i32 nsw %t1, %t2    | add t3, t1, t2   |
--------+-------------------------------+------------------+
Labels  | Label_4_if_body:              | Label_4_if_body: |
--------+-------------------------------+------------------+
Jumps   | br label %Label_5_if_end      | j Label_5_if_end |
--------+-------------------------------+------------------+
Casting | %t6 = bitcast i8* %t7 to i8** | move t7, t6      |
--------+-------------------------------+------------------+
```

Translation of *other* commands is not immediate.
For instance, accessing local variables,
passing arguments to a function and calling it,
returning from a called function and more.
The following table lists some LLVM bitcode examples that require
non trivial handling in the generated MIPS code.
The equivalent MIPS code column is deliberately missing and will be shown in class.

\pagebreak

```
          | LLVM bitcode example                  |
----------+---------------------------------------+
Call      | %t2 = call i32 @foo(i32 %t3, i32 %t4) |
----------+---------------------------------------+
Return    | ret i32 %t1                           | 
----------+---------------------------------------+
Local     | alloca i32 x, align 4                 |
Variables | store i32 3, i32* x                   |
----------+---------------------------------------+
```

### Register Allocation
The second step of the exercise requires that you implement a
standard "def-use" algorithm to extract the liveness range of every temporary.
Once these ranges are computed, you should build the so-called interference graph
whose nodes are temporaries, and (Temp_i,Temp_j) is an edge in the graph if
the liveness ranges of these temporaries intersect. After building the interference
graph, you will use a greedy algorithm to color its nodes with 8 colors.
The 8 colors stand for the 8 physical registers.

## Install SPIM and XSPIM
To complete this exercise you need a working MIPS simulator ([SPIM][SPIM-link])
and debugger ([XSPIM][XSPIM-link]).
Lucky for us, these tools are readily availabale from the official repository of Ubuntu.
Simply open the terminal and type:
```
$ sudo apt install spim xspim
```
Note that root privliges are needed for the installation of both tools.
To check your installation go to the source code folder and run `make everything`.
You should see the prime numbers from 2 to 100 printed to stdout.

[SPIM-link]:https://en.wikipedia.org/wiki/SPIM
[XSPIM-link]:http://www.cs.kent.edu/~durand/CS35101F06/Help/spimintro.html

\pagebreak

## Poseidon Semantics
The Poseidon semantics was thouroughly exaplained in the previous exercise,
and is brought here again for completeness. The next sections describe it
with a multitude of running examples.

### If and While Statements
**If statements** behave similar to (practically) all programming languages:
before executing their body, their condition is evaluated.
If it equals 0, the body is ignored, and control is transferred to the statement
immediately after the body. Otherwise, the body is executed exactly once,
then control is transferred to the statement immediately after the body.

```java
// Expected Output: 8 2 2
void foo(int i)
{
	if (i = 6)
	{
		PrintInt(8);
	}
	PrintInt(2);
}
void main(){ foo(6); foo(3); }
```

**While statements** behave similar to (practically) all programming languages:
before executing their body, their condition is evaluated.
If it equals 0, the body is ignored, and control is transferred to the statement
immediately after the body. Otherwise, the body is executed,
then the condition is evaluated again, and so forth.

```java
// Expected Output: 6 7 8 
void foo(int i)
{
	while (i < 9)
	{
		PrintInt(i);
		i := i + 1;
	}
}
void main(){ foo(6); foo(9); }
```

\pagebreak

### Binary Operations
**Integers** in Poseidon are artificially bounded between −2<sup>15</sup> and 2<sup>15</sup> − 1.
The semantics of integer binary operations in Poseidon is therefore somewhat different
than that of standard programming languages. It is presented in the following table,
and to distinguish Poseidon operators from the usual arithmetic signs, we shall
use a Poseidon subscript inside brackets: (`+[Poseidon]`, `-[Poseidon]` etc.)

```java
|       Binop        |   Condition            |    Value    |
+--------------------+------------------------+-------------+
|                    |  32767 <= a+b          |    32767    |
| a +[Poseidon] b    | -32768 <= a+b <  32767 |     a+b     |
|                    |           a+b < -32768 |   -32768    |
+--------------------+------------------------+-------------+
|                    |  32767 <= a-b          |    32767    |
| a -[Poseidon] b    | -32768 <= a-b <  32767 |     a-b     |
|                    |           a=b < -32768 |   -32768    |
+--------------------+------------------------+-------------+
|                    |  32767 <= a*b          |    32767    |
| a *[Poseidon] b    | -32768 <= a*b <  32767 |     a*b     |
|                    |           a*b < -32768 |   -32768    |
+--------------------+------------------------+-------------+
|                    |  32767 <= a/b          |    32767    |
| a /[Poseidon] b    | -32768 <= a/b <  32767 |     a/b     |
|                    |           a/b < -32768 |   -32768    |
+--------------------+------------------------+-------------+
```

**Strings** can be concatenated with binary operation `+`,
and tested for (contents) equality with binary operator `=`.
When concatenating two (null terminated) strings s1 and s2,
the resulting string s1s2 is allocated on the heap,
and should be null terminated.
The result of testing contents equality is either `1`
when they are equal, or `0` otherwise.

\pagebreak

### Order of Evaluation
**When calling a function** evaluation order matters.
Sent parameters should be evaluated from left to right. For instance,
the following code should output `32766`:

```java
int x=32767;
int foo(int i,int j)
{
	PrintInt(x);
}
int inc(){ x := x + 1; return x; }
int dec(){ x := x - 1; return x; }
void main(){ foo(inc(),dec()); }
```

**Global Variables**
should be evaluated according to their
order of appearence in the original program.
For example, the following code should output `32767`:

```java
int x=32767;
int inc(){ x := x + 1; return x; }
int dec(){ x := x - 1; return x; }
int y := dec();
int z := inc();
void main(){ PrintInt(z); }
```

**Assignments**
are evaluated according to a left before right paradigm.
So the following code should output `6`:

```java
int x := 4;
array IntArray = int[]
IntArray A := new int[9];
int inc(){ x := x + 1; return x; }
void main(){ A[inc()] := inc(); PrintInt(A[5]); }
```

**Binary Expressions**

\pagebreak

### System Calls
MIPS supports a somewhat limited set of system calls,
but it is enough to handle everything we need.

```
| Poseidon code       | MIPS code         | Remarks               |
+---------------------+-------------------+-----------------------+
| PrintInt(5);        | li $t2, 5         |                       |
|                     | move $a0, $t2     |                       |
|                     | li $v0, 1         | 1 = print int code    |
|                     | syscall           |                       |
|                     | li $a0, 32        | 32 = ascii of ' '     |
|                     | li $v0, 11        | 11 = print char code  |
|                     | syscall           |                       |
+---------------------+-------------------+-----------------------+
| string s := "M";    | .data             |                       |
| void main()         | Mstr: .asciiz "M" |                       |
| {                   | .text             |                       |
|     PrintString(s); | main:             |                       |
| }                   |   la $a0,Mstr     |                       |
|                     |   li $v0,4        | 4 = print string code |
|                     |   syscall         |                       |
|                     |   li $a0, 32      | 32 = ascii of ' '     |
|                     |   li $v0, 11      | 11 = print char code  |
|                     |   syscall         |                       |
|                     |   li $v0, 10      | 10 = exit code        |
|                     |   syscall         | finish main with exit |
+---------------------+-------------------+-----------------------+
| array IA = int[]    | .data             |                       |
| IA a := new int[5]; | a: .word 0        | initialize to null    |
|                     | .text             |                       |
|                     | main:             |                       |
|                     | li $a0,20         | 20 = 5 * 4 bytes      |
|                     | li $v0,9          | 9 = malloc code       |
|                     | syscall           |                       |
|                     | sw $v0,a          | allocation address    |
|                     |                   | returned in $v0       |
+---------------------+-------------------+-----------------------+
```

\pagebreak

## Poseidon Syntax
The Poseidon syntax is identical to the original syntax shown in the second exercise.
It is brought here again for completeness.

```java
Program  ::= dec+

dec      ::= varDec | funcDec | classDec | arrayDec

varDec   ::= ID ID [ ASSIGN exp ] ';'
         ::= ID ID ASSIGN newExp ';'
funcDec  ::= ID ID ( [ ID ID [ ',' ID ID ]∗ ] ) { stmt [ stmt ]∗ }
classDec ::= CLASS ID [ EXTENDS ID ] { cField [ cField ]∗ }
arrayDec ::= ARRAY ID = ID '[' ']'

exp      ::= var
         ::= ( exp )
         ::= exp BINOP exp
         ::= [ var '.' ] ID ( [ exp [ ',' exp ]∗ ] )
         ::= −INT | NIL | STRING

var      ::= ID
         ::= var '.' ID
         ::= var '[' exp ']'
	
stmt     ::= varDec
         ::= var ASSIGN exp ';'
         ::= var ASSIGN newExp ';'
         ::= RETURN [ exp ] ';'
         ::= IF    ( exp ) { stmt [ stmt ]∗ }
         ::= WHILE ( exp ) { stmt [ stmt ]∗ }
         ::= [ var '.' ] ID ( [ exp [ ',' exp ]∗ ] ) ';'

newExp   ::= new ID | new ID '[' exp ']'

cField   ::= varDec | funcDec

BINOP    ::= + | − | ∗ | / | < | > | =

INT      ::= [1 − 9][0 − 9]∗ | 0
```

\pagebreak

## Input
The input for this exercise is a single text file:
a semantically valid Posiedon program.

## Output
The output of this exercise is a single MIPS file
that conforms to the specification of SPIM `8.0`.

## Submission Guidelines
The skeleton code for this exercise resides (as usual) in subdirectory EX5 of the
course repository. COMPILATION/EX5 should contain a makefile building
your source files to a runnable jar file called COMPILER (note the lack of the
.jar suffix). Feel free to use the makefile supplied in the course repository, or
write a new one if you want to. Before you submit, make sure that your exercise
compiles and runs on Ubuntu 18.04.1 LTS.
This is the formal running environment of the course.

### Execution parameters
COMPILER receives 2 input file names:

 - InputPoseidonProgram.txt
 - OutputMIPSFile.s
