import subprocess
import os

class WhenSteps:
    def __init__(self, context):
        self._context = context

    def environment_is_stopped(self):
        self._context.stop_dms()

    def target_folder_listed(self, path_to_list):
        if path_to_list.startswith('/'):
            path_to_list = path_to_list.replace('/', '', 1)

        path = os.path.join(self._context.execution_folder_path, 'testing_area/target', path_to_list)
        shell_process = subprocess.Popen(
          'ls -l {}'.format(path),
          shell=True,
          stdout=self._context.console_logger.stdout_log_writer,
          stderr=self._context.console_logger.stderr_log_writer)
        shell_process.wait()

    def simple_file_is_copied(self):
        assert 1==0
        #fill out details - this should copy the test file created by given method "simple_test_file_is_setup" to /home/vagrant/systemTests/execution_space/testing_area/target/ using gridftp
        #possibly something like: os.system('globus-url-copy -v file:///home/${USER}/systemTests/execution_space/testing_area/src/testA.text ftp://localhost:5000/home/${USER}/systemTests/execution_space/testing_area/target/')