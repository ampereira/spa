#!/bin/sh

####################################
###### Configure the profiler ######
####################################

# KBest threshold (if applicable) - between 0 and 1
THRESHOLD = 0.05
# KBest k value
K = 3
# Minimum of KBest runs
MIN = 4
# Maximum of KBest runs
MAX = 4
# Output filename, without extension
FILENAME = "output"
# Report mode - csv or verbose
REPORT = "verbose"
# Script that executes the application
RUNSCRIPT = "test.sh"

# Chose the profiler
ruby kbest.rb $THRESHOLD $K $MIN $MAX $FILENAME $REPORT $RUNSCRIPT