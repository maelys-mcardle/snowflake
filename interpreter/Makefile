snowflake: main.o parse_file.o instructions.o program.o type_conversion.o \
		output.o parse_instruction.o print_program.o run_program.o bank.o \
		run_instruction_types.o run_instruction_basic.o devices.o
	cc -o snowflake main.o parse_file.o instructions.o program.o type_conversion.o \
		output.o parse_instruction.o print_program.o run_program.o bank.o \
		run_instruction_types.o run_instruction_basic.o devices.o

main.o: src/cli/main.c src/cli/headers/main.h
	cc -c src/cli/main.c

parse_file.o: src/cli/parse_file.c src/cli/headers/parse_file.h
	cc -c src/cli/parse_file.c

print_program.o: src/cli/print_program.c src/cli/headers/print_program.h 
	cc -c src/cli/print_program.c

parse_instruction.o: src/core/parse_instruction.c src/core/headers/parse_instruction.h
	cc -c src/core/parse_instruction.c

program.o: src/core/program.c src/core/headers/program.h 
	cc -c src/core/program.c

bank.o: src/core/bank.c src/core/headers/bank.h 
	cc -c src/core/bank.c

run_program.o: src/core/run_program.c src/core/headers/run_program.h 
	cc -c src/core/run_program.c

run_instruction_basic.o: src/core/run_instruction_basic.c src/core/headers/run_instruction_basic.h 
	cc -c src/core/run_instruction_basic.c

run_instruction_types.o: src/core/run_instruction_types.c src/core/headers/run_instruction_types.h 
	cc -c src/core/run_instruction_types.c

instructions.o: src/core/instructions.c src/core/headers/instructions.h
	cc -c src/core/instructions.c

output.o: src/core/platforms/linux/output.c src/core/headers/output.h
	cc -c src/core/platforms/linux/output.c

devices.o: src/core/devices.c src/core/headers/devices.h
	cc -c src/core/devices.c

type_conversion.o: src/core/type_conversion.c src/core/headers/type_conversion.h
	cc -c src/core/type_conversion.c

clean:
	rm snowflake main.o parse_file.o instructions.o program.o type_conversion.o \
		output.o parse_instruction.o print_program.o run_program.o bank.o \
		run_instruction_types.o run_instruction_basic.o devices.o