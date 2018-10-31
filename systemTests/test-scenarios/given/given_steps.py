import os
import ftplib
from ftplib import FTP

from .basic_gridftp_environment import BasicGridftpEnvironment
from .gridftp_with_plugin import GridftpWithPlugin

class GivenSteps:
    def __init__(self, context):
        self._context = context
        self._basic_gridftp_environment = BasicGridftpEnvironment(context)
        self._gridftp_with_plugin = GridftpWithPlugin(context)

    def _write_test_file(self, file_name, content):
        with open(os.path.join(self._context.execution_folder_path, 'testing_area/src', file_name), 'w') as file:
            file.write(content)

    def gridftp_basic_server(self):                 
        return self._basic_gridftp_environment

    def simple_test_file_is_setup(self):
        self._write_test_file('testA.txt', 'example test content A')

    def gridftp_plugin_server(self):
        return self._gridftp_with_plugin

    def an_ftp_client_is_connected(self):
        host = 'localhost'
        port = 5000
        self._context.ftp_client = FTP()
        self._context.ftp_client.set_debuglevel(2)
        self._context.ftp_client.connect(host, port)
        self._context.ftp_client.login()