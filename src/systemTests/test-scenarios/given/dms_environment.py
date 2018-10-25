import subprocess
import os
import io
import sys
import time


class DmsEnvironment:
    def __init__(self, context):
        self._context = context
   
    def add_configuration_file(self):
        src_folder = os.path.abspath(self._context.execution_folder_path + '/testing_area/src')
        staging_folder = os.path.abspath(self._context.execution_folder_path + '/testing_area/staging')
        logging_folder = os.path.abspath(self._context.execution_folder_path + '/logs/')

        file_contents = '[Settings]\n' \
                        'AdapterType = dev\n' \
                        'SourceFolder = {}\n' \
                        'TargetFolder = {}\n' \
                        'UpdateInterval = 1\n' \
                        'LogFolderLocation = {}\n' \
                        '\n' \
                        '[Cache Adapters]\n' \
                        'Adapters = on_demand\n' \
                        '\n' \
                        '[Security]\n' \
                        'Authentication = None\n'.format(src_folder, staging_folder, logging_folder)
        
        with open(self._context.execution_folder_path + '/web-api/configuration.ini','w') as file:
            file.write(file_contents)

    def add_fuse_configuration(self):
        logging_folder = os.path.join(self._context.execution_folder_path, 'logs/')

        file_contents = '{' \
                        '  "logFileLocation": "' + logging_folder + '",' \
                        '  "logLevel": "trace",' \
                        '  "webApiAddress": "http://localhost:8080",' \
                        '  "updateIntervalInSeconds" : 1,' \
                        '  "Authentication": "None"' \
                        '}'
        with open(self._context.execution_folder_path + '/dms-fuse-client/dms-settings.json','w') as file:
            file.write(file_contents)

    def is_running(self):
        self.add_configuration_file()
        self.add_fuse_configuration()

        path_of_file = os.path.dirname(os.path.realpath(__file__))
        web_api_script = path_of_file + '/runSystemTestWebApi.sh'
        web_api_path = self._context.execution_folder_path + '/web-api/DMSWebApi'

        self._context.web_api_process = subprocess.Popen(
          [web_api_script, web_api_path],
          stdout=self._context.web_api_process_logger.stdout_log_writer,
          stderr=self._context.web_api_process_logger.stderr_log_writer,
          preexec_fn=os.setsid)

        # let the web api start up properly
        time.sleep(3)

        # start the fuse client
        fuse_client_script = path_of_file + '/runSystemTestFuseClient.sh'
        fuse_path = self._context.execution_folder_path + '/dms-fuse-client'
        staging_folder = os.path.abspath(self._context.execution_folder_path + '/testing_area/staging')
        target_folder = os.path.abspath(self._context.execution_folder_path + '/testing_area/target')

        self._context.fuse_client_process = subprocess.Popen(
          [fuse_client_script, fuse_path, staging_folder, target_folder],
          stdout=self._context.fuse_process_logger.stdout_log_writer,
          stderr=self._context.fuse_process_logger.stderr_log_writer,
          preexec_fn=os.setsid)

        # let the fuse client initialize too
        time.sleep(1)

