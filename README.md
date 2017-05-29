# Getting the expected results:

## Script to run the test cases:

```sh
#!/bin/sh
mkdir results 2>/dev/null;
clang main.c -o results/a.out
cd results

echo 'write "aaabcdefghij" seek 0 write "##"'
./a.out write "aaabcdefghij" seek 0 write "##"

echo 'open novo write "aaabcdefghij" seek 0 write "##" close'
./a.out open novo write "aaabcdefghij" seek 0 write "##" close
stat novo
readlink novo

echo 'open novo1 write "aaabcdefghij" seek 100 write "##" close'
./a.out open novo1 write "aaabcdefghij" seek 100 write "##" close
stat novo1
readlink novo1

echo 'open novo2 write "aaabcdefghij" seek 100000 write "##" seek "100001" write "@@@@@"'
./a.out open novo2 write "aaabcdefghij" seek 100000 write "##" seek "100001" write "@@@@@"
stat novo2
readlink novo2

echo 'open novo2 seek 50000 read 2 seek 100003 write 2'
./a.out open novo2 seek 50000 read 2 seek 100003 write 2
stat novo2
readlink novo2

ls -l
```

## Script output:

```
# ./assignment.sh
write "aaabcdefghij" seek 0 write "##"
Invalid file descriptor
open novo write "aaabcdefghij" seek 0 write "##" close
896 48 -rwxrwxrwx 1 root operator 0 12 "May 29 12:03:43 2017" "May 29 12:03:43 2017" "May 29 12:03:43 2017" "Jan  1 00:00:00 1970" 4096 8 0 novo
open novo1 write "aaabcdefghij" seek 100 write "##" close
896 50 -rwxrwxrwx 1 root operator 0 102 "May 29 12:03:43 2017" "May 29 12:03:43 2017" "May 29 12:03:43 2017" "Jan  1 00:00:00 1970" 4096 8 0 novo1
open novo2 write "aaabcdefghij" seek 100000 write "##" seek "100001" write "@@@@@"
You forgot to close the file so I am closing for you
896 60 -rwxrwxrwx 1 root operator 0 100006 "May 29 12:03:43 2017" "May 29 12:03:43 2017" "May 29 12:03:43 2017" "Jan  1 00:00:00 1970" 4096 208 0 novo2
open novo2 seek 50000 read 2 seek 100003 write 2
You forgot to close the file so I am closing for you
896 60 -rwxrwxrwx 1 root operator 0 100006 "May 29 12:03:43 2017" "May 29 12:03:43 2017" "May 29 12:03:43 2017" "Jan  1 00:00:00 1970" 4096 208 0 novo2
total 248
-rwxr-xr-x  1 root  operator    9670 May 29 12:03 a.out
-rwxrwxrwx  1 root  operator      12 May 29 12:03 novo
-rwxrwxrwx  1 root  operator     102 May 29 12:03 novo1
-rwxrwxrwx  1 root  operator  100006 May 29 12:03 novo2
```

# Discussion/Closing comments:

* First test case: did not do anything since the file wasn't open in first place.  
* Second test case: it appended the new characters to the text, within a gap of (100-12) bytes between them.  
* Third test case: firstly it appended '##' to the text, within a gap of (100000-12) bytes between them. Then it overwrited the last character, appending "@@@@@". Also the file was automatically closed by the program design.  
* Fourth test case: It read two "^@" characters between the text and overwrote some of the last characters with that.

## Contents of novo1 file (as represented on Vim):

```
aaabcdefghij^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@##
```

