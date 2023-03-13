# Jungle Board Game 鬥獸棋
This is a Jungle Board Game I developed as a part of CSCI1120 course I took.

## Main features
This program is inspired by an existing board game Dou Shou Qi (鬥獸棋). It allows 3 modes of gameplay including mode 1 - Human vs Human | mode 2 - Human vs Machine | mode 3 - Machine vs Machine. To make a move, type a command in the following form: `<starting grid> <destination grid>`, e.g., `a7 a6`

## How to run
Download all the source files and add them into a C++ project using tools like VS Code or CodeBlocks to run the program and generate a `.exe` file. Then, use the command line to run:
```
<file_name>.exe boardset.txt
```
where `boardset.txt` is an optional parameter, where you can pass the text file to set initial game set-up. Example of such is `boardsample.txt`. Then, you will be asked to choose the gamemode and begin the game.

## Technologies
This program uses pure **C++ OOP** running across 33 source and header files.

## Credits
The teaching staff of this course has provided certain C++ and header files to help students handle topics not relating to OOP, e.g., `fileman.cpp` that is for handling File I/O, as well as the board sample text files. Also, in some files, there contain pre-existing function where students only have to complete To-do lists in them. Refer to the files and comments in them for more detail about the program.
