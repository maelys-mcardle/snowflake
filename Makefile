BASE_CFLAGS=-Wall -Werror -Wextra -lm
RELEASE_FLAGS=-O3
DEBUG_FLAGS=-g
CFLAGS=$(BASE_CFLAGS)

all: release

release: CFLAGS=$(BASE_CFLAGS) $(RELEASE_FLAGS)
release: snowflake

debug: CFLAGS=$(BASE_CFLAGS) $(DEBUG_FLAGS)
debug: snowflake

snowflake: main.o parse_file.o instructions.o program.o type_conversion.o \
		output_devices.o parse_instruction.o print_program.o run_program.o bank.o \
		run_instruction_types.o run_instruction_basic.o input_devices.o \
		string.o parameters.o instruction_info.o run_instruction_branching.o \
		run_instruction_math.o run_instruction_logic.o run_instruction_array.o \
		logging.o array.o
	cc -o snowflake main.o parse_file.o instructions.o program.o type_conversion.o \
		output_devices.o parse_instruction.o print_program.o run_program.o bank.o \
		run_instruction_types.o run_instruction_basic.o input_devices.o \
		string.o parameters.o instruction_info.o run_instruction_branching.o \
		run_instruction_math.o run_instruction_logic.o run_instruction_array.o \
		logging.o array.o $(CFLAGS)

main.o: src/cli/main.c src/cli/headers/main.h
	cc -c src/cli/main.c $(CFLAGS)

parse_file.o: src/cli/parse_file.c src/cli/headers/parse_file.h
	cc -c src/cli/parse_file.c $(CFLAGS)

print_program.o: src/cli/print_program.c src/cli/headers/print_program.h 
	cc -c src/cli/print_program.c $(CFLAGS)

parse_instruction.o: src/core/parse_instruction.c src/core/headers/parse_instruction.h
	cc -c src/core/parse_instruction.c $(CFLAGS)

program.o: src/core/program.c src/core/headers/program.h 
	cc -c src/core/program.c $(CFLAGS)

bank.o: src/core/bank.c src/core/headers/bank.h 
	cc -c src/core/bank.c $(CFLAGS)

run_program.o: src/core/run_program.c src/core/headers/run_program.h 
	cc -c src/core/run_program.c $(CFLAGS)

run_instruction_array.o: src/core/run_instruction_array.c src/core/headers/run_instruction_array.h 
	cc -c src/core/run_instruction_array.c $(CFLAGS)

run_instruction_basic.o: src/core/run_instruction_basic.c src/core/headers/run_instruction_basic.h 
	cc -c src/core/run_instruction_basic.c $(CFLAGS)

run_instruction_branching.o: src/core/run_instruction_branching.c src/core/headers/run_instruction_branching.h 
	cc -c src/core/run_instruction_branching.c $(CFLAGS)

run_instruction_logic.o: src/core/run_instruction_logic.c src/core/headers/run_instruction_logic.h 
	cc -c src/core/run_instruction_logic.c $(CFLAGS)

run_instruction_math.o: src/core/run_instruction_math.c src/core/headers/run_instruction_math.h 
	cc -c src/core/run_instruction_math.c $(CFLAGS)

run_instruction_types.o: src/core/run_instruction_types.c src/core/headers/run_instruction_types.h 
	cc -c src/core/run_instruction_types.c $(CFLAGS)

instructions.o: src/core/instructions.c src/core/headers/instructions.h
	cc -c src/core/instructions.c $(CFLAGS)

instruction_info.o: src/core/instruction_info.c src/core/headers/instruction_info.h
	cc -c src/core/instruction_info.c $(CFLAGS)

logging.o: src/core/platforms/linux/logging.c src/core/headers/logging.h
	cc -c src/core/platforms/linux/logging.c $(CFLAGS)

output_devices.o: src/core/platforms/linux/output_devices.c src/core/headers/output_devices.h
	cc -c src/core/platforms/linux/output_devices.c $(CFLAGS)

input_devices.o: src/core/platforms/linux/input_devices.c src/core/headers/input_devices.h
	cc -c src/core/platforms/linux/input_devices.c $(CFLAGS)

string.o: src/core/string.c src/core/headers/string.h
	cc -c src/core/string.c $(CFLAGS)

parameters.o: src/core/parameters.c src/core/headers/parameters.h
	cc -c src/core/parameters.c $(CFLAGS)

type_conversion.o: src/core/type_conversion.c src/core/headers/type_conversion.h
	cc -c src/core/type_conversion.c $(CFLAGS)

array.o: src/core/array.c src/core/headers/array.h
	cc -c src/core/array.c $(CFLAGS)

clean:
	rm snowflake main.o parse_file.o instructions.o program.o type_conversion.o \
		output_devices.o parse_instruction.o print_program.o run_program.o bank.o \
		run_instruction_types.o run_instruction_basic.o input_devices.o \
		string.o parameters.o instruction_info.o run_instruction_branching.o \
		run_instruction_math.o run_instruction_logic.o run_instruction_array.o \
		logging.o array.o