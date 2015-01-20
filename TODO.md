TODO
====

Contents
--------

TODO for V0.1
-------------

1. Show accounted collumn value correcly after closing Execution Dialog; _ok_
1. Forbid two estimates to have the same name and same budget_id. A name should 
	happen only once per budget;_ok_
1. Create some way to copy estimates for the following budgets. _ok_
1. <del>Create some way to import/export the budget as CSV.</del>
	<ins>If I really need to do this, I can use tooling over the database file.
2. Halt open or creating action if path invalid; _ok_
3. Show leftover on status bar; _ok_
4. Reopen last file on startup;
5. Write a nice readme.

Goals for V0.1
--------------

- Budget management (Budget Category postponed);
- Promise Category management;
- Promise management;
- Execution management;
- <del>Budget sequence result consistency enforcement and cycle prevention;</del> It is now nonsense. 
	Our Previous file format required it, but the perfect file format we have now made it unnecessary. 
- Table like view with ordering. May Leave it for the next version?

Goals for V0.2
--------------
- Use the DocumentView Framework.
- Better display of Totals. The status bar is problematic. We need copyable and
	filter-able (per wallet at least) totals;
- Filtering
- Ordering?


TODO for who knows...
- CHECK against change in fields estimate for table execution and budget for table estimate. 
- Some way do deactivate, delete budget for human error.
- Some way to delete wallet, execution, estimate for humar error too.
- Provide some save feature (which calls commit, obviously)