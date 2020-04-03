BASE_CFLAGS=-Wall -Werror -Wextra -lm -Isrc/include
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
		logging.o array.o run_instruction_io.o bank_operations.o \
		print_instruction.o 
	cc -o snowflake main.o parse_file.o instructions.o program.o type_conversion.o \
		output_devices.o parse_instruction.o print_program.o run_program.o bank.o \
		run_instruction_types.o run_instruction_basic.o input_devices.o \
		string.o parameters.o run_instruction_branching.o \
		run_instruction_math.o run_instruction_logic.o run_instruction_array.o \
		logging.o array.o run_instruction_io.o bank_operations.o \
		print_instruction.o $(CFLAGS)

main.o: src/cli/main.c src/cli/main.h
	cc -c src/cli/main.c $(CFLAGS)

parse_file.o: src/interpreter/parse/parse_file.c src/include/parse/parse_file.h
	cc -c src/interpreter/parse/parse_file.c $(CFLAGS)

print_program.o: src/interpreter/print/print_program.c src/include/print/print_program.h 
	cc -c src/interpreter/print/print_program.c $(CFLAGS)

print_instruction.o: src/interpreter/print/print_instruction.c src/include/print/print_instruction.h 
	cc -c src/interpreter/print/print_instruction.c $(CFLAGS)

parse_instruction.o: src/interpreter/parse/parse_instruction.c src/include/parse/parse_instruction.h
	cc -c src/interpreter/parse/parse_instruction.c $(CFLAGS)

program.o: src/interpreter/core/program.c src/include/core/program.h 
	cc -c src/interpreter/core/program.c $(CFLAGS)

bank.o: src/interpreter/core/bank.c src/include/core/bank.h 
	cc -c src/interpreter/core/bank.c $(CFLAGS)

run_program.o: src/interpreter/run/run_program.c src/include/run/run_program.h 
	cc -c src/interpreter/run/run_program.c $(CFLAGS)

run_instruction_array.o: src/interpreter/run/run_instruction_array.c src/include/run/run_instruction_array.h 
	cc -c src/interpreter/run/run_instruction_array.c $(CFLAGS)

run_instruction_basic.o: src/interpreter/run/run_instruction_basic.c src/include/run/run_instruction_basic.h 
	cc -c src/interpreter/run/run_instruction_basic.c $(CFLAGS)

run_instruction_branching.o: src/interpreter/run/run_instruction_branching.c src/include/run/run_instruction_branching.h 
	cc -c src/interpreter/run/run_instruction_branching.c $(CFLAGS)

run_instruction_io.o: src/interpreter/run/run_instruction_io.c src/include/run/run_instruction_io.h 
	cc -c src/interpreter/run/run_instruction_io.c $(CFLAGS)

run_instruction_logic.o: src/interpreter/run/run_instruction_logic.c src/include/run/run_instruction_logic.h 
	cc -c src/interpreter/run/run_instruction_logic.c $(CFLAGS)

run_instruction_math.o: src/interpreter/run/run_instruction_math.c src/include/run/run_instruction_math.h 
	cc -c src/interpreter/run/run_instruction_math.c $(CFLAGS)

run_instruction_types.o: src/interpreter/run/run_instruction_types.c src/include/run/run_instruction_types.h 
	cc -c src/interpreter/run/run_instruction_types.c $(CFLAGS)

instructions.o: src/interpreter/core/instructions.c src/include/core/instructions.h
	cc -c src/interpreter/core/instructions.c $(CFLAGS)

logging.o: src/interpreter/platforms/linux/logging.c src/include/platforms/logging.h
	cc -c src/interpreter/platforms/linux/logging.c $(CFLAGS)

output_devices.o: src/interpreter/platforms/linux/output_devices.c src/include/platforms/output_devices.h
	cc -c src/interpreter/platforms/linux/output_devices.c $(CFLAGS)

input_devices.o: src/interpreter/platforms/linux/input_devices.c src/include/platforms/input_devices.h
	cc -c src/interpreter/platforms/linux/input_devices.c $(CFLAGS)

string.o: src/interpreter/core/string.c src/include/core/string.h
	cc -c src/interpreter/core/string.c $(CFLAGS)

parameters.o: src/interpreter/core/parameters.c src/include/core/parameters.h
	cc -c src/interpreter/core/parameters.c $(CFLAGS)

type_conversion.o: src/interpreter/core/type_conversion.c src/include/core/type_conversion.h
	cc -c src/interpreter/core/type_conversion.c $(CFLAGS)

array.o: src/interpreter/core/array.c src/include/core/array.h
	cc -c src/interpreter/core/array.c $(CFLAGS)

bank_operations.o: src/interpreter/run/bank_operations.c src/include/run/bank_operations.h
	cc -c src/interpreter/run/bank_operations.c $(CFLAGS)

clean:
	rm snowflake main.o parse_file.o instructions.o program.o type_conversion.o \
		output_devices.o parse_instruction.o print_program.o run_program.o bank.o \
		run_instruction_types.o run_instruction_basic.o input_devices.o \
		string.o parameters.o run_instruction_branching.o \
		run_instruction_math.o run_instruction_logic.o run_instruction_array.o \
		logging.o array.o run_instruction_io.o bank_operations.o \
		print_instruction.o 