#!/bin/sh

drush cc drush
drush -r /var/www cc all
drush -r /var/www cron