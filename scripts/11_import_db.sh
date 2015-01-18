#!/bin/sh

# get latest db dump
LATESTDB=`ls -t /home/vagrant/db | grep .sql | head -1`

echo "Importing latest db, $LATESTDB"
mysql -u VAGRANT -pVAGRANT VAGRANT < /home/vagrant/db/$LATESTDB
