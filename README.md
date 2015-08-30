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
- Safe storage (we use [sqlite3][SQLite] under the hood, so your data will be mostly ok. 
	Do regular backup, however)
- Free and visible format (again it's [sqlite3][SQLite], there are many programs out 
	there able to see and export your info, in case you give up this program or
	I give up it's development).
- Cross platform-ish. It is developed using [wxWidgets][] and [sqlite3][SQLite] (Using 
	[SQLiteC++][] as a c++11 layer). I use mingw32 on windows, it should be super 
	easy to port to Linux or Mac now.
- For developers thinking about working on contributing, I am using [c++11][] 
	features and even some [c++14][] that [gcc 4.9.2][gcc492] supports, so the code is actual and
	should not be difficult pick up.

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
- Lack of Analysis and Graphic views of you budget. It can export to you check
    on Excel or Calc, but it would be better to have some basic charts built in.
- Lack of interoperability. You can always view the database, but it is not documented
	and can be hard to understand. We do have a CSV export feature, but it is very
	limited.
	
Goals
-----
The goal for this app was create a easier budget management tool than my old
excel spreadsheet. On technical side, I wanted to get practice on [SQLite][]
databases, being [wxWidgets][] and C++11 and 14 more like bonus experience. 

Because of that I made it as personal need it may be a little too specific in 
some resources, as I do not have a general dataset to base my requirements. 
I probably can not even notice when it happens, but suggestions are welcome as
I want it to be more general. A token of my good faith is the app interface language, 
witch is English instead of Portuguese (my mother language) :)

Dependencies
------------
1. [wxWidgets 3.0.x][wxWidgets];
2. [SQLite 3][SQLite];
3. [SQLiteC++][].

It was compiled using [TDM-gcc](http://tdm-gcc.tdragon.net), [version 4.9.2](http://sourceforge.net/projects/tdm-gcc/files/TDM-GCC%20Installer/tdm-gcc-4.9.2.exe/download). 
It should be compilable in any port of [gcc 4.9.2][gcc492] or later.

Licence issues
--------------
I started this project using MIT license, but then I decided that GPL would
be more suited for it, as MIT sounds too library-y for me. So read the [license.TXT](https://github.com/TalesM/orcamento/blob/master/LICENSE.txt)
if you want to modify or use this as part of other app or library.

[SQLite]: http://sqlite.org/
[SQLiteC++]: http://srombauts.github.io/SQLiteCpp/ 
[wxWidgets]: http://wxwidgets.org/
[c++11]: https://gcc.gnu.org/projects/cxx0x.html
[c++14]: https://gcc.gnu.org/projects/cxx1y.html
[gcc492]: https://gcc.gnu.org/gcc-4.9/
