import unittest
import time

import context

class FileInfoTests(context.BaseSystemTest):
    def test_file_contents_listed_correctly(self):
        self.given.simple_test_files_set_up()
        self.given.dms_environment().is_running()
        
        self.when.target_folder_listed('/')

        self.when.environment_is_stopped()
        self.then.web_api_log.contains('List directories in /')
        self.then.console_output.contains(r'[-wrxd]{10}[\.]? 1 [0-9a-zA-Z\s:]* test1\.txt')
        self.then.console_output.contains(r'[-wrxd]{10}[\.]? 1 [0-9a-zA-Z\s:]* test2\.txt')

        # check that no files were transferred to check the file info was listed from the web api metadata
        self.then.staging_folder.is_empty()
