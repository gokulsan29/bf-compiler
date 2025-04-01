CPP_FILES = bf_parse.cpp \
						bf_ast.cpp \
						bf_eval.cpp \
						bfc.cpp

BFC_DEPS = $(CPP_FILES) \
					 bf_ast.h

BFC_LIBS = $(CPP_FILES)

bfc: $(BFC_DEPS)
	g++ -g -O2 $(BFC_LIBS) -o $@

.PHONY: clean
clean:
	rm -f bfc compile_commands.json

.PHONY: compile_commands
compile_commands: clean
	bear -- make

