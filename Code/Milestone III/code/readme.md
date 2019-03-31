# Milestone III

The purpose of Milestone III was to make a first attempt at creating a functioning Arduino library. Later in the course, I will be creating libraries to read various types of sensors.

This library implements the most basic flow sensor reading code from Milestone I.

A library primarily consists of two files:

(1) A header file (\*.h) that contains the names of public and private variables and functions.
(2) A class file (\*.cpp) that contains the actual code with the class functions.

Most of the code in the \*.cpp file looks very similar to that in a \*.ino file, and further, most of the code in the \*.h file is just boilerplate. One could essentially write a Python script to generate the \*.h file form the \*.cpp function. Its main purpose is to separate publically exposed functions.

I also created a keywords.txt file. This file causes the Arduino IDE to highlight kewords when you include the library in a project. It contains two different classes of keywords for classes and methods.
