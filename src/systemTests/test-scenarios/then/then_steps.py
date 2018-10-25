from .log_file_steps import LogFileSteps
from .folder_steps import FolderSteps

class ThenSteps:
    def __init__(self, context):
        self._context = context

        self.web_api_log = LogFileSteps(context, 'dms-web-api.log')
        self.fuse_log = LogFileSteps(context, 'dms_fuse_client.log')
        self.console_output = LogFileSteps(context, 'console-stdout.log')

        self.staging_folder = FolderSteps(context, 'testing_area/staging')
