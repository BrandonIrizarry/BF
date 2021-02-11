### BF
The notorious Brainfuck (abbreviated "BF") language was created by Urban Müller in 1993. My take is that the scandalous name helps draw attention and interest to the language, separating it a bit from something that would otherwise be considered "meh". It could even
become a gateway language to learn about other, less conspicuously-named esolangs.

[The Wikipedia article](https://en.wikipedia.org/wiki/Brainfuck) is easy to follow,
and more or less definitive. [This Youtube video](https://www.youtube.com/watch?v=qK0vmuQib8Y&t=4s) is a notable introduction to the language, and definitely kindled my
interest in BF somewhat.

### Overview Of The Interpreter
The interpreter first reads in the program, and in the process guards against
unbalanced loop brackets. The source is then interpreted; loop starting
positions are pushed on a stack, which are read when a jump is performed.
They're popped when the loop is finished.

The interpreter's complexity derives in most part from the need to handle
loops, which can be nested.

### Room For Improvement

I've already run my interpreter on some existing programs, such as one that
prints the famous Mandelbrot set to the terminal  (for best results, shrink
your terminal font down as much as possible.) 

I notice that, for some programs
(e.g. the Mandelbrot one, as well as one that computes a list of prime numbers
less than or equal to a given number), the program runs a bit slow; I suspect
that the equivalent program written in C would run much faster.

### Other Thoughts
A key realization in writing this: You reach a point when you stop thinking about
writing a program you're compiling and getting to work (the interpreter), and start
crafting the source code of an _interpreted language_ as input for your interpreter.
(In the beginning, I would, on impulse, try to recompile the interpreter after editing 
a BF source file; at that point, I realized I just needed to edit the interpreted
source, and then thought that was cool :))
