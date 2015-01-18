# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  # General configuration, valid for all defined boxes.

  # Virtualbox tweaks.
  config.vm.provider :virtualbox do |vb|
   # Moar memory
    vb.customize ["modifyvm", :id, "--memory", "1024"]
  end

  # NFS shares
  config.vm.synced_folder "www", "/var/www", :nfs => true
  config.vm.synced_folder "db", "/home/vagrant/db", :nfs => true
  config.vm.synced_folder "scripts", "/home/vagrant/scripts", :nfs => true
  
  # https/ssl port forwarding
  config.vm.network :forwarded_port, guest: 443, host: 4444

  ## Provision
  # setup.sh will run to provide additional provisioning, see script for details
  config.vm.provision :shell, :inline => "
  sh /vagrant/scripts/setup.sh;
  "

  # the box
  config.vm.define :vagrant do |vagrant|
    vagrant.vm.box = "precise64lamp"
    vagrant.vm.box_url = "http://boxes.wunderkraut.be:8080/precise64lamp.box"
    vagrant.vm.network :private_network, ip: "192.168.50.2"
    vagrant.vm.hostname = "vagrant.loc"
  end
end
