# Documentation for the gridftp plugin

## Stories covered:

#6 - Set the file permissions using gridFTP plugin

## Demo
1. Preconditions- vagrant machine is up to date with issue #6, dev enviornment is enabled ("scl enable devtoolset-6 bash")
1. Create a temporary file and directory in your home folder ("mkdir /home/vagrant/TestDir/test.txt")
1. Change the permissions to read, write and execute for all ("chmod 777 /home/vagrant/TestDir/test.txt")
1. Run "ls -l /home/vagrant/TestDir/test.txt" to verify the permissions and ownership
1. Start up the gridFTP server (from build directory run "../run-gridftp-server.sh")
1. Start a python3.6 session and run the following commands:

from ftplib import FTP
ftp =FTP()
ftp.set_debuglevel(2)
ftp.connect('127.0.0.1', 5000)
ftp.login()
ftp.sendcmd('SITE SETPERMISSIONS /home/vagrant/TestDir/test.txt mode=33188;groupID=1234;userID=1234')

1. Stop the server and run "ls -lt" on the file to verify the changes have taken place