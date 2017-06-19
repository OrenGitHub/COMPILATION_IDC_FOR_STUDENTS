############
# COMPILER #
############
CC=gcc

###############
# DIRECTORIES #
###############
BASEDIR              = $(shell pwd)
LEXER_DIR            = $(BASEDIR)/FOLDER_00_Flex
PARSER_DIR           = $(BASEDIR)/FOLDER_01_Bison
STARKIST_DIR         = $(BASEDIR)/FOLDER_02_LEXER_PARSER_StarKist
CODEGEN__DIR         = $(BASEDIR)/FOLDER_03_LEXER_PARSER_PseudoAsm_To_Simulation
REGALLOC_DIR         = $(BASEDIR)/FOLDER_04_LEXER_PARSER_RegAlloc
COMPILER_SOURCE_DIR  = $(BASEDIR)/FOLDER_05_COMPILER_SOURCE_FILES
COMPILER_HEADER_DIR  = $(BASEDIR)/FOLDER_06_COMPILER_HEADER_FILES
COMPILER_DIR         = $(BASEDIR)/FOLDER_07_COMPILER
INPUT_DIR            = $(BASEDIR)/FOLDER_08_INPUT_PROGRAMS
OUTPUT_DIR           = $(BASEDIR)/FOLDER_10_OUTPUT_ASM
GDB_COMMANDS_DIR     = $(BASEDIR)/FOLDER_11_GDB_SCRIPTS
LEXER_SOURCE_DIR     = $(LEXER_DIR)/SOURCE_FILES
LEXER_HEADER_DIR     = $(LEXER_DIR)/HEADER_FILES
LEXER_OBJECT_DIR     = $(LEXER_DIR)/OBJECT_FILES
PARSER_SOURCE_DIR    = $(PARSER_DIR)/SOURCE_FILES
PARSER_HEADER_DIR    = $(PARSER_DIR)/HEADER_FILES
PARSER_OBJECT_DIR    = $(PARSER_DIR)/OBJECT_FILES

###############
# LEXER FLAGS #
###############
LEXER_PROGRAM_FLAGS_StarKist   = -o$(STARKIST_DIR)/FILE_04_StarKist_Lexer.c
LEXER_PROGRAM_FLAGS__CodeGen   = -o$(CODEGEN__DIR)/FILE_17_PseudoAsm_To_Simulation_Lexer.c
LEXER_PROGRAM_FLAGS_RegAlloc   = -o$(REGALLOC_DIR)/FILE_23_RegAlloc_Lexer.c

################
# PARSER FLAGS #
################
PARSER_PROGRAM_FLAGS_StarKist  = -d -v -o $(STARKIST_DIR)/FILE_05_StarKist_Parser.c
PARSER_PROGRAM_FLAGS__CodeGen  = -d -v -p zz -o $(CODEGEN__DIR)/FILE_18_PseudoAsm_To_Simulation_Parser.c
PARSER_PROGRAM_FLAGS_RegAlloc  = -d -v -p gg -o $(REGALLOC_DIR)/FILE_24_RegAlloc_Parser.c

#####################
# LEXER INPUT FILES #
#####################
LEXER_INPUT_StarKist  = $(STARKIST_DIR)/StarKist.lex
LEXER_INPUT__CodeGen  = $(CODEGEN__DIR)/CodeGen.lex
LEXER_INPUT_RegAlloc  = $(REGALLOC_DIR)/RegAlloc.lex

######################
# PARSER INPUT FILES #
######################
PARSER_INPUT_StarKist = $(STARKIST_DIR)/StarKist.y
PARSER_INPUT__CodeGen = $(CODEGEN__DIR)/CodeGen.y
PARSER_INPUT_RegAlloc = $(REGALLOC_DIR)/RegAlloc.y

