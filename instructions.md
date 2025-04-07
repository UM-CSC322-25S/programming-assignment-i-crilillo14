

The Marina Manager of Nautical Ventures needs a simple program to track the various boats stored and being repaired at the marina, and the charges being levied on each:

Boats in slips - $12.50/foot/month
Boats on land for work - $14.00/foot/month
Boats on trailors - $25.00/foot/month
Boats in storage - $11.20/foot/month
The program must allow for up to 120 boats, and must hold the following information about each boat:
The name of the boat (up to 127 characters long, not containing a comma)
The length in feet - up to 100' (hint: choose a suitable data type)
Which type of place (slip/land/trailor/storage) (hint: use an enum like this)
Depending on the type, extra relevant information (use a union):
Slip - the slip number 1-85
Land - the bay letter, A-Z
Trailor - the trailor license tag
Storage - the storage space number 1-50
The amount of money owed to the marina
The data for each boat must be held in a malloced struct that is pointed to from an element of an array of 120 pointers, some of which might not be in use because the marina is not always full.
While the program is not running the data about the boats is stored in a Comma Separated Values file such as BoatData.csv. When the program starts it must load the data from the file whose name is provided as the command line argument, and when the program exits it must store the data back to that file.

Once the boat data is loaded the program must offer a menu of options:

Print the boat inventory, sorted alphabetically by boat name (hint: keep the array packed and sorted by boat name)
Add a boat by providing as a string that looks like one line of the .csv file
Remove a boat by name
Accept a payment for the boat, up to the amount owed
Update the amount owed because a new month has started
Exit
The program must be user friendly, but you can assume that the user will enter reasonable data values:
Menu options must be accepted in upper and lower case. The user might enter an invalid option, which results in an error message and is ignored.
Boat names must be accepted without regard for case.
Boat data in .csv format will be correctly formatted and within limits
Numeric input will be syntactically correct.
The user might enter a non-existent boat name for removal and payment, or an amount too large for payment, in which case the action is not completed.
Here's what a run should look like (with the keyboard input shown in italics) ...

geoff@johnston: BoatManagement BoatData.csv

Welcome to the Boat Management System
-------------------------------------

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : *Q*
Invalid option Q

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : i
Big Brother           20'    slip   # 27   Owes $1200.00
Magic                 38' trailor 7KZ099   Owes $   0.00
Moon Glow             30'    slip   # 13   Owes $ 500.00
Osita                 40'    land      C   Owes $1000.07
Run About             18' storage   # 13   Owes $ 200.50

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : A
Please enter the boat data in CSV format                 : Brooks,34,trailor,AAR666,99.00

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : I
Big Brother           20'    slip   # 27   Owes $1200.00
Brooks                34' trailor AAR666   Owes $  99.00
Magic                 38' trailor 7KZ099   Owes $   0.00
Moon Glow             30'    slip   # 13   Owes $ 500.00
Osita                 40'    land      C   Owes $1000.07
Run About             18' storage   # 13   Owes $ 200.50

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : r
Please enter the boat name                               : Lost Soul
No boat with that name

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : R
Please enter the boat name                               : MAGIC

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : i
Big Brother           20'    slip   # 27   Owes $1200.00
Brooks                34' trailor AAR666   Owes $  99.00
Moon Glow             30'    slip   # 13   Owes $ 500.00
Osita                 40'    land      C   Owes $1000.07
Run About             18' storage   # 13   Owes $ 200.50

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : P
Please enter the boat name                               : Broke Boater
No boat with that name

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : P
Please enter the boat name                               : Moon Glow
Please enter the amount to be paid                       : 2000
That is more than the amount owed, $500.00

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : P
Please enter the boat name                               : Moon Glow
Please enter the amount to be paid                       : 200

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : i
Big Brother           20'    slip   # 27   Owes $1200.00
Brooks                34' trailor AAR666   Owes $  99.00
Moon Glow             30'    slip   # 13   Owes $ 300.00
Osita                 40'    land      C   Owes $1000.07
Run About             18' storage   # 13   Owes $ 200.50

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : m

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : I
Big Brother           20'    slip   # 27   Owes $1450.00
Brooks                34' trailor AAR666   Owes $ 949.00
Moon Glow             30'    slip   # 13   Owes $ 675.00
Osita                 40'    land      C   Owes $1560.07
Run About             18' storage   # 13   Owes $ 402.10

(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : x

Exiting the Boat Management System
Here's what the saved .csv file could look like:
Big Brother,20,slip,27,1450.00
Brooks,34,trailor,AAR666,949.00
Moon Glow,30,slip,13,675.00
Osita,40,land,C,1560.07
Run About,18,storage,13,402.10
Your must submit your project on GitHub You may sit with the TA when (s)he runs your program in the lab session so you can see together how well it works.
Your project is worth 20% of the course grade. It will be assessed for functionality and programming style using this marking scheme. Please review the policies on assessment in the administration document.

