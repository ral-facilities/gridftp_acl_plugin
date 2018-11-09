Vagrant.configure("2") do |config|
  config.ssh.forward_agent = true  
  
  config.vm.define "machine1" do |machine1|
    machine1.vm.box = "gugek/scientific-linux-7"
    machine1.vm.box_version = "7.2.0"
    machine1.vm.synced_folder "src", "/home/vagrant/src"
    machine1.vm.synced_folder "systemTests", "/home/vagrant/systemTests"
    machine1.vm.synced_folder "dev-environment", "/home/vagrant/playbooks"
    machine1.vm.network :private_network, ip: "172.28.128.150"
      machine1.vm.hostname = "server1"
    machine1.vm.provider "virtualbox" do |vb|
      vb.memory = 1024
    end

    machine1.vm.provision "ansible_local" do |ansible|
      ansible.playbook = "dev-environment/gridftp-plugin-dev.yml"
    end
  end
						      	
  config.vm.define "machine2" do |machine2|
    machine2.vm.box = "gugek/scientific-linux-7"
    machine2.vm.box_version = "7.2.0"
    machine2.vm.synced_folder "src", "/home/vagrant/src"
    machine2.vm.network :private_network, ip: "172.28.128.151"
      machine2.vm.hostname = "server2"
    machine2.vm.provider "virtualbox" do |vb|
      vb.memory = 1024
    end
					      	
    machine2.vm.provision "ansible_local" do |ansible|
      ansible.playbook = "dev-environment/gridftp-plugin-dev.yml"
    end
  end
end
