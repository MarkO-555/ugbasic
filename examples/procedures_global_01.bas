   GLOBAL a, b
   
   a = 6
   b = 9
   
   PROCEDURE test1
      a = a + 1
      b = b + 1
   END PROC
   
   PROCEDURE test2
      a = a + b
      b = b + a
   END PROC

   test1
   test2
   
   PRINT a;" ";: REM print 17
   PRINT b;" ";: REM print 27

   HALT