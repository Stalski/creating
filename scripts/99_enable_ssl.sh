#! /bin/bash

# HTTPS/SSL Guudness
echo "setting up https/ssl"

SSLAPACHECONF="\n<VirtualHost *:443>
\n
\n        ServerAdmin webmaster@localhost
\n
\n        DocumentRoot /var/www
\n        <Directory />
\n                Options FollowSymLinks
\n                AllowOverride All
\n        </Directory>
\n        <Directory /var/www/>
\n                Options Indexes FollowSymLinks MultiViews
\n                AllowOverride All
\n                Order allow,deny
\n                allow from all
\n        </Directory>
\n
\n        ScriptAlias /cgi-bin/ /usr/lib/cgi-bin/
\n        <Directory "/usr/lib/cgi-bin">
\n                AllowOverride All
\n                Options +ExecCGI -MultiViews +SymLinksIfOwnerMatch
\n                Order allow,deny
\n                Allow from all
\n        </Directory>
\n
\n       ErrorLog ${APACHE_LOG_DIR}/error.log
\n
\n        # Possible values include: debug, info, notice, warn, error, crit,
\n        # alert, emerg.
\n        LogLevel warn
\n
\n        CustomLog ${APACHE_LOG_DIR}/access.log combined
\n
\n        SSLEngine on
\n        SSLCertificateFile /etc/ssl/certs/ssl-cert-snakeoil.pem
\n
\n</VirtualHost>"

# pipe https config into apache config
echo $SSLAPACHECONF >> /etc/apache2/sites-available/default

# enable ssl
a2enmod ssl

echo "https/ssl is set up, restarting apache"

# restart apache
sudo service apache2 restart
