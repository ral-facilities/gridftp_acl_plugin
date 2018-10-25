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