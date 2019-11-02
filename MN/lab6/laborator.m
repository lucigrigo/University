# laborator 6
# metode bisectiei
x = met_bisect(-1,3,0.001,@sin);
printf("1. Solutia prin metoda bisesctiei este %.15f\n", x);
# metoda tangentei
x = met_tangent(-1,2,0.001,@sin,@cos);
printf("2. Solutia prin metoda tangentei este %.15f\n", x);