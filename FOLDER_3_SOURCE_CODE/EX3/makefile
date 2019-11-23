###############
# DIRECTORIES #
###############
BASEDIR           = $(shell pwd)
JFlex_DIR         = ${BASEDIR}/FOLDER_0_JFlex
CUP_DIR           = ${BASEDIR}/FOLDER_1_CUP
SRC_DIR           = ${BASEDIR}/FOLDER_2_SRC
BIN_DIR           = ${BASEDIR}/FOLDER_3_BIN
INPUT_DIR         = ${BASEDIR}/FOLDER_4_INPUT
OUTPUT_DIR        = ${BASEDIR}/FOLDER_5_OUTPUT
EXTERNAL_JARS_DIR = ${BASEDIR}/FOLDER_7_EXTERNAL_JARS
MANIFEST_DIR      = ${BASEDIR}/FOLDER_8_MANIFEST

#########
# FILES #
#########
JFlex_GENERATED_FILE      = ${SRC_DIR}/Lexer.java
CUP_GENERATED_FILES       = ${SRC_DIR}/Parser.java ${SRC_DIR}/TokenNames.java
JFlex_CUP_GENERATED_FILES = ${JFlex_GENERATED_FILE} ${CUP_GENERATED_FILES}
SRC_FILES                 = ${SRC_DIR}/*.java              \
                            ${SRC_DIR}/AST/*.java          \
                            ${SRC_DIR}/TYPES/*.java        \
                            ${SRC_DIR}/SYMBOL_TABLE/*.java
EXTERNAL_JAR_FILES        = ${EXTERNAL_JARS_DIR}/java-cup-11b-runtime.jar
MANIFEST_FILE             = ${MANIFEST_DIR}/MANIFEST.MF

########################
# DEFINITIONS :: JFlex #
########################
JFlex_PROGRAM  = jflex
JFlex_FLAGS    = -q
JFlex_DEST_DIR = ${SRC_DIR}
JFlex_FILE     = ${JFlex_DIR}/LEX_FILE.lex

######################
# DEFINITIONS :: CUP #
######################
CUP_PROGRAM                    = java -jar ${EXTERNAL_JARS_DIR}/java-cup-11b.jar 
CUP_FILE                       = ${CUP_DIR}/CUP_FILE.cup
CUP_GENERATED_PARSER_NAME      = Parser
CUP_GENERATED_SYMBOLS_FILENAME = TokenNames

######################
# DEFINITIONS :: CUP #
######################
CUP_FLAGS =                                \
-nowarn                                    \
-parser  ${CUP_GENERATED_PARSER_NAME}      \
-symbols ${CUP_GENERATED_SYMBOLS_FILENAME} 

#########################
# DEFINITIONS :: PARSER #
#########################
INPUT    = ${INPUT_DIR}/Input.txt
OUTPUT   = ${OUTPUT_DIR}/SemanticStatus.txt

##########
# TARGET #
##########
compile:
	clear
	@echo "*******************************"
	@echo "*                             *"
	@echo "*                             *"
	@echo "* [0] Remove COMPILER program *"
	@echo "*                             *"
	@echo "*                             *"
	@echo "*******************************"
	rm -rf COMPILER
	@echo "\n"
	@echo "************************************************************"
	@echo "*                                                          *"
	@echo "*                                                          *"
	@echo "* [1] Remove *.class files and JFlex-CUP generated files:  *"
	@echo "*                                                          *"
	@echo "*     Lexer.java                                           *"
	@echo "*     Parser.java                                          *"
	@echo "*     TokenNames.java                                      *"
	@echo "*                                                          *"
	@echo "************************************************************"
	rm -rf ${JFlex_CUP_GENERATED_FILES} ${BIN_DIR}/*.class ${BIN_DIR}/AST/*.class
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
	@echo "*******************************************************************************"
	@echo "*                                                                             *"
	@echo "*                                                                             *"
	@echo "* [3] Use CUP to synthesize Parser.java and TokenNames.java from CUP_FILE.cup *"
	@echo "*                                                                             *"
	@echo "*                                                                             *"
	@echo "*******************************************************************************"
	$(CUP_PROGRAM) ${CUP_FLAGS} -destdir ${SRC_DIR} ${CUP_FILE}
	@echo "\n"
	@echo "********************************************************"
	@echo "*                                                      *"
	@echo "*                                                      *"
	@echo "* [4] Create *.class files from *.java files + CUP JAR *"
	@echo "*                                                      *"
	@echo "*                                                      *"
	@echo "********************************************************"
	javac -cp ${EXTERNAL_JAR_FILES} -d ${BIN_DIR} ${SRC_FILES}
	@echo "\n"
	@echo "***********************************************************"
	@echo "*                                                         *"
	@echo "*                                                         *"
	@echo "* [5] Create a JAR file from from *.class files + CUP JAR *"
	@echo "*                                                         *"
	@echo "*                                                         *"
	@echo "***********************************************************"
	jar cfm COMPILER ${MANIFEST_FILE} -C ${BIN_DIR} .
	
everything:
	clear
	@echo "*****************************"
	@echo "*                           *"
	@echo "*                           *"
	@echo "* [0] Remove PARSER program *"
	@echo "*                           *"
	@echo "*                           *"
	@echo "*****************************"
	rm -rf COMPILER
	@echo "\n"
	@echo "************************************************************"
	@echo "*                                                          *"
	@echo "*                                                          *"
	@echo "* [1] Remove *.class files and JFlex-CUP generated files:  *"
	@echo "*                                                          *"
	@echo "*     Lexer.java                                           *"
	@echo "*     Parser.java                                          *"
	@echo "*     TokenNames.java                                      *"
	@echo "*                                                          *"
	@echo "************************************************************"
	rm -rf ${JFlex_CUP_GENERATED_FILES} ${BIN_DIR}/*.class ${BIN_DIR}/AST/*.class
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
	@echo "*******************************************************************************"
	@echo "*                                                                             *"
	@echo "*                                                                             *"
	@echo "* [3] Use CUP to synthesize Parser.java and TokenNames.java from CUP_FILE.cup *"
	@echo "*                                                                             *"
	@echo "*                                                                             *"
	@echo "*******************************************************************************"
	$(CUP_PROGRAM) ${CUP_FLAGS} -destdir ${SRC_DIR} ${CUP_FILE}
	@echo "\n"
	@echo "********************************************************"
	@echo "*                                                      *"
	@echo "*                                                      *"
	@echo "* [4] Create *.class files from *.java files + CUP JAR *"
	@echo "*                                                      *"
	@echo "*                                                      *"
	@echo "********************************************************"
	javac -cp ${EXTERNAL_JAR_FILES} -d ${BIN_DIR} ${SRC_FILES}
	@echo "\n"
	@echo "***********************************************************"
	@echo "*                                                         *"
	@echo "*                                                         *"
	@echo "* [5] Create a JAR file from from *.class files + CUP JAR *"
	@echo "*                                                         *"
	@echo "*                                                         *"
	@echo "***********************************************************"
	jar cfm COMPILER ${MANIFEST_FILE} -C ${BIN_DIR} .
	@echo "\n"
	@echo "*****************************"
	@echo "*                           *"
	@echo "*                           *"
	@echo "* [6] Run resulting program *"
	@echo "*                           *"
	@echo "*                           *"
	@echo "*****************************"
	java -jar COMPILER ${INPUT} ${OUTPUT}
	@echo "\n"
	@echo "***************************************"
	@echo "*                                     *"
	@echo "*                                     *"
	@echo "* [7] Create a jpeg AST visualization *"
	@echo "*                                     *"
	@echo "*                                     *"
	@echo "***************************************"
	dot -Tjpeg -o${OUTPUT_DIR}/AST.jpeg ${OUTPUT_DIR}/AST_IN_GRAPHVIZ_DOT_FORMAT.txt
	@echo "\n"
	@echo "************************************************"
	@echo "*                                              *"
	@echo "*                                              *"
	@echo "* [8] Open the jpeg AST visualization with eog *"
	@echo "*                                              *"
	@echo "*                                              *"
	@echo "************************************************"
	eog ${OUTPUT_DIR}/AST.jpeg &
	@echo "*********************************************************"
	@echo "*                                                       *"
	@echo "*                                                       *"
	@echo "* [9] Create a jpeg SYMBOL TABLE visualization in steps *"
	@echo "*                                                       *"
	@echo "*                                                       *"
	@echo "*********************************************************"
	dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_0.jpeg  ${OUTPUT_DIR}/SYMBOL_TABLE_0_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_1.jpeg  ${OUTPUT_DIR}/SYMBOL_TABLE_1_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_2.jpeg  ${OUTPUT_DIR}/SYMBOL_TABLE_2_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_3.jpeg  ${OUTPUT_DIR}/SYMBOL_TABLE_3_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_4.jpeg  ${OUTPUT_DIR}/SYMBOL_TABLE_4_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_5.jpeg  ${OUTPUT_DIR}/SYMBOL_TABLE_5_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_6.jpeg  ${OUTPUT_DIR}/SYMBOL_TABLE_6_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_7.jpeg  ${OUTPUT_DIR}/SYMBOL_TABLE_7_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_8.jpeg  ${OUTPUT_DIR}/SYMBOL_TABLE_8_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_9.jpeg  ${OUTPUT_DIR}/SYMBOL_TABLE_9_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_10.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_10_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_11.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_11_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_12.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_12_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_13.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_13_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_14.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_14_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_15.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_15_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_16.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_16_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_17.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_17_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_18.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_18_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_19.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_19_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_20.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_20_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_21.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_21_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_22.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_22_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_23.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_23_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_24.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_24_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_25.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_25_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_26.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_26_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_27.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_27_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_28.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_28_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_29.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_29_IN_GRAPHVIZ_DOT_FORMAT.txt
	@dot -Tjpeg -o${OUTPUT_DIR}/SYMBOL_TABLE_30.jpeg ${OUTPUT_DIR}/SYMBOL_TABLE_30_IN_GRAPHVIZ_DOT_FORMAT.txt
	@echo "******************************************************************"
	@echo "*                                                                *"
	@echo "*                                                                *"
	@echo "* [10] Open the (first) jpeg SYMBOL TABLE visualization with eog *"
	@echo "*                                                                *"
	@echo "*                                                                *"
	@echo "******************************************************************"
	eog ${OUTPUT_DIR}/SYMBOL_TABLE_0.jpeg &
	
