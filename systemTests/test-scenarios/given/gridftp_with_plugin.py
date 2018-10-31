import subprocess
import os
import io
import sys
import time


class GridftpWithPlugin:
	def __init__(self, context):
		self._context=context

	def is_started(self):
		self._context.gridftp_process = subprocess.Popen('cd ~/src/build; ../run-gridftp-server.sh', shell=True)