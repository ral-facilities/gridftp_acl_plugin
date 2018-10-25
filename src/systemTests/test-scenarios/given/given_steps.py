import os
from .dms_environment import DmsEnvironment

class GivenSteps:
    def __init__(self, context):
        self._context = context
        self._dms_environment = DmsEnvironment(context)

    def dms_environment(self):
        return self._dms_environment

    def simple_test_files_set_up(self):
        self._write_test_file('test1.txt', 'example content 1')
        self._write_test_file('test2.txt', 'example content 2')

    def _write_test_file(self, file_name, content):
        with open(os.path.join(self._context.execution_folder_path, 'testing_area/src', file_name), 'w') as file:
            file.write(content)
