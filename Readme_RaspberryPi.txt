**This File should help you get the RFID software running and show you how to use it**

-this folder should go into the file path \home\pi

-to get to the pi directory, simply hit the file manager button directly to the right of the "start button"
 this should bring you directly to the place you need to be, to double check youre in the right place, look 
 up at the top of the file manager window and the file path will be listed there.

-paste all of these files insde a folder entitled "picode" you will have to create this new folder by simply 
 right clicking in any blank area of the file manager, hovering over "create new..." and select folder.

-once these files are in place the program should be ready to execute.

-for convenience put the text file the code will be written to also in the \home\pi file path

-to create the new text file open up the LXTermimal located on the desktop

-type in the command "touch unnamed.txt" the unnamed part can be changed to whatever you would like the file
 to be called

-you will now notice that next time you open the file manager a your text file will be in there

-to run the program, open up the LXTerminal again which is located on the desktop

-type "cd picode" this will change the directory of the console window you are in to the location of the program

-to run the program type "./rfid" immediately below this command the program will be begin running

-follow the onscreen prompts. when you are asked to input your file name, you will need to provide the full file
 path, it should read "/home/pi/yourfilename.txt" 

-if the file path is valid and a com port is opened the program will begin polling for fish and can be exited by
 hitting any key. upon hitting a key the com port will be closed, the file will be saved and the program will be exited

~*~NOTE~*~
for whatever reason, after running the program, the console window breaks, aka you wont be able to give it anymore
commands. to remmedy this, simply x out of the window and open a new LXterminal window.

~*Kyle Butler*~