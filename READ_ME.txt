Cheaters Program
Written by: Justin Swinney (jps3869) & Victor Yip (vsy59)

Objective: The program is designed to compare multiple text files and point out the ones that are likely to be plagiarized. 

Included files:
cheaters.cpp
cheaters.h
makefile
READ_ME.txt

How to run program:
1) unzip files
2) enter command: make
3) run program command (example): ./plagiarismCatcher /home/ecelrc/guest/vyip/EE312/HW/HW08/med_doc_s
et/ 6 200

program arguments:
0: program name: plagarismCatcher
1: full path of where text fiels are located
2: a positive integer number of words per chunk. 
	Each chunk of words is compared. 
	A smaller number is more sensitive to similarities but will increase false positives.
3: a positive integer number of how many chunk matches
	you want to consider possibly plagiarism.

Notes: 
It is very important to type the full path to the location where your text files are.

ONLY ANSI TEXT FILES WILL WORK WITH THIS PROGRAM!!!