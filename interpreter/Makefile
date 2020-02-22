snowflake: main.o parse_snowflake_file.o instructions.o program.o output.o parse_snowflake_line.o print_program.o run_program.o
	cc -o snowflake main.o parse_snowflake_file.o instructions.o program.o output.o parse_snowflake_line.o print_program.o run_program.o

main.o: src/main.c src/headers/main.h
	cc -c src/main.c
	
snowflake.o: src/snowflake.c src/headers/snowflake.h
	cc -c src/snowflake.c

parse_snowflake_file.o: src/parse_snowflake_file.c src/headers/parse_snowflake_file.h
	cc -c src/parse_snowflake_file.c

parse_snowflake_line.o: src/parse_snowflake_line.c src/headers/parse_snowflake_line.h
	cc -c src/parse_snowflake_line.c

program.o: src/program.c src/headers/program.h 
	cc -c src/program.c

print_program.o: src/print_program.c src/headers/print_program.h 
	cc -c src/print_program.c

run_program.o: src/run_program.c src/headers/run_program.h 
	cc -c src/run_program.c

instructions.o: src/instructions.c src/headers/instructions.h
	cc -c src/instructions.c

output.o: src/output.c src/headers/output.h
	cc -c src/output.c

clean:
	rm snowflake main.o parse_snowflake_file.o instructions.o program.o output.o parse_snowflake_line.o print_program.o run_program.o