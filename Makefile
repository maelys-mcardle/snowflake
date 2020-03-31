BASE_CFLAGS=-Wall -Werror -Wextra -lm -Isrc/core/headers
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
		string.o parameters.o run_instruction_branching.o \
		run_instruction_math.o run_instruction_logic.o run_instruction_array.o \
		logging.o array.o
	cc -o snowflake main.o parse_file.o instructions.o program.o type_conversion.o \
		output_devices.o parse_instruction.o print_program.o run_program.o bank.o \
		run_instruction_types.o run_instruction_basic.o input_devices.o \
		string.o parameters.o run_instruction_branching.o \
		run_instruction_math.o run_instruction_logic.o run_instruction_array.o \
		logging.o array.o $(CFLAGS)

main.o: src/cli/main.c src/cli/headers/main.h
	cc -c src/cli/main.c $(CFLAGS)

parse_file.o: src/core/parse_file.c src/core/headers/parse_file.h
	cc -c src/core/parse_file.c $(CFLAGS)

print_program.o: src/core/print_program.c src/core/headers/print_program.h 
	cc -c src/core/print_program.c $(CFLAGS)

parse_instruction.o: src/core/parse_instruction.c src/core/headers/parse_instruction.h
	cc -c src/core/parse_instruction.c $(CFLAGS)

program.o: src/core/structures/program.c src/core/headers/structures/program.h 
	cc -c src/core/structures/program.c $(CFLAGS)

bank.o: src/core/structures/bank.c src/core/headers/structures/bank.h 
	cc -c src/core/structures/bank.c $(CFLAGS)

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

instructions.o: src/core/structures/instructions.c src/core/headers/structures/instructions.h
	cc -c src/core/structures/instructions.c $(CFLAGS)

logging.o: src/core/platforms/linux/logging.c src/core/headers/platforms/logging.h
	cc -c src/core/platforms/linux/logging.c $(CFLAGS)

output_devices.o: src/core/platforms/linux/output_devices.c src/core/headers/platforms/output_devices.h
	cc -c src/core/platforms/linux/output_devices.c $(CFLAGS)

input_devices.o: src/core/platforms/linux/input_devices.c src/core/headers/platforms/input_devices.h
	cc -c src/core/platforms/linux/input_devices.c $(CFLAGS)

string.o: src/core/structures/string.c src/core/headers/structures/string.h
	cc -c src/core/structures/string.c $(CFLAGS)

parameters.o: src/core/structures/parameters.c src/core/headers/structures/parameters.h
	cc -c src/core/structures/parameters.c $(CFLAGS)

type_conversion.o: src/core/structures/type_conversion.c src/core/headers/structures/type_conversion.h
	cc -c src/core/structures/type_conversion.c $(CFLAGS)

array.o: src/core/structures/array.c src/core/headers/structures/array.h
	cc -c src/core/structures/array.c $(CFLAGS)

clean:
	rm snowflake main.o parse_file.o instructions.o program.o type_conversion.o \
		output_devices.o parse_instruction.o print_program.o run_program.o bank.o \
		run_instruction_types.o run_instruction_basic.o input_devices.o \
		string.o parameters.o run_instruction_branching.o \
		run_instruction_math.o run_instruction_logic.o run_instruction_array.o \
		logging.o array.o