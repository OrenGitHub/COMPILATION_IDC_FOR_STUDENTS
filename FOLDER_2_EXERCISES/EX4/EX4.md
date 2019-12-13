# Compilation
###### Exercise 4, Due 5/1/2020 before 14:00

## Introduction
For the first time ever we are going to compile Poseidon programs to LLVM bitcode.
[LLVM][LLVM-link] is an open source compiler infraructure and toolchain
that supports multiple source languages (C, CPP, C#, Go, etc.)
and multiple destination targets (x86, ARM, MIPS, x86_64, sparc, etc.).
Its [bitcode][bitcode-link] (or intermediate representation)
was designed as a language-independent, high-level portable assembley.
Bitcode files come in two flavours, or formats:
machine readable and human readable.
Machine readable (\*.bc) bitcode files can be transformed
into human readable ones with [llvm-dis][llvm-dis-link].
Human readable (\*.ll) bitcode files can be transformed
into machine readable ones with [llvm-as][llvm-as-link].
In this exercise you will translate the input Poseidon program
into a human readable (\*.ll) bitcode file.
Then, in order to check you work, the human readable bitcode file
will be translated into a proper machine readable bitcode file,
and linked with [clang][clang-link] to a native executable.

[LLVM-link]:https://llvm.org/
[bitcode-link]:https://llvm.org/docs/LangRef.html
[llvm-dis-link]:https://llvm.org/docs/CommandGuide/llvm-dis.html
[llvm-as-link]:https://llvm.org/docs/CommandGuide/llvm-as.html
[clang-link]:https://clang.llvm.org/

## Install LLVM
To complete this exercise you need a working LLVM + clang.
The formal LLVM + clang version for our course can be downloaded and installed
with this [build-llvm-script][build-llvm-script-link].
Note that this is a debug build, so allow at least one hour for it to finish.
In addition you will need to have root privliges for the final install step of the script.
To check your installation go to the source code folder and run `make everything`.
You should see the prime numbers from 2 to 100 printed to stdout.

[build-llvm-script-link]: https://github.com/OrenGitHub/COMPILATION_IDC_FOR_STUDENTS/blob/master/FOLDER_3_SOURCE_CODE/EX4/FOLDER_9_SCRIPTS/build-llvm-6.0.0

## Poseidon Semantics
Until now used the term semantics to describe legal and illegal programs.
But a programming language semantics also describes the way a program is meant to be executed.
What is the order of evaluation when a mathematical expression is computed?
What is the explicit underlying mechanism that controls execution of while loops? etc.
The following sections describe the Poseidon semantics with a multitude of running examples.

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

| CODE | STATUS |
| ---- | ------ |
```java
class Father extends Grandfather { int i; int j; }
``` | dsfposdfpo
