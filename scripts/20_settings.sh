#!/bin/sh

# Settings for Drupal 6
# Check the Memcache config if the module is not in /sites/all/modules/contrib/
D6SETTINGS="<?php

 \$db_url = 'mysql://VAGRANT:VAGRANT@localhost/VAGRANT';
 # \$db_prefix = ;

 \$update_free_access = FALSE;

 ini_set('arg_separator.output',     '&');
 ini_set('magic_quotes_runtime',     0);
 ini_set('magic_quotes_sybase',      0);
 ini_set('session.cache_expire',     200000);
 ini_set('session.cache_limiter',    'none');
 ini_set('session.cookie_lifetime',  2000000);
 ini_set('session.gc_maxlifetime',   200000);
 ini_set('session.save_handler',     'user');
 ini_set('session.use_cookies',      1);
 ini_set('session.use_only_cookies', 1);
 ini_set('session.use_trans_sid',    0);
 ini_set('url_rewriter.tags',        '');

 # \$conf = array(
 #   'site_name' => 'My Drupal site',
 #   'theme_default' => 'minnelli',
 #   'anonymous' => 'Visitor',

 #   'maintenance_theme' => 'minnelli',

 # Memcached configuration
 \$conf['cache_inc'] = './sites/all/modules/contrib/memcache/memcache.inc';
 \$conf['memcache_servers'] = array(
          '127.0.0.1:11211' => 'default',
 );

 # Varnish reverse proxy on localhost
 \$conf['reverse_proxy'] = TRUE;
 \$conf['reverse_proxy_addresses'] = array('127.0.0.1');

 # General caching settings
 \$conf['cache'] = 1;
 \$conf['block_cache'] = 1;
 \$conf['cache_lifetime'] = 600;
 \$conf['page_cache_maximum_age'] = 600;
 \$conf['page_compression'] = 1;
 \$conf['preprocess_css'] = 1;
 \$conf['preprocess_js'] = 1;

error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

ini_set('memory_limit', '128M');"

# Settings for Drupal 7
D7SETTINGS="<?php

\$databases = array();
\$databases['default']['default'] = array(
  'driver' => 'mysql',
  'database' => 'VAGRANT',
  'username' => 'VAGRANT',
  'password' => 'VAGRANT',
  'host' => 'localhost',
  'prefix' => '',
);

\$update_free_access = FALSE;
\$drupal_hash_salt = '';
# $base_url = 'http://www.example.com';  // NO trailing slash!

/**
 * PHP settings:
 */
ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 100);
ini_set('session.gc_maxlifetime', 200000);
ini_set('session.cookie_lifetime', 2000000);
# ini_set('pcre.backtrack_limit', 200000);
# ini_set('pcre.recursion_limit', 200000);

# \$cookie_domain = '.example.com';
# \$conf['site_name'] = 'My Drupal site';
# \$conf['theme_default'] = 'garland';
# \$conf['anonymous'] = 'Visitor';
# \$conf['maintenance_theme'] = 'bartik';

/**
 * Fast 404 pages:
 */
\$conf['404_fast_paths_exclude'] = '/\/(?:styles)\//';
\$conf['404_fast_paths'] = '/\.(?:txt|png|gif|jpe?g|css|js|ico|swf|flv|cgi|bat|pl|dll|exe|asp)$/i';
\$conf['404_fast_html'] = '<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML+RDFa 1.0//EN\" \"http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\"><head><title>404 Not    Found</title></head><body><h1>Not Found</h1><p>The requested URL \"@path\" was not found on this server.</p></body></html>';
# drupal_fast_404();

# \$conf['proxy_user_agent'] = ;
# \$conf['proxy_exceptions'] = array('127.0.0.1', 'localhost');

error_reporting(2147483647);
\$conf['error_level'] = 2;
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

ini_set('memory_limit', '128M');"

SETTINGSPATH='/var/www/sites/default/settings.php'

echo "Setting correct permissions"
/bin/chmod -R 0777 /var/www/sites/default

if [ -e "$SETTINGSPATH" ]
then

  echo "Settings file already found. Moving current settings file to 'settings.php.backup'"
  /bin/mv $SETTINGSPATH $SETTINGSPATH.backup

fi

echo "Creating settings file for Vagrant box"
# Check which Drupal version it is, so we create the correct settings file.
DRVE=`drush -r /var/www status | grep 'Drupal version' | sed 's/.*\([0-9]\)\..*$/\1/'`
if [ "$DRVE" = 7 ]
then

  echo "Found a Drupal 7 website, creating settings file ..."
  /bin/echo "$D7SETTINGS" > $SETTINGSPATH

elif [ "$DRVE" = 6 ]
then

  echo "Found a Drupal 6 website, creating settings file ..."
  /bin/echo "$D6SETTINGS" > $SETTINGSPATH

fi
