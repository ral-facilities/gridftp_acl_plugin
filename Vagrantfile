Vagrant.configure("2") do |config|
  config.ssh.forward_agent = true

  config.vm.define "control" do |control|
    control.vm.box = "gugek/scientific-linux-7"
    control.vm.box_version = "7.2.0"

    control.vm.synced_folder "src", "/home/vagrant/src"

    control.vm.provider "virtualbox" do |vb|
      vb.memory = 1024
    end

    control.vm.provision "ansible_local" do |ansible|
      ansible.playbook = "dev-environment/gridftp-plugin-dev.yml"
    end

  end
end