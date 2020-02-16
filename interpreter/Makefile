snowflake: main.o parse_snowflake_file.o instructions.o
	cc -o snowflake main.o parse_snowflake_file.o instructions.o

snowflake.o: snowflake.c headers/snowflake.h
	cc -c snowflake.c

parse_snowflake_file.o: parse_snowflake_file.c headers/parse_snowflake_file.h
	cc -c parse_snowflake_file.c

instructions.o: instructions.c headers/instructions.h
	cc -c instructions.c

clean:
	rm snowflake main.o parse_snowflake_file.o instructions.o