from .log_file_steps import LogFileSteps
from .folder_steps import FolderSteps

class ThenSteps:
	def __init__(self, context):
		self._context = context

		self.console_output = LogFileSteps(context, 'console-stdout.log')
		
		self.staging_folder = FolderSteps(context, 'testing_area/staging')

	def simple_test_file_is_transferred(self):
		assert 1==0
		# should check that the file copied by "when_steps" method "simple_file_is_copied" is pasted in the correct output directory

	def contents_of_copied_file_unchanged(self):
		assert 1==0
		#check that file copied across has the same contents as the input file

	def logs_get_permissions(self):
		assert 1==0