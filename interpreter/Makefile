snowflake: main.o parse_snowflake_file.o instructions.o program.o errors.o
	cc -o snowflake main.o parse_snowflake_file.o instructions.o program.o errors.o

snowflake.o: snowflake.c headers/snowflake.h
	cc -c snowflake.c

parse_snowflake_file.o: parse_snowflake_file.c headers/parse_snowflake_file.h
	cc -c parse_snowflake_file.c

program.o: program.c headers/program.h 
	cc -c program.c

instructions.o: instructions.c headers/instructions.h
	cc -c instructions.c

errors.o: errors.c headers/errors.h
	cc -c errors.c

clean:
	rm snowflake main.o parse_snowflake_file.o instructions.o program.o errors.o