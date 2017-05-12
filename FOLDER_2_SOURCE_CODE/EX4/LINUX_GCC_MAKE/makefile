############
# COMPILER #
############
CC=gcc

###############
# DIRECTORIES #
###############
BASEDIR              = .
LEXER_DIR            = $(BASEDIR)/FOLDER_00_Flex
PARSER_DIR           = $(BASEDIR)/FOLDER_01_Bison
MAT_READER_DIR       = $(BASEDIR)/FOLDER_02_LEXER_PARSER_MatReader
ROW_OPERATIONS_DIR   = $(BASEDIR)/FOLDER_03_LEXER_PARSER_RowOperations
SOLUTION_SET_DIR     = $(BASEDIR)/FOLDER_04_LEXER_PARSER_SolutionSet
LINI_SOURCE_DIR      = $(BASEDIR)/FOLDER_05_Lini_SOURCE_FILES
LINI_HEADER_DIR      = $(BASEDIR)/FOLDER_06_Lini_HEADER_FILES
LINI_DIR             = $(BASEDIR)/FOLDER_07_Lini
INPUT_DIR            = $(BASEDIR)/FOLDER_08_INPUT_FILES
OUTPUT_DIR           = $(BASEDIR)/FOLDER_09_OUTPUT_FILES
LEXER_SOURCE_DIR     = $(LEXER_DIR)/SOURCE_FILES
LEXER_HEADER_DIR     = $(LEXER_DIR)/HEADER_FILES
LEXER_OBJECT_DIR     = $(LEXER_DIR)/OBJECT_FILES
PARSER_SOURCE_DIR    = $(PARSER_DIR)/SOURCE_FILES
PARSER_HEADER_DIR    = $(PARSER_DIR)/HEADER_FILES
PARSER_OBJECT_DIR    = $(PARSER_DIR)/OBJECT_FILES

###############
# LEXER FLAGS #
###############
LEXER_PROGRAM_FLAGS_MatReader     = -o$(MAT_READER_DIR)/FILE_05_MatReader_Lexer.c
LEXER_PROGRAM_FLAGS_RowOperations = -o$(ROW_OPERATIONS_DIR)/FILE_10_RowOperations_Lexer.c
LEXER_PROGRAM_FLAGS_SolutionSet   = -o$(SOLUTION_SET_DIR)/FILE_15_SolutionSet_Lexer.c

################
# PARSER FLAGS #
################
PARSER_PROGRAM_FLAGS_MatReader     = -d -v -p aa -o $(MAT_READER_DIR)/FILE_06_MatReader_Parser.c
PARSER_PROGRAM_FLAGS_RowOperations = -d -v -p bb -o $(ROW_OPERATIONS_DIR)/FILE_11_RowOperations_Parser.c
PARSER_PROGRAM_FLAGS_SolutionSet   = -d -v -p cc -o $(SOLUTION_SET_DIR)/FILE_16_SolutionSet_Parser.c

#####################
# LEXER INPUT FILES #
#####################
LEXER_INPUT_MatReader     = $(MAT_READER_DIR)/MatReader.lex
LEXER_INPUT_RowOperations = $(ROW_OPERATIONS_DIR)/RowOperations.lex
LEXER_INPUT_SolutionSet   = $(SOLUTION_SET_DIR)/SolutionSet.lex

######################
# PARSER INPUT FILES #
######################
PARSER_INPUT_MatReader     = $(MAT_READER_DIR)/MatReader.y
PARSER_INPUT_RowOperations = $(ROW_OPERATIONS_DIR)/RowOperations.y
PARSER_INPUT_SolutionSet   = $(SOLUTION_SET_DIR)/SolutionSet.y

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

