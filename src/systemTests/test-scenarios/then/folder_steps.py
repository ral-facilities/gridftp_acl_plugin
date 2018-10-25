import os

class FolderSteps:
    def __init__(self, context, folder_name):
        self._context = context
        self._folder_name = os.path.join(context.execution_folder_path, folder_name)

    def is_empty(self):
        assert len(os.listdir(self._folder_name)) == 0