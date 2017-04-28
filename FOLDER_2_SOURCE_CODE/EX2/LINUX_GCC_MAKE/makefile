########
# CALC #
########
CC=gcc

###############
# DIRECTORIES #
###############
#BASEDIR                 = /home/oren/GIT/COMPILATION_IDC_FOR_STUDENTS/FOLDER_2_SOURCE_CODE/EX1/LINUX_GCC_MAKE
BASEDIR                 = .
LEXER_DIR               = $(BASEDIR)/FOLDER_0_Flex
LEXER_MatReader_DIR     = $(BASEDIR)/FOLDER_1_LEXER_MatReader
LEXER_RowOperations_DIR = $(BASEDIR)/FOLDER_2_LEXER_RowOperations
LEXER_SolutionSet_DIR   = $(BASEDIR)/FOLDER_3_LEXER_SolutionSet
SOURCE_FILES_DIR        = $(BASEDIR)/FOLDER_4_SOURCE_FILES
HEADER_FILES_DIR        = $(BASEDIR)/FOLDER_5_HEADER_FILES
PROG_DIR                = $(BASEDIR)/FOLDER_6_Lini
INPUT_DIR               = $(BASEDIR)/FOLDER_7_INPUT
OUTPUT_DIR              = $(BASEDIR)/FOLDER_8_OUTPUT
LEXER_SOURCE_DIR        = $(LEXER_DIR)/SOURCE_FILES
LEXER_HEADER_DIR        = $(LEXER_DIR)/HEADER_FILES
LEXER_OBJECT_DIR        = $(LEXER_DIR)/OBJECT_FILES

###############
# LEXER FLAGS #
###############
LEXER_PROGRAM_FLAGS_MatReader     = -o$(LEXER_MatReader_DIR)/MatReader_Lexer.c
LEXER_PROGRAM_FLAGS_RowOperations = -o$(LEXER_RowOperations_DIR)/RowOperations_Lexer.c
LEXER_PROGRAM_FLAGS_SolutionSet   = -o$(LEXER_SolutionSet_DIR)/SolutionSet_Lexer.c

#####################
# LEXER INPUT FILES #
#####################
LEXER_INPUT_MatReader     = $(LEXER_MatReader_DIR)/MatReader.lex
LEXER_INPUT_RowOperations = $(LEXER_RowOperations_DIR)/RowOperations.lex
LEXER_INPUT_SolutionSet   = $(LEXER_SolutionSet_DIR)/SolutionSet.lex

#########
# LEXER #
#########
LEXER_FLAGS           = -I$(LEXER_HEADER_DIR) -w
LEXER_PROGRAM         = $(LEXER_DIR)/MyFlex 
LEXER_SOURCE_FILES   := $(wildcard  $(LEXER_SOURCE_DIR)/*.c)
LEXER_HEADER_FILES   := $(wildcard  $(LEXER_HEADER_DIR)/*.h)
LEXER_OBJECT_FILES   := $(addprefix $(LEXER_OBJECT_DIR)/,$(LEXER_SOURCE_FILES,.c=.o))

########
# Lini #
########
Lini_FLAGS         = -I$(HEADER_FILES_DIR) -w
Lini_PROGRAM       = $(PROG_DIR)/Lini
Lini_SOURCE_FILES := $(wildcard  $(SOURCE_FILES_DIR)/*.c)
Lini_HEADER_FILES := $(wildcard  $(HEADER_FILES_DIR)/*.h)

################
# INPUT/OUTPUT #
################
INPUT	=	$(INPUT_DIR)/Mat.txt \
			$(INPUT_DIR)/RowOperations.txt \
			$(INPUT_DIR)/SolutionSet.txt

OUTPUT	=	$(OUTPUT_DIR)/MatTokens.txt \
			$(OUTPUT_DIR)/RowOperationsTokens.txt \
			$(OUTPUT_DIR)/SolutionSetTokens.txt

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
	rm -rf $(Lini_PROGRAM) 
	rm -rf $(SOURCE_FILES_DIR)/MatReader_Lexer.c
	rm -rf $(SOURCE_FILES_DIR)/RowOperations_Lexer.c
	rm -rf $(SOURCE_FILES_DIR)/SolutionSet_Lexer.c
	@echo "\n"
	@echo "******************"
	@echo "* Build Flex ... *"
	@echo "******************"
	@echo "\n"	
	$(CC) $(LEXER_FLAGS) $(LEXER_SOURCE_FILES) -o $(LEXER_PROGRAM)
	@echo "\n"
	@echo "************************"
	@echo "* Run All Lexer(s) ... *"
	@echo "************************"
	@echo "\n"
	$(LEXER_PROGRAM) $(LEXER_PROGRAM_FLAGS_MatReader) $(LEXER_INPUT_MatReader)
	$(LEXER_PROGRAM) $(LEXER_PROGRAM_FLAGS_RowOperations) $(LEXER_INPUT_RowOperations)
	$(LEXER_PROGRAM) $(LEXER_PROGRAM_FLAGS_SolutionSet) $(LEXER_INPUT_SolutionSet)
	@echo "\n"
	@echo "**************************************************"
	@echo "* Move Generated Lexer(s) to destined folder ... *"
	@echo "**************************************************"
	@echo "\n"	
	mv $(LEXER_MatReader_DIR)/MatReader_Lexer.c $(SOURCE_FILES_DIR)
	mv $(LEXER_RowOperations_DIR)/RowOperations_Lexer.c $(SOURCE_FILES_DIR)
	mv $(LEXER_SolutionSet_DIR)/SolutionSet_Lexer.c $(SOURCE_FILES_DIR)
	@echo "\n"
	@echo "******************"
	@echo "* Build Lini ... *"
	@echo "******************"
	@echo "\n"	
	$(CC) $(Lini_FLAGS) $(Lini_SOURCE_FILES) -o $(Lini_PROGRAM)
	@echo "\n"
	@echo "********************"
	@echo "* Execute Lini ... *"
	@echo "********************"
	@echo "\n"	
	$(Lini_PROGRAM) $(INPUT) $(OUTPUT)

