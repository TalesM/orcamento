# How to contribute
==================
A quick guideline (If this project ever become popular I swear I will re-write it more properly)

## Starting
------------
1. Choose an issue;
2. checkout locally;
3. Develop it.

##Testing
---------
During development you probably should focus on testing the code related to the issue. But before you submit, 
you should do the complete testing, to be as follow, in any order:

- Compile and execute the controller-test target;
- Compile and execute the presenter-test target;
- Compile and execute the standalone target (In codelite project, it can be either "Debug" or "Release").

If any fail, you should debug, fix and redo the tests. If fixing is impossible, you should follow these steps:

1. Create a new issue with the problem and all the info you can retrieve;
2. Put a comment before the offending Test Case/Scenario pointing to the issue number;
3. Put the tag [!mayfail] on that offending Test Case/Scenario.
4. If it was a new Test Case and the entire test is compromised, you can hide it ("[.]" or "[!hide]")

## Submitting
-------------
1. Execute the entire Testing procedure.
2. If you used the CodeLite IDE, make sure you cleared the target parameters and selected the debug branch 
  (commit it if necessary);
3. Rebase your work, so it has only one revision per push/pull request;
4. Make sure the submitted commit message has the task number preceded by '#' (Eg #39).
5. If you are not the author (me), then submit your pull-request.
