#!/bin/sh

CONF='/opt/solr/core0/conf/'

echo "Checking Solr requirements ..."

# Check if we can find an Apache Solr module
SOLR_MODULE=`sudo /usr/bin/find /var/www/sites/ -name apachesolr | head -1`
if [ ! -e "$SOLR_MODULE" ]
then

  echo "No Apache Solr module found, make sure it is installed!"
  exit 1

fi

echo "Found Apache Solr in: $SOLR_MODULE"

SOLR_CONFIG=`sudo /usr/bin/find $SOLR_MODULE -name solr-3.x | head -1`
if [ ! -e "$SOLR_CONFIG" ]
then

  echo "No Apache Solr configuration found, using default config!"
  
else 

  echo "Found configuration files in $SOLR_CONFIG"

  # Copy the relevant configuration files
  echo "Copying configuration files ..."
  sudo /bin/cp $SOLR_CONFIG/*.txt $CONF
  sudo /bin/cp $SOLR_CONFIG/*.xml $CONF
  
fi

# Use Vagrant Solr
echo "Setting Drupal Solr environment to vagrant"
drush -r /var/www solr-set-env-url http://192.168.50.2:8081/solr/core0

# Restart Tomcat/Solr
echo "Restarting Jetty Solr service"
sudo service jetty restart
