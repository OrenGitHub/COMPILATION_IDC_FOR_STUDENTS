# Compilation
###### Exercise 4, Due 5/1/2020 before 14:00

## Introduction
For the first time ever we are going to compile Poseidon programs to LLVM bitcode.
[LLVM](https://llvm.org/) is an open source compiler infraructure and toolchain
that supports multiple source languages (C, CPP, C#, Go, etc.)
and multiple destination targets (x86, ARM, MIPS, x86_64, sparc, etc.).
Its [bitcode](https://llvm.org/docs/LangRef.html) (or intermediate representation)
was designed as a language-independent, high-level portable assembley.
We are going to translate Poseidon programs into a human readable (\*.ll) file.
Then, in order to check you work, the (\*.ll) file will be translated to a proper
bitcode (\*.bc) file, and linked with clang to a native executable.
The input for this exercise is a semantically valid Poseidon program,
and the output is a human readable (\*.ll) file.

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
**While statements** behave similar to (practically) all programming languages:
before executing their body, their condition is evaluated. If it equals 0, the body
is ignored, and control is transferred to the statement immediately after the
body. Otherwise, the body is executed, then the condition is evaluated again,
and so forth.
**If statements** behave similar to (practically) all programming languages: be-
fore executing their body, their condition is evaluated. If it equals 0, the body is
ignored, and control is transferred to the statement immediately after the body.
Otherwise, the body is executed exactly once, then control is transferred to the
statement immediately after the body.

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
