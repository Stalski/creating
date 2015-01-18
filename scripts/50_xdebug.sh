#!/bin/bash
echo "installing xdebug"
sudo pecl install xdebug
echo "xdebug installed"
echo "configuring xdebug"
sudo touch /etc/php5/apache2/conf.d/xdebug.ini
sudo echo "xdebug.default_enable=1" >> /etc/php5/apache2/conf.d/xdebug.ini
sudo echo "xdebug.show_local_vars=1" >> /etc/php5/apache2/conf.d/xdebug.ini
sudo echo "xdebug.remote_connect_back=1" >> /etc/php5/apache2/conf.d/xdebug.ini
sudo echo "xdebug.remote_autostart=1" >> /etc/php5/apache2/conf.d/xdebug.ini
sudo echo "xdebug.remote_host=192.168.50.1" >> /etc/php5/apache2/conf.d/xdebug.ini
sudo echo "xdebug.remote_enable=1" >> /etc/php5/apache2/conf.d/xdebug.ini
sudo echo "xdebug.remote_port=9000" >> /etc/php5/apache2/conf.d/xdebug.ini
sudo echo 'zend_extension = "/usr/lib/php5/20090626/xdebug.so"' >> /etc/php5/apache2/conf.d/xdebug.ini
echo "xdebug is now configured"
