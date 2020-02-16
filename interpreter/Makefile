snowflake: snowflake.o load_program.o instructions.o
	cc -o snowflake snowflake.o load_program.o instructions.o

snowflake.o: snowflake.c snowflake.h
	cc -c snowflake.c

load_program.o: load_program.c load_program.h
	cc -c load_program.c

instructions.o: instructions.c instructions.h
	cc -c instructions.c

clean:
	rm snowflake snowflake.o load_program.o instructions.o