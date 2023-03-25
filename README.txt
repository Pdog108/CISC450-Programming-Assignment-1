Patrick Harris -- CISC450 Programming Assignment 1

List of Relevant Files:
    1. server.c
    2. client.c
    3. README.txt
    4. Makefile
    5. recv.txt
    6. send.txt

Compilation instructions:

make all: This command will creates both the client and server to run

make clean removes all files including a file called recv.txt because it created each time by the client server so we delete it each time to have a clean state

make client: This will create only the client that will be run

make server: This will create only the server to be run



Configuration file(s):
These are the files that are created when make all is run:
    ./server
    ./client


Running instructions: 
    1. To run the files, the first thing you need to do is have two terminals open at the same time, (in VS Code, there is an option for split terminal).
    2. Once you do this, to run the respected files, you do ./client for the client to run and ./server for the server to run.
    3. It is important to note that you must run ./server first before ./client so that the can look for a connection in order to receive the data.
    4. If all of this works, you should also see a new file called recv.txt which is an exact replica of the send.txt file.