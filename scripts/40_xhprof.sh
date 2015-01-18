#!/bin/bash

echo "downloading & enabling the xhprof Drupal module"
drush -r /var/www dl -y XHProf
drush -r /var/www en -y xhprof

echo "configuring the xhprof Drupal module"
drush -r /var/www vset -y xhprof_default_class XHProfRunsFile
drush -r /var/www vset -y xhprof_disable_admin_paths 0
drush -r /var/www vset -y xhprof_enabled 1

echo "done with xhprof"
cd