########
# LINI #
########
LINI_FLAGS         = -I$(LINI_HEADER_DIR) -w
LINI_PROGRAM       = $(LINI_DIR)/Lini
LINI_SOURCE_FILES := $(wildcard  $(LINI_SOURCE_DIR)/*.c)
LINI_HEADER_FILES := $(wildcard  $(LINI_HEADER_DIR)/*.h)
LINI_OBJECT_FILES := $(addprefix $(LEXER_OBJECT_DIR)/,$(LEXER_SOURCE_FILES,.c=.o))

################
# INPUT/OUTPUT #
################
INPUT  = $(INPUT_DIR)/Input_SolutionSet.txt
OUTPUT = $(OUTPUT_DIR)/Status_SolutionSet.txt

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
	rm -rf $(LINI_PROGRAM)
	rm -rf $(LINI_SOURCE_DIR)/FILE_05_MatReader_Lexer.c
	rm -rf $(LINI_SOURCE_DIR)/FILE_06_MatReader_Parser.c
	rm -rf $(LINI_HEADER_DIR)/FILE_06_MatReader_Parser.h
	rm -rf $(LINI_SOURCE_DIR)/FILE_10_RowOperations_Lexer.c
	rm -rf $(LINI_SOURCE_DIR)/FILE_11_RowOperations_Parser.c
	rm -rf $(LINI_HEADER_DIR)/FILE_11_RowOperations_Parser.h
	rm -rf $(LINI_SOURCE_DIR)/FILE_15_SolutionSet_Lexer.c
	rm -rf $(LINI_SOURCE_DIR)/FILE_16_SolutionSet_Parser.c
	rm -rf $(LINI_HEADER_DIR)/FILE_16_SolutionSet_Parser.h
	@echo "\n"
	@echo "******************"
	@echo "* Build Flex ... *"
	@echo "******************"
	@echo "\n"
	$(CC) $(LEXER_FLAGS)  $(LEXER_SOURCE_FILES)  -o $(LEXER_PROGRAM)
	@echo "\n"
	@echo "*******************"
	@echo "* Build Bison ... *"
	@echo "*******************"
	@echo "\n"
	$(CC) $(PARSER_FLAGS) $(PARSER_SOURCE_FILES) -o $(PARSER_PROGRAM)
	@echo "\n"
	@echo "**********************************"
	@echo "* Run All Lexer(s) Parser(s) ... *"
	@echo "**********************************"
	@echo "\n"
	$(LEXER_PROGRAM)  $(LEXER_PROGRAM_FLAGS_MatReader)      $(LEXER_INPUT_MatReader)
	$(LEXER_PROGRAM)  $(LEXER_PROGRAM_FLAGS_RowOperations)  $(LEXER_INPUT_RowOperations)
	$(LEXER_PROGRAM)  $(LEXER_PROGRAM_FLAGS_SolutionSet)    $(LEXER_INPUT_SolutionSet)
	$(PARSER_PROGRAM) $(PARSER_PROGRAM_FLAGS_MatReader)     $(PARSER_INPUT_MatReader)
	$(PARSER_PROGRAM) $(PARSER_PROGRAM_FLAGS_RowOperations) $(PARSER_INPUT_RowOperations)
	$(PARSER_PROGRAM) $(PARSER_PROGRAM_FLAGS_SolutionSet)   $(PARSER_INPUT_SolutionSet)
	@echo "\n"
	@echo "***************************************************************"
	@echo "* Move Generated Lexer(s) Parser(s) to destined folder(s) ... *"
	@echo "***************************************************************"
	@echo "\n"
	mv $(MAT_READER_DIR)/FILE_05_MatReader_Lexer.c  $(LINI_SOURCE_DIR)
	mv $(MAT_READER_DIR)/FILE_06_MatReader_Parser.c $(LINI_SOURCE_DIR)
	mv $(MAT_READER_DIR)/FILE_06_MatReader_Parser.h $(LINI_HEADER_DIR)
	mv $(ROW_OPERATIONS_DIR)/FILE_10_RowOperations_Lexer.c  $(LINI_SOURCE_DIR)
	mv $(ROW_OPERATIONS_DIR)/FILE_11_RowOperations_Parser.c $(LINI_SOURCE_DIR)
	mv $(ROW_OPERATIONS_DIR)/FILE_11_RowOperations_Parser.h $(LINI_HEADER_DIR)
	mv $(SOLUTION_SET_DIR)/FILE_15_SolutionSet_Lexer.c  $(LINI_SOURCE_DIR)
	mv $(SOLUTION_SET_DIR)/FILE_16_SolutionSet_Parser.c $(LINI_SOURCE_DIR)
	mv $(SOLUTION_SET_DIR)/FILE_16_SolutionSet_Parser.h $(LINI_HEADER_DIR)
	@echo "\n"
	@echo "******************"
	@echo "* Build Lini ... *"
	@echo "******************"
	@echo "\n"
	$(CC) $(LINI_FLAGS) $(LINI_SOURCE_FILES) -o $(LINI_PROGRAM)
	@echo "\n"
	@echo "********************"
	@echo "* Execute Lini ... *"
	@echo "********************"
	@echo "\n"
	$(LINI_PROGRAM) $(INPUT) $(OUTPUT)

