gcc -g -fprofile-arcs -ftest-coverage polygon.c pgtest.c && ./a.out && gcov -b polygon.c
#rm *.gcno *.gcda && gcc -g -fprofile-arcs -ftest-coverage polygon.c && ./a.out && gcov -b polygon.c
