import os
from .basic_gridftp_environment import BasicGridftpEnvironment

class GivenSteps:
    def __init__(self, context):
        self._context = context
        self._basic_gridftp_environment = BasicGridftpEnvironment(context)

    def _write_test_file(self, file_name, content):
        with open(os.path.join(self._context.execution_folder_path, 'testing_area/src', file_name), 'w') as file:
            file.write(content)

    def gridftp_basic_server(self):                 
        return self._basic_gridftp_environment

    def simple_test_file_is_setup(self):
        self._write_test_file('testA.txt', 'example test content A')