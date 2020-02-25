snowflake: main.o parse_file.o instructions.o program.o type_conversion.o \
		output.o parse_line.o print_program.o run_program.o bank.o \
		run_instruction_types.o
	cc -o snowflake main.o parse_file.o instructions.o program.o type_conversion.o \
		output.o parse_line.o print_program.o run_program.o bank.o \
		run_instruction_types.o

main.o: src/main.c src/headers/main.h
	cc -c src/main.c
	
snowflake.o: src/snowflake.c src/headers/snowflake.h
	cc -c src/snowflake.c

parse_file.o: src/parse_file.c src/headers/parse_file.h
	cc -c src/parse_file.c

parse_line.o: src/parse_line.c src/headers/parse_line.h
	cc -c src/parse_line.c

program.o: src/program.c src/headers/program.h 
	cc -c src/program.c

bank.o: src/bank.c src/headers/bank.h 
	cc -c src/bank.c

print_program.o: src/print_program.c src/headers/print_program.h 
	cc -c src/print_program.c

run_program.o: src/run_program.c src/headers/run_program.h 
	cc -c src/run_program.c

run_instruction_types.o: src/run_instruction_types.c src/headers/run_instruction_types.h 
	cc -c src/run_instruction_types.c

instructions.o: src/instructions.c src/headers/instructions.h
	cc -c src/instructions.c

output.o: src/output.c src/headers/output.h
	cc -c src/output.c

type_conversion.o: src/type_conversion.c src/headers/type_conversion.h
	cc -c src/type_conversion.c

clean:
	rm snowflake main.o parse_file.o instructions.o program.o type_conversion.o \
		output.o parse_line.o print_program.o run_program.o bank.o \
		run_instruction_types.o