snowflake: main.o parse_snowflake_file.o instructions.o program.o output.o parse_snowflake_line.o print_program.o
	cc -o snowflake main.o parse_snowflake_file.o instructions.o program.o output.o parse_snowflake_line.o print_program.o

snowflake.o: snowflake.c headers/snowflake.h
	cc -c snowflake.c

parse_snowflake_file.o: parse_snowflake_file.c headers/parse_snowflake_file.h
	cc -c parse_snowflake_file.c

parse_snowflake_line.o: parse_snowflake_line.c headers/parse_snowflake_line.h
	cc -c parse_snowflake_line.c

program.o: program.c headers/program.h 
	cc -c program.c

print_program.o: print_program.c headers/print_program.h 
	cc -c print_program.c

instructions.o: instructions.c headers/instructions.h
	cc -c instructions.c

output.o: output.c headers/output.h
	cc -c output.c

clean:
	rm snowflake main.o parse_snowflake_file.o instructions.o program.o output.o parse_snowflake_line.o print_program.o