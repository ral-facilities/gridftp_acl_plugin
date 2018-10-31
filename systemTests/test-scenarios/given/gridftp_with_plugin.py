import subprocess
import os
import io
import sys
import time


class GridftpWithPlugin:
  def __init__(self, context):
    self._context=context

  def is_started(self):
    self._context.gridftp_process = subprocess.Popen(['../run-gridftp-server.sh'], stdout=subprocess.PIPE, 
                       shell=True, preexec_fn=os.setsid, cwd=r'/home/vagrant/src/build')