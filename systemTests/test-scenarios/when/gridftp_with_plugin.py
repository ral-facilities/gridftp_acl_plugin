import subprocess
import os
import signal
import io
import sys
import time
import psutil


class GridftpWithPlugin:
  def __init__(self, context):
    self._context = context

  def is_shut_down(self):
    if self._context.gridftp_process is not None:
      pgrp = os.getpgid(self._context.gridftp_process.pid)
      print(pgrp)
      os.killpg(pgrp, signal.SIGTERM)
      self._context.gridftp_process = None

      #parent_pid = self._context.gridftp_process.pid
      #parent = psutil.Process(parent_pid)
      #for child in parent.children(recursive=True):  # or parent.children() for recursive=False
      #    child.kill()
      #parent.kill()


      #os.killpg(self._context.gridftp_process.pid, signal.SIGTERM)
      #self._context.gridftp_process.terminate()

      