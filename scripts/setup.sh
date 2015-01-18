#!/bin/sh

# Checking if there is a .provisioncheck file
echo "Checking for .provisioncheck file..."

if [ -e "/home/vagrant/.provisioncheck" ]
then
  # Skipping provisioning to prevent overwriting db changes
  echo "The .provisioncheck file already exists."
  echo "Skipping provisioning..."
  echo "All done..."
  exit
fi

# no .provisioncheck, run provisioning
echo "No .provisioncheck file exists, provisioning..."

# Execute all scripts in the 'scripts' folder.
PREFIX='/home/vagrant/scripts/'
for SCRIPT in `ls $PREFIX`
do

  if [ $SCRIPT != "setup.sh" ]
  then

    echo "Executing: $PREFIX$SCRIPT"
    sh $PREFIX$SCRIPT

  fi

done

#create .provisioncheck
echo "Creating a .provisioncheck file."
touch .provisioncheck

echo "All done..."
