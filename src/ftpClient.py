#!/usr/bin/env python
import ftplib
from ftplib import FTP

host = 'localhost'
port = 5000

ftp = FTP()
ftp.connect(host, port)
ftp.login()

# Check that you are able to send commands (print working dir)
ftp.sendcmd('PWD')

# Send a custom registered command
#ftp.sendcmd('SITE')
