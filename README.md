OrcaMento
=========

OrcaMento is a small program to manage finances. Mine in particular, but some 
might find useful too.

It is based on budgets, a closed time span generally sequential. It is supposed 
to be the time span between your salary. Each budget should be filled with 
Estimates that is credits you hope to receive and debits you plan to pay. These
can be divided in categories to better organize.

After you plan enough and the given month has come, you want execute the 
budget. When you put it in execution you can add executions (movement) to your
estimates, and you will see the difference between the estimated and the 
accounted values.

But this execution is not from itself, but relative to an Wallet: An wallet is
your pocket, your purse, your banking account, or any other place where you 
hold money. Each execution is done on an wallet and you can execute the same
estimate many times, so each one can be in a different wallet.

Features
--------

- Multiple wallets;
- Monthly budgets;
- Safe storage (we use sqlite3 under the hood, so your data will be mostly ok. 
	Do regular backup, however)
- Free and visible format (again it's sqlite3, there are many programs out 
	there able to see and export your info, in case you give up this program or
	I give up it's development).
- Cross platform-ish. It is developed using wxWidgets and sqlite3 (Using 
	SQLiteCpp as a c++11 layer). I use mingw32 on windows, it should be super 
	easy to port to Linux or Mac now.
- For developers thinking about working on contributing, I am using c++11 
	features and even some c++14 that gcc supports, so the code is actual and
	should not be difficult pick up. Some messy code was made to enable the
	quick release of v0.1, but I intend to clean it until v0.2.

Limitations
-----------

- For now it is fixed to monthly budgets because it the way we are paid in my 
	country, but the file format is flexible enough for very different time 
	spans. The interface really isn't, so I do not intend to fix it now.
- When you walk away from the happy path (the correct way) the interface does
	not handle errors in an friendly way, but instead just show the sqlite 
	error message and revert the operation. It is robust as you can continue
	working without restart the program but I know it is really bad UX and I
	will punish myself in honour to front-end gods.
- Lack of a explicit save feature. All your changes are saved automatically
	(and, in general, immediately) and the user have no feedback or control.
	I plan to solve this ASAP as it may scare people.
	
Goals
-----
TODO

Dependencies
------------
1. WxWidgets 3.0.x;
2. sqlite3;
3. SQLiteCpp.

To finish.

Licence issues
--------------
TODO
