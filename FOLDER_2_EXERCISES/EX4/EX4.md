# Compilation
###### Exercise 4, Due 5/1/2020 before 14:00

## Introduction
For the first time ever we are going to compile Poseidon programs to LLVM bitcode.
[LLVM][Llvm-link] is an open source compiler infraructure and toolchain
that supports multiple source languages (C, CPP, C#, Go, etc.)
and multiple destination targets (x86, ARM, MIPS, x86_64, sparc, etc.).
Its [bitcode][bitcode-link] (or intermediate representation)
was designed as a language-independent, high-level portable assembley.
You will translate the input Poseidon program into a human readable (\*.ll) bitcode file.
Then, in order to check you work, the human readable (\*.ll) bitcode file
will be translated to a proper bitcode (\*.bc) file,
and linked with [clang][clang-link] to a native executable.
The input for this exercise is a semantically valid Poseidon program,
and the output is a human readable (\*.ll) file.

[Llvm-link]:https://llvm.org/
[bitcode-link]:https://llvm.org/docs/LangRef.html
[clang-link]:https://clang.llvm.org/

## Install LLVM
Download and install LLVM/clang [with this script][build-llvm-600-script]

[build-llvm-600-script]: https://github.com/OrenGitHub/COMPILATION_IDC_FOR_STUDENTS/blob/master/FOLDER_3_SOURCE_CODE/EX4/FOLDER_9_SCRIPTS/build-llvm-6.0.0

```java
class Father extends Grandfather { int i; int j; }
int Check(Father f)
{
	if (f = nil)
	{
	    return 333;
	}
	    return 774;
	}
}
```
## If and While Statements
**If statements** behave similar to (practically) all programming languages:
before executing their body, their condition is evaluated.
If it equals 0, the body is ignored, and control is transferred to the statement
immediately after the body. Otherwise, the body is executed exactly once,
then control is transferred to the statement immediately after the body.

**While statements** behave similar to (practically) all programming languages:
before executing their body, their condition is evaluated.
If it equals 0, the body is ignored, and control is transferred to the statement
immediately after the body. Otherwise, the body is executed,
then the condition is evaluated again, and so forth.

```java
class Father extends Grandfather { int i; int j; }
int Check(Father f)
{
	if (f = nil)
	{
	    return 800;
	}
	    return 774;
	}
}
```



| CODE | STATUS |
| ---- | ------ |
```java
class Father extends Grandfather { int i; int j; }
``` | dsfposdfpo