#########
# LEXER #
#########
LEXER_FLAGS           = -I$(LEXER_HEADER_DIR) -w
LEXER_PROGRAM         = $(LEXER_DIR)/MyFlex 
LEXER_SOURCE_FILES   := $(wildcard  $(LEXER_SOURCE_DIR)/*.c)
LEXER_HEADER_FILES   := $(wildcard  $(LEXER_HEADER_DIR)/*.h)
LEXER_OBJECT_FILES   := $(addprefix $(LEXER_OBJECT_DIR)/,$(LEXER_SOURCE_FILES,.c=.o))

##########
# PARSER #
##########
PARSER_FLAGS          = -I$(PARSER_HEADER_DIR) -w
PARSER_PROGRAM        = $(PARSER_DIR)/MyBison 
PARSER_SOURCE_FILES  := $(wildcard  $(PARSER_SOURCE_DIR)/*.c)
PARSER_HEADER_FILES  := $(wildcard  $(PARSER_HEADER_DIR)/*.h)
PARSER_OBJECT_FILES  := $(addprefix $(PARSER_OBJECT_DIR)/,$(PARSER_SOURCE_FILES,.c=.o))

############
# COMPILER #
############
COMPILER_FLAGS         = -ggdb -I$(COMPILER_HEADER_DIR) -w
COMPILER_PROGRAM       = $(COMPILER_DIR)/compiler
COMPILER_SOURCE_FILES := $(wildcard  $(COMPILER_SOURCE_DIR)/*.c)
COMPILER_HEADER_FILES := $(wildcard  $(COMPILER_HEADER_DIR)/*.h)
COMPILER_OBJECT_FILES := $(addprefix $(LEXER_OBJECT_DIR)/,$(LEXER_SOURCE_FILES,.c=.o))

################
# INPUT/OUTPUT #
################
INPUT_STARKIST_FILE  = ${INPUT_DIR}/Input.txt
OUTPUT_MIPS_ASM_FILE = ${OUTPUT_DIR}/Output.s
OUTPUT               = ${OUTPUT_DIR}/Output.txt

#######
# GDB #
#######
GDB_COMMANDS = ${GDB_COMMANDS_DIR}/gdbCommands.txt

##########################
# ALL LEXER(S) PARSER(S) #
##########################
all:
	@echo "\n"
	@echo "*****************"
	@echo "* Clean All ... *"
	@echo "*****************"
	@echo "\n"
	rm -rf $(LEXER_PROGRAM)
	rm -rf $(PARSER_PROGRAM)
	rm -rf $(COMPILER_PROGRAM)
	rm -rf $(COMPILER_SOURCE_DIR)/FILE_04_StarKist_Lexer.c
	rm -rf $(COMPILER_HEADER_DIR)/FILE_05_StarKist_Parser.h
	rm -rf $(COMPILER_SOURCE_DIR)/FILE_05_StarKist_Parser.c
	rm -rf $(COMPILER_SOURCE_DIR)/FILE_23_RegAlloc_Lexer.c
	rm -rf $(COMPILER_SOURCE_DIR)/FILE_24_RegAlloc_Parser.c
	rm -rf $(COMPILER_HEADER_DIR)/FILE_24_RegAlloc_Parser.h
	rm -rf $(COMPILER_SOURCE_DIR)/FILE_17_PseudoAsm_To_Simulation_Lexer.c
	rm -rf $(COMPILER_SOURCE_DIR)/FILE_18_PseudoAsm_To_Simulation_Parser.c
	rm -rf $(COMPILER_HEADER_DIR)/FILE_18_PseudoAsm_To_Simulation_Parser.h
	@echo "\n"
	@echo "**************************"
	@echo "* Build Flex & Bison ... *"
	@echo "**************************"
	@echo "\n"
	$(CC) $(LEXER_FLAGS)  $(LEXER_SOURCE_FILES)  -o $(LEXER_PROGRAM)
	$(CC) $(PARSER_FLAGS) $(PARSER_SOURCE_FILES) -o $(PARSER_PROGRAM)
	@echo "\n"
	@echo "**********************************"
	@echo "* Run All Lexer(s) Parser(s) ... *"
	@echo "**********************************"
	@echo "\n"
	$(LEXER_PROGRAM)  $(LEXER_PROGRAM_FLAGS_StarKist)  $(LEXER_INPUT_StarKist)
	$(LEXER_PROGRAM)  $(LEXER_PROGRAM_FLAGS__CodeGen)  $(LEXER_INPUT__CodeGen)
	$(LEXER_PROGRAM)  $(LEXER_PROGRAM_FLAGS_RegAlloc)  $(LEXER_INPUT_RegAlloc)
	$(PARSER_PROGRAM) $(PARSER_PROGRAM_FLAGS_StarKist) $(PARSER_INPUT_StarKist)
	$(PARSER_PROGRAM) $(PARSER_PROGRAM_FLAGS__CodeGen) $(PARSER_INPUT__CodeGen)
	$(PARSER_PROGRAM) $(PARSER_PROGRAM_FLAGS_RegAlloc) $(PARSER_INPUT_RegAlloc)
	@echo "\n"
	@echo "***************************************************************"
	@echo "* Move Generated Lexer(s) Parser(s) to destined folder(s) ... *"
	@echo "***************************************************************"
	@echo "\n"
	mv $(STARKIST_DIR)/FILE_04_StarKist_Lexer.c  $(COMPILER_SOURCE_DIR)
	mv $(STARKIST_DIR)/FILE_05_StarKist_Parser.c $(COMPILER_SOURCE_DIR)
	mv $(STARKIST_DIR)/FILE_05_StarKist_Parser.h $(COMPILER_HEADER_DIR)
	mv $(REGALLOC_DIR)/FILE_23_RegAlloc_Lexer.c  $(COMPILER_SOURCE_DIR)
	mv $(REGALLOC_DIR)/FILE_24_RegAlloc_Parser.c $(COMPILER_SOURCE_DIR)
	mv $(REGALLOC_DIR)/FILE_24_RegAlloc_Parser.h $(COMPILER_HEADER_DIR)
	mv $(CODEGEN__DIR)/FILE_17_PseudoAsm_To_Simulation_Lexer.c  $(COMPILER_SOURCE_DIR)
	mv $(CODEGEN__DIR)/FILE_18_PseudoAsm_To_Simulation_Parser.c $(COMPILER_SOURCE_DIR)
	mv $(CODEGEN__DIR)/FILE_18_PseudoAsm_To_Simulation_Parser.h $(COMPILER_HEADER_DIR)
	@echo "\n"
	@echo "**********************"
	@echo "* Build compiler ... *"
	@echo "**********************"
	@echo "\n"
	$(CC) $(COMPILER_FLAGS) $(COMPILER_SOURCE_FILES) -o $(COMPILER_PROGRAM)
	@echo "\n"
	@echo "*********************************"
	@echo "* Compile the input program ... *"
	@echo "*********************************"
	@echo "\n"
	${COMPILER_PROGRAM} ${INPUT_STARKIST_FILE} ${OUTPUT_MIPS_ASM_FILE}
	@echo "\n"
	@echo "************************************************"
	@echo "* Run the compiled program with mips simulator *"
	@echo "************************************************"
	@echo "\n"
	spim -file ${OUTPUT_MIPS_ASM_FILE} > ${OUTPUT} 
	@echo "\n"
	@echo "***************************************"
	@echo "* Optionally, debug compiler with dbg *"
	@echo "***************************************"
	@echo "\n"
	#gdb -x ${GDB_COMMANDS} --args ${COMPILER_PROGRAM} ${INPUT} ${OUTPUT}
	
