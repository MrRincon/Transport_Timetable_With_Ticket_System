#Busy Bees Bus Timetable and ticket purchasing system.
###This program and instructions were made for windows OS cases. Please adjust where necessary for other operations systems.

##Prerequisites:
- Windows OS
- Linux OS
- GCC version 10 or above
- GNU Make 4.3 or above

##Installation instructions:
git clone https://CST2555-Coursework@dev.azure.com/CST2555-Coursework/TFL-Database/_git/TFL-Database
cd TFL-Database/src/
make testcase
make
 
##To run the test cases for the program:
Navigate to the src/ folder and run the command 'make testcase',
after this command, the compilation process will take place and a testcase.exe file will be created.
Now run the command './testcase.exe' to run the test cases.

##To run the Program:
Navigate to src/ folder and run the 'make' command,
after this command, the compilation process will take place and a main.exe file will be created.
Now run the command './main.exe' to run the program.

##Program instructions:
- After running the command to execute the program, the first prompt will ask you to enter the necessary files for the program to use. 
Please enter all .csv files the program requests and any additional ones.
Necessary files required for the program to run:
buses.csv, routes.csv, stops.csv.
Additional files the program can optionally use:
users.csv, tickets.csv

- The program will ask you to then login or register.
Please input your details to register or, use your given id number and password to login.

- Once into the system, please use the menu options to select the operation you wish to run.

Menu options include:
1. Find a route.
2. Show obtained tickets.
3. Show timetable at the bus stop.
9. Account settings.
0. Log-out.

All prompts and console outputs are structured to inform the user with as much detail as possible, 
allowing them to make informed decisions within the program.

- Once finished with the program, please use the option to log-out
On logout the .csv files will be re-written to, with the updated information, changed during runtime of the program.

- On completion of the use of the program please exit the system using the appropriate menu option.
This will cause the program to cease operation on the command line.

##Dataset Templates
Each dataset follows certain rules.
Attributes making up a class are all separated by ','. Attributes representing multiple values such as lists are separated by ';'. Attributes representing hashtables are represented in the following format Key>Value|Key>Value.
Each dataset has an id attribute which is an integer prepended with a character. Lacking this prepended character means the data when loaded will be unable to be sorted or searched through.
Below are the required prepended characters for each dataset type:
- BUS->B
- ROUTE->R
- STOPS->S
- TICKETS->T
- USERS->U

Empty attributes are represented by 'NULL'.
Times are stored in the following format 'MM/DD/YYYY:HH:MM:SS'
##CSV Template Examples:
- BUS: ID DRIVER CURRENT_LOCATION ROUTE_ASSIGNED CAPACITY DELAYED_STATUS
    - B1;Joe Schmoe;S1;R1;50;FALSE
- ROUTE: ID DIRECTION START_POINT END_POINT ORDERED_STOPS ASSIGNED_BUSES DISTANCE DIVERSION
    - R1,N,S1,S10;S1;S4;S9;S10,B1;B2;B3,2,2,TRUE
- STOPS: ID NAME XLOCATION YLOCATION ROUTE_ASSIGNED BUSSES_ASSIGNED
    - S1,St. Ann Way,25.5,6.125,R1;R2;R6;R8,B1>08:00;10:00|B2>12:00;13:00
- TICKETS: ID ASSIGNED_BUS START_LOCATION END_LOCATION ROUTE BUS_TIME VALID
    - T1,B1,S1,S10,R1,08/23/2024:10:00:00,TRUE
- USERS: FIRST_NAME LAST_NAME PASSWORD EMAIL UID BALANCE TICKETS
    - Janae,Summer,Froggy1,janae@summer.com,U0,0,T0;T1
##Report and video explanation location:
TFL-Database/Report_and_video/

##Design diagrams of the project:
TFL-Database/Initial Diagrams Design

##Contributors:
Alam Rincon M00774667, 
Charlie Dovey M00843428, 
Petar Atanasov M00916537, 
Artem Halis M00951627, 
Teon Morgan M00829986.