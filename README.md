# Gexp

Gexp is a mathematical solver written in C++. It uses the Bodmas method.
Bodmas stands for B-Brackets, O-Orders (powers/indices or roots), D-Division, M-Multiplication, A-Addition, S-Subtraction.

What is the BODMAS rule

The Bodmas rule states that division and multiplication must be done before addition and subtraction in any mathematical example. And if there are brackets (or parentheses) and orders (of powers or roots), these must be done first of all. For example in the question 47 + 54 ÷ 9 the answer is 53 not 11.2r.

The Bodmas rule follows the order of the BODMAS acronym ie  B – Brackets, O – Order of powers or roots, D – Division, M – Multiplication A – Addition, and S – Subtraction. Mathematical expressions with multiple operators need to be solved from left to right in the order of BODMAS. Division and Multiplication are considered as interchangeable and depend on which comes first in the expression, as are Addition and Subtraction.

Some children use the Bodmas rule as a mnemonic (like Richard Of York Gave Battle In Vain is used to remember the colours Red, Orange, Yellow, Green, Blue, Indigo, Violet).

“Mathematical operations” are what you do to the numbers given. The four main operations are:

    addition (+);
    subtraction (-);
    multiplication (x);
    and division (÷).

When presented with a number sentence containing more than one operation (such as 3 + 4 x 2) the operations cannot be completed from left to right, but instead in their order of “importance”, which is what BODMAS stands for.

BODMAS stands for:

Brackets
Orders
Division/Multiplication
Addition/Subtraction

“Orders” means square roots and indices (which you may know as square numbers, powers or exponents).

## Supported expressions
Any valid combination of the following operators and functions, with floating point numbers (in decimal or exponential form) as operands can be parsed by Gexp. Parentheses can be used to override the default operator precedences. 

* Arithematic operators

`+` (addition), `-` (subtraction), `*` (multiplication), `/` (division), `%` (modulo) 

* Single-argument functions

`sin()`, `cos()`, `tan()`, `asin()`, `acos()`, `atan()`, `log()`, 
`exp()`, `log10()`, `exp10()`, `sqrt()`, `rnd()`, `round()`,
`floor()`, `fabs()`, `expm1()`, `sinh()`, `tanh()`, `cbrt()`

* Pre-defined math constants

`pi`, `e`

* Support for long variable names:

Test = sin(2)+12

#console commands
clear : clear all set variables
quit : quits the application

## Usage
The code snippet given below is a console based interpreter that interactively takes in math expressions from stdin, and prints out their results. 

```
#include "parser.h"

int main()
{
  Parser parser;

  std::cout.precision(12);

  while (std::cin) {
	std::cout << "Enter an expression:\n";
    std::string s;
    std::getline(std::cin, s);
    if (!std::cin || s == "quit") break;
    if (!std::cin || s == "clear") 
    {
		parser.Clear();
	}
    
    try {
      std::cout << parser(s) << '\n';
    } catch(const Lexical_error& e) {
      std::cerr << "Lexical error: " << e << '\n';
    } catch(const Syntax_error& e) {
      std::cerr << "Syntax error: " << e << '\n';
    } catch(const Runtime_error& e) {
      std::cerr << "Runtime error: " << e << '\n';
    }
  }
}


#TODO
Add support for two value functions.



