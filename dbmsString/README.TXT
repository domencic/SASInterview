This file is for the first question.
Different data base engines have different definitions for string manipulation functions such as getting a substring for example. 
Supposing that DBMS1 uses substr, DBMS2 uses substring, and DBMS3 uses sbstr, can you write a function using C that would take a query 
and the DBMS as a parameter and rebuild the query using the adequate function for that particular engine?

For this exercise, I made the assumption that the 3 substrings listed (substr,substring,sbstr) would be the only possible values for substrings.
I expected values could come in any of the above formats.

The source code is uploaded to src directory.

dbmsString.out is the output from running test cases.

