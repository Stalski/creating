#!/bin/sh

echo "Setting up db"
mysql -u root -e "create database VAGRANT default character set utf8" -proot
mysql -u root -e "grant all privileges on VAGRANT.* to VAGRANT@localhost identified by 'VAGRANT'" -proot
