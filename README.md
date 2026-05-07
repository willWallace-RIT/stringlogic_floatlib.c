StringLogicFloatLib-C

> Ever run into a situation where you have string reggies but no numeric ones? I got you covered, boi.



StringLogicFloatLib-C is a low-level experimental C library for systems where:

numeric parsing is unavailable,

arithmetic operators are restricted,

everything behaves like string registers,

and you still need binary arithmetic, hex conversion, and float-style packing.


Instead of relying on:

atoi()

strtol()

sprintf()

numeric conversion helpers

or high-level arithmetic abstractions


this library builds operations manually from:

logic gates,

conditional branching,

ripple carry adders,

symbolic bit strings,

and two’s complement arithmetic.



---

Features

Logic Gates

Built entirely from conditional logic:

NOT

AND

OR

XOR



---

Arithmetic

String-based binary arithmetic:

Half Adder

Full Adder

Ripple Carry Adder

Two’s Complement

Binary Subtraction



---

Encoding

Supports symbolic conversion between:

Decimal strings

Binary strings

Hexadecimal strings

Simplified float layouts



---

Why?

Because sometimes you:

inherit cursed systems,

build fantasy hardware,

write emulators,

prototype custom CPUs,

make VM interpreters,

abuse game scripting engines,

or just want to see how far string arithmetic can go.



---

Example

char out[256];

BINARY_ADD(
    "00001111",
    "00000001",
    out
);

printf("%s\n", out);

Output:

00010000


---

Binary Subtraction

char out[256];

BINARY_SUB(
    "00001111",
    "00000001",
    out
);

printf("%s\n", out);

Output:

00001110


---

Decimal → Binary

char binary[256];

DECIMAL_TO_BINARY(
    "1234",
    binary
);

printf("%s\n", binary);

Output:

0001001000110100


---

Binary → Hex

char hex[256];

BINARY_TO_HEX(
    binary,
    hex
);

printf("%s\n", hex);

Output:

1234


---

Float Packing

The library includes a simplified symbolic float layout:

[ sign ][ exponent ][ mantissa ]

This is:

deterministic,

VM-friendly,

symbolic,

educational,


but not true IEEE754 arithmetic.


---

Compilation

Using GCC:

gcc stringlogic_floatlib.c -o stringlogic

Run:

./stringlogic


---

Architecture

The arithmetic system is synthesized manually through:

gate logic,

carry propagation,

conditional branching,

symbolic bit movement,

and register-like string buffers.


This mimics:

educational ALUs,

primitive CPUs,

constrained interpreters,

and logic-level arithmetic systems.



---

Intended Use Cases

Emulator development

Educational CPUs

Soft-logic systems

Fantasy architectures

Sandbox VMs

Embedded experiments

Retro-computing projects

Procedural logic engines

Digital logic teaching



---

Future Ideas

Full IEEE754 emulation

String multiplication/division

ALU simulation layer

Register bank abstraction

Stack machine support

Bytecode VM

Timing simulation

Symbolic memory arrays

Soft-FPU implementation



---

Safety Notes

This library intentionally:

sacrifices performance,

avoids standard numeric conversion paths,

and prioritizes transparency of logic flow.


It is educational and experimental rather than production-grade numeric infrastructure.


---

License

Do whatever. Break things responsibly.
