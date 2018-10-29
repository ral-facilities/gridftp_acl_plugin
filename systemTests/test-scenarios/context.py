import os
import signal
import io
import shutil
import unittest
import time
import pytest

from given.given_steps import GivenSteps
from when.when_steps import WhenSteps
from then.then_steps import ThenSteps
from tools.process_logger import ProcessLogger

class SystemTestContext:
    def __init__(self):
        self.execution_folder_path = os.path.abspath(os.path.dirname(os.path.realpath(__file__)) + '/../execution_space/')

        self.console_logger = ProcessLogger('console')

    def clean_up(self):
        print('cleaning up test')
        self.console_logger.clean_up()


class BaseSystemTest(unittest.TestCase):
    @pytest.fixture(autouse=True)
    def setup(self, request):
        print("setting up test")

        self.context = SystemTestContext()

        self._clean_up_working_folders()
        self._set_up_loggers()

        self.given = GivenSteps(self.context)
        self.when = WhenSteps(self.context)
        self.then = ThenSteps(self.context)

        request.addfinalizer(self.context.clean_up)

    def _set_up_loggers(self):
        self.context.console_logger.set_up()

    def _clean_up_working_folders(self):
        # clear out the old logs
        shutil.rmtree(self.context.execution_folder_path + '/logs')
        os.makedirs(self.context.execution_folder_path + '/logs')

        shutil.rmtree(self.context.execution_folder_path + '/testing_area')
        os.makedirs(self.context.execution_folder_path + '/testing_area/src')
        os.makedirs(self.context.execution_folder_path + '/testing_area/staging')
        os.makedirs(self.context.execution_folder_path + '/testing_area/target')

