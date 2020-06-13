# Librere
Librere is a C Library I'm making on my own in order to learn and build things in the C programming language. It mainly achieves basic things, however it has some interesting code to look at and even use.
You can especially take a look to the OOP directory as I've built a kind of "LinkedList class" that can be really helpful for some people needing easy data management. I always try to provide a great documentation for each one of my "big" projects, thus you would not run into too many problems if you follow it carefully each time you want to use my code.

## Installation
You want to use `librere`? Amazing! Just follow **these steps** and you will be ready in a few minutes.

1. Clone this entire repository into an arbitrary location on your machine : it can be anything, as long as you've the rights on it and you can access it easily. You can clone using `git clone https://github.com/AurelleGit/LibRere` in the directory of your choice. 
2. Jump in the directory if you're not in, and simply run the `make` command in the terminal prompt. If command is not found, make sure you've installed `make`.
3. If everything has gone as intended, you must have an archive called `librere.a` which is the compiled library itself. 
4. Compile any of your C code using the library with the following command (I'm supposing the directory where you cloned was something called ~/lib but you need to replace it where your own path)

  

      `gcc -o executable *.c  -I~/lib/librere         -L~/lib/librere -lrere`

	`-I` indicates the location where the header needs to be found, `-L` is the same for the library and `-l` indicates the name of the lib (without the `lib` prefix).
Do not forget to include `libere.h` in your source files to avoid compilation warnings and get a better error handling.

## Conventions

Each function is prefixed with the `r_` prefix, excepting pseudo-classes created in the OOP/ directory. Files name are always wrote without the `r_` prefix. 
 
