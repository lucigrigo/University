/Test [1-9]0*/ {printf "%s %d:\t%d\n", $1, $2, ($3 == "PASSED") ? 100 : 0 }
/TIMEOUT/
/Your code has been rated at/
