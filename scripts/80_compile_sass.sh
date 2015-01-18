#!/bin/sh

# Checking for wundertheme location
echo "Searching for Wundertheme"
WUNDERTHEME=`sudo /usr/bin/find /var/www/sites/ -name wundertheme | head -1`
if [ ! -e "$WUNDERTHEME" ]
then

  echo "No Wundertheme found!"
  exit 1

fi

echo "Found Wundertheme in $WUNDERTHEME"
echo "Compiling Wundertheme sass"
compass compile --force --environment=development --output-style=expanded $WUNDERTHEME
echo "Wundertheme sass compiled"
