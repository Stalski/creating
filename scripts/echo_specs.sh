#!/bin/sh

echo ""
echo ""
echo "##     ##    ###     ######   ########     ###    ##    ## ########"
echo "##     ##   ## ##   ##    ##  ##     ##   ## ##   ###   ##    ##   "
echo "##     ##  ##   ##  ##        ##     ##  ##   ##  ####  ##    ##   "
echo "##     ## ##     ## ##   #### ########  ##     ## ## ## ##    ##   "
echo " ##   ##  ######### ##    ##  ##   ##   ######### ##  ####    ##   "
echo "  ## ##   ##     ## ##    ##  ##    ##  ##     ## ##   ###    ##   "
echo "   ###    ##     ##  ######   ##     ## ##     ## ##    ##    ##   "
echo ""
echo ">> Precise64Lamp Vagrant box by WK BE, stack specs & info follow <<"
echo ""
echo ""
# apache info
echo "# Apache info"
which apache2
apache2 -v
echo ""
# mysql info
echo "# MySQL info"
which mysql
mysql -V
echo ""
# php info
echo "# PHP info"
which php
php -v
echo ""
# postfix info
echo "# Postfix info"
which postfix
postconf mail_version
echo ""
# java info
echo "# Java info"
java -version
echo ""
# drush info
echo "# Drush info"
which drush
drush version
echo ""
# xhprof info
echo "# xhprof info"
echo "installed, enabled and configured if you're running a D7 codebase"
echo "look for the link on the bottom left of the page, or go to /admin/reports/xhprof"
echo ""
