#!/bin/sh

# Clear index
echo "Clearing Solr index"
drush -r /var/www solr-delete-index

# Re-index Solr
echo "Re-indexing Solr"
drush -r /var/www solr-mark-all
drush -r /var/www solr-index
drush -r /var/www cron