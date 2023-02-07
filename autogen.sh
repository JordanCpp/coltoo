#!/bin/sh
# $Id: autogen.sh,v 1.1 2004/06/26 15:09:17 sprudl Exp $

# Remove any previously created cache files
test -w config.cache && rm config.cache

# Regenerate configuration files
aclocal
automake -a -c --foreign
autoconf

# Run configure for this platform
#./configure $*
echo "Now you are ready to run ./configure"
