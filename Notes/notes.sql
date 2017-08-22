# inserting a row in to a table
insert into table_name (col1, col2, col3) VALUES (col1_val, col2_val, col3_val);





#--------------------------------------SQL Questions------------------------------------------------
1. (5 points) Which of the following statement about ADO is incorrect?
   (A) ADO stands for Active Data Objects.
   (B) With ADO you can access and manipulate data in a database.
   (C) You can move data from a server to a client, manipulate the data, and return updates to the server, with ADOs Remote Data Service (RDS).
   (D) ADO and RDS are automatically installed with Microsoft IIS.
Ans.: A

2. (5 points) ADO is
   (A) a Microsoft technology
   (B) a Microsoft Active-X component 
   (C) a programming interface to access data in a database 
   (D) All of the above
Ans.: D

3. (5 points) Which of the following step is NOT needed to create an ODBC connection?
   (A) set conn=Server.CreateObject("ADODB.Connection")
   (B) conn.Provider="Microsoft.Jet.OLEDB.4.0"
   (C) conn.Open "northwind"
   (D) None of the above.
Ans.: B

4. (5 points) Which of the following statement is NOT true?
   (A) The easiest way to connect to a database is to use a DSN-less connection.
   (B) A DSN-less connection can be used against any database on your web site.
   (C) With an ODBC connection, you can connect to any database, on any computer in your network, as long as an ODBC connection is available.
   (D) The ADO Connection object is used to create an open connection to a data source.
Ans.: B

5. (5 points) A recordset, once created, is opened directly from
   (A) an ADO object
   (B) an ODBC object
   (C) a DSN object
   (D) an ADO connection object
Ans.: D

6. (5 points) If a recordset 'rs' has a row of data with values 'Alice' and '80' for fields 'Name' and 'Grade', respectively, which of the following output is the result of the script: "for each x in rs.fields, response.write(x.name & "<br>"), next"? (Note: Symbol ',' respresents a line break.)
   (A) Name, Grade
   (B) Alice, 80
   (C) Name, Alice
   (D) "Grade, 80"
Ans.: A

7. (5 points) What does SQL stand for?
   (A) Strong Question Language
   (B) Structured Query Language
   (C) Structured Question Line
   (D) None of the above.
Ans.: B

8. (5 points) With SQL, how do you select the column named "FirstName" from a table named "Persons" ?
   (A) SELECT FirstName FROM Persons
   (B) EXTRACT FirstName FROM Persons
   (C) SELECT Persons,FirstName
   (D) None of the above.
Ans.: A

9. (5 points) With SQL, how do you select all the columns from a table named "Persons" ?
   (A) SELECT [all] FROM PERSONS
   (B) SELECT * FROM Persons
   (C) SELECT *.Persons
   (D) SELECT Persons
Ans.: B

10. (5 points) With SQL, how do you select all the records from a table named "Persons" where the "FirstName" is "Peter" ?
   (A) SELECT * FROM Persons LIKE 'Peter'
   (B) SELECT * FROM Persons WHERE FirstName='Peter'
   (C) SELECT [all] FROM Persons LIKE FirstName:'Peter'
   (D) SELECT * FROM Persons WHERE FirstName:'Peter'
Ans.: B

11. (5 points) With SQL, how do you select all the records from a table named "Persons" where the "FirstName" starts with an "a" ?
   (A) SELECT * FROM Persons LIKE FirstName='%a'
   (B) SELECT * FROM Persons WHERE FirstName LIKE '%a'
   (C) SELECT * FROM Persons WHERE FirstName='a'
   (D) SELECT * FROM Persons WHERE FirstName LIKE 'a%'
Ans.: D

12. (5 points) With SQL, how do you select all the records from a table named "Persons" where the "FirstName" is "Peter" and the "LastName" is "Jackson" ?
   (A) SELECT FirstName='Peter' LastName='Jackson' FROM Persons
   (B) You can not do that with SQL
   (C) SELECT * FROM Persons WHERE FirstName='Peter' AND LastName='Jackson'
   (D) None of the above.
Ans.: C

13. (5 points) With SQL, how do you select all the records where the "LastName" is alphabetically between (and including) "Hansen" and "Pettersen" ?
   (A) SELECT * FROM customers WHERE LastName>'Hansen' AND LastName>'Pettersen'
   (B) SELECT * FROM Persons WHERE LastName BETWEEN 'Hansen' AND 'Pettersen'
   (C) SELECT LastName>'Hansen' AND LastName<'Pettersen' FROM Persons
   (D) "SELECT * FROM Persons WHERE LastName>'Hansen', LastName<'Pettersen'"
Ans.: B

14. (5 points) Which SQL keyword is used to return only different values?
   (A) NOSAME
   (B) SC
   (C) COUNT
   (D) DISTINCT
Ans.: D

15. (5 points) Which SQL keyword is used to sort the result?
   (A) SORT
   (B) ORDER BY
   (C) ORDER
   (D) SORT-ORDER
Ans.: B

16. (5 points) With SQL, how can you return all the records from a table named "Persons" sorted REVERSE alphabetically by "FirstName" ?
   (A) SELECT * FROM Persons WHERE FirstName ORDER BY FirstName DESC
   (B) SELECT * FROM Persons ORDER BY -'FirstName'
   (C) SELECT * FROM Persons ORDER BY FirstName DESC
   (D) SELECT * FROM Persons SORT REVERSE 'FirstName'
Ans.: C

17. (5 points) With SQL, how can you insert a new record into the "Persons" table?
   (A) INSERT ('Jimmy', 'Jackson') INTO Persons
   (B) INSERT VALUES ('Jimmy', 'Jackson') INTO Persons
   (C) INSERT INTO Persons VALUES ('Jimmy', 'Jackson')
   (D) None of the above.
Ans.: C

18. (5 points) With SQL, how can you insert "Olsen" as the "LastName" in the "Persons" table?
   (A) INSERT INTO Persons (LastName) VALUES ('Olsen')
   (B) INSERT INTO Persons ('Olsen') INTO LastName
   (C) INSERT ('Olsen') INTO (LastName) FROM Persons
   (D) None of the above.
Ans.: A

19. (5 points) How can you change "Hansen" into "Nilsen" in the "LastName" column in the Persons Table?
   (A) SAVE Persons SET LastName = 'Nilsen' WHERE LastName = 'Hansen'
   (B) SAVE Persons SET LastName = 'Hansen' INTO LastName = 'Nilsen'
   (C) UPDATE Persons SET LastName = 'Hansen' INTO LastName = 'Nilsen'
   (D) UPDATE Persons SET LastName = 'Nilsen' WHERE LastName = 'Hansen'
Ans.: D

20. (5 points) With SQL, how can you delete the records where the "FirstName" is "Peter" in the Persons Table?
   (A) DELETE FROM Persons WHERE FirstName = 'Peter'
   (B) DELETE FirstName='Peter' FROM Persons
   (C) DELETE ROW FirstName='Peter' FROM Persons
   (D) None of the above.
Ans.: A
