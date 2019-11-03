###############
# DIRECTORIES #
###############
BASEDIR           = $(shell pwd)
JFlex_DIR         = ${BASEDIR}/FOLDER_0_JFlex
SRC_DIR           = ${BASEDIR}/FOLDER_2_SRC
BIN_DIR           = ${BASEDIR}/FOLDER_3_BIN
INPUT_DIR         = ${BASEDIR}/FOLDER_4_INPUT
OUTPUT_DIR        = ${BASEDIR}/FOLDER_5_OUTPUT
EXTERNAL_JARS_DIR = ${BASEDIR}/FOLDER_7_EXTERNAL_JARS
MANIFEST_DIR      = ${BASEDIR}/FOLDER_8_MANIFEST

#########
# FILES #
#########
JFlex_GENERATED_FILE = ${SRC_DIR}/Lexer.java
SRC_FILES            = ${SRC_DIR}/*.java
CLASS_FILES          = ${BIN_DIR}/*.class
EXTERNAL_JAR_FILES   = ${EXTERNAL_JARS_DIR}/java-cup-11b-runtime.jar
MANIFEST_FILE        = ${MANIFEST_DIR}/MANIFEST.MF

########################
# DEFINITIONS :: JFlex #
########################
JFlex_PROGRAM  = jflex
JFlex_FLAGS    = -q
JFlex_DEST_DIR = ${SRC_DIR}
JFlex_FILE     = ${JFlex_DIR}/LEX_FILE.lex

########################
# DEFINITIONS :: LEXER #
########################
INPUT    = ${INPUT_DIR}/Input.txt
OUTPUT   = ${OUTPUT_DIR}/OutputTokens.txt

all:
	clear
	@echo "****************************"
	@echo "*                          *"
	@echo "*                          *"
	@echo "* [0] Remove LEXER program *"
	@echo "*                          *"
	@echo "*                          *"
	@echo "****************************"
	rm -rf LEXER
	@echo "\n"
	@echo "***********************************************************"
	@echo "*                                                         *"
	@echo "*                                                         *"
	@echo "* [1] Remove *.class files and JFlex generated Lexer.java *"
	@echo "*                                                         *"
	@echo "*                                                         *"
	@echo "***********************************************************"
	rm -rf ${JFlex_GENERATED_FILE} ${CLASS_FILES}
	@echo "\n"
	@echo "************************************************************"
	@echo "*                                                          *"
	@echo "*                                                          *"
	@echo "* [2] Use JFlex to synthesize Lexer.java from LEX_FILE.lex *"
	@echo "*                                                          *"
	@echo "*                                                          *"
	@echo "************************************************************"
	$(JFlex_PROGRAM) ${JFlex_FLAGS} -d ${JFlex_DEST_DIR} ${JFlex_FILE}
	@echo "\n"
	@echo "*********************************************************************"
	@echo "*                                                                   *"
	@echo "*                                                                   *"
	@echo "* [3] Create *.class files from *.java files + External *.jar files *"
	@echo "*                                                                   *"
	@echo "*                                                                   *"
	@echo "*********************************************************************"
	javac -cp ${EXTERNAL_JAR_FILES} -d ${BIN_DIR} ${SRC_FILES}
	@echo "\n"
	@echo "************************************************************************"
	@echo "*                                                                      *"
	@echo "*                                                                      *"
	@echo "* [4] Create a JAR file from from *.class files + External *.jar files *"
	@echo "*                                                                      *"
	@echo "*                                                                      *"
	@echo "************************************************************************"
	jar cfm LEXER ${MANIFEST_FILE} -C ${BIN_DIR} .
	@echo "\n"
	@echo "*****************************"
	@echo "*                           *"
	@echo "*                           *"
	@echo "* [5] Run resulting program *"
	@echo "*                           *"
	@echo "*                           *"
	@echo "*****************************"
	java -jar LEXER ${INPUT} ${OUTPUT}

