########
# CALC #
########
CC=gcc

###############
# DIRECTORIES #
###############
BASEDIR                = .
LEXER_DIR              = $(BASEDIR)/FOLDER_0_Flex
LEXER_Calc_DIR         = $(BASEDIR)/FOLDER_1_LEXER_Calc
SOURCE_FILES_DIR       = $(BASEDIR)/FOLDER_2_SOURCE_FILES
HEADER_FILES_DIR       = $(BASEDIR)/FOLDER_3_HEADER_FILES
PROG_DIR               = $(BASEDIR)/FOLDER_4_CALC
INPUT_DIR              = $(BASEDIR)/FOLDER_5_INPUT
OUTPUT_DIR             = $(BASEDIR)/FOLDER_6_OUTPUT
LEXER_SOURCE_DIR       = $(LEXER_DIR)/SOURCE_FILES
LEXER_HEADER_DIR       = $(LEXER_DIR)/HEADER_FILES
LEXER_OBJECT_DIR       = $(LEXER_DIR)/OBJECT_FILES

###############
# LEXER FLAGS #
###############
LEXER_PROGRAM_FLAGS_Calc   = -o$(LEXER_Calc_DIR)/Calc_Lexer.c

#####################
# LEXER INPUT FILES #
#####################
LEXER_INPUT_Calc = $(LEXER_Calc_DIR)/Calc.lex

#########
# LEXER #
#########
LEXER_FLAGS           = -I$(LEXER_HEADER_DIR) -w
LEXER_PROGRAM         = $(LEXER_DIR)/MyFlex 
LEXER_SOURCE_FILES   := $(wildcard  $(LEXER_SOURCE_DIR)/*.c)
LEXER_HEADER_FILES   := $(wildcard  $(LEXER_HEADER_DIR)/*.h)
LEXER_OBJECT_FILES   := $(addprefix $(LEXER_OBJECT_DIR)/,$(LEXER_SOURCE_FILES,.c=.o))

########
# CALC #
########
CALC_FLAGS         = -I$(HEADER_FILES_DIR) -w
CALC_PROGRAM       = $(PROG_DIR)/calc
CALC_SOURCE_FILES := $(wildcard  $(SOURCE_FILES_DIR)/*.c)
CALC_HEADER_FILES := $(wildcard  $(HEADER_FILES_DIR)/*.h)

################
# INPUT/OUTPUT #
################
INPUT  = $(INPUT_DIR)/Input.txt
OUTPUT = $(OUTPUT_DIR)/Output.txt

##########################
# ALL LEXER(S) PARSER(S) #
##########################
all:
	@rm -rf $(LEXER_PROGRAM) 
	@rm -rf $(CALC_PROGRAM) 
	@rm -rf $(SOURCE_FILES_DIR)/Calc_Lexer.c
	@$(CC) $(LEXER_FLAGS) $(LEXER_SOURCE_FILES) -o $(LEXER_PROGRAM)
	@$(LEXER_PROGRAM) $(LEXER_PROGRAM_FLAGS_Calc) $(LEXER_INPUT_Calc)
	@mv $(LEXER_Calc_DIR)/Calc_Lexer.c $(SOURCE_FILES_DIR)
	@$(CC) $(CALC_FLAGS) $(CALC_SOURCE_FILES) -o $(CALC_PROGRAM)
	@$(CALC_PROGRAM) $(INPUT) $(OUTPUT)

