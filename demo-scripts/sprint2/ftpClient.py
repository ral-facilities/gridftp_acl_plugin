#!/usr/bin/python
'''
Demo script to set up a python ftp client, which
connects to a gridftp server set up in anonymous mode using:
globus-gridftp-server -control-interface 127.0.0.1 -aa -p 5000
'''
import ftplib
from ftplib import FTP

host = 'localhost'
port = 5000

ftp = FTP()
ftp.set_debuglevel(2)
ftp.connect(host, port)
ftp.login()

# Check that you are able to send commands (print working dir)
print('Send command to print working dir to gridFTP server...')
print('Server returned: ')
print('\t' + ftp.sendcmd('PWD'))

print('\t' + ftp.sendcmd('SITE GETPERMISSIONS test'))

# Send a custom registered command
#ftp.sendcmd('SITE', args)
