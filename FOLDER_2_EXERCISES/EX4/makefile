###############
# DIRECTORIES #
###############
BASEDIR = $(shell pwd)

##########
# PANDOC #
##########
PANDOC_FLAGS =           \
--variable urlcolor=blue \
--pdf-engine=xelatex

###########
# EX4.pdf #
###########
${BASEDIR}/EX4.pdf: ${BASEDIR}/EX4.md
	@pandoc ${PANDOC_FLAGS} $< -o $@

