all		:	lang

y.tab.h y.tab.c :	src/lang.y
			@bison -v -y  -d  src/lang.y
			@mv y.tab.h src/
			@mv y.tab.c src/
			@mv y.output src/
lex.yy.c	:	src/lang.l y.tab.h
			@flex src/lang.l
			@mv lex.yy.c src/

lang		:	lex.yy.c y.tab.c src/Table_des_symboles.c src/Table_des_chaines.c src/Attribute.c
			@gcc -std=gnu99 -o myc src/lex.yy.c src/y.tab.c src/Attribute.c src/Table_des_symboles.c src/Table_des_chaines.c

compil: lang
			@./myc < test/test.myC

exec: test/test.c test/test.h
			gcc -std=c99 -o test_exec test/test.c
			mv test_exec test/test
			./test/test

clean		:
			rm -f 	src/lex.yy.c src/*.o src/y.tab.h src/y.tab.c myc src/*~ src/y.output test/test.c test/test.h test/test
