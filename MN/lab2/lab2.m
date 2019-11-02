printf("\n=== Cerinta 1 ===\n");
#prob1
[L, U] = factCrout();
printf("\n   Factorizarea Crout:\n\n\tMatricea L\n");
disp(L)
printf("\n\tMatricea U\n");
disp(U)

printf("\n\n=== Cerinta 2 ===\n");
#prob2
[L, U] = factDoolittle();
printf("\n   Factorizarea Doolittle:\n\n\tMatricea L\n");
disp(L)
printf("\n\tMatricea U\n");
disp(U)

printf("\n=== Cerinta 3 ===\n");
#prob3
printf("-----------------\n");

printf("\n=== Cerinta 4 ===\n");
#prob4
makePart();
