#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/ilamatveev/Desktop/speed_typing/speed_typing/build
  make -f /Users/ilamatveev/Desktop/speed_typing/speed_typing/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/ilamatveev/Desktop/speed_typing/speed_typing/build
  make -f /Users/ilamatveev/Desktop/speed_typing/speed_typing/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/ilamatveev/Desktop/speed_typing/speed_typing/build
  make -f /Users/ilamatveev/Desktop/speed_typing/speed_typing/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/ilamatveev/Desktop/speed_typing/speed_typing/build
  make -f /Users/ilamatveev/Desktop/speed_typing/speed_typing/build/CMakeScripts/ReRunCMake.make
fi

