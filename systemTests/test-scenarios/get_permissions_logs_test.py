import unittest
import time

import context

class GetPermissionsLogs(context.BaseSystemTest):                      #class would need a "Test" prefix if it did not inhrit the __init__ method
    def test_Get_permissions_logs(self):                   #this needs the "test_" prefix to get picked up by pytest
        self.given.gridftp_plugin_server().is_started()
        self.given.an_ftp_client_is_connected()
        
        self.when.get_permissions_called()
        self.when.gridftp_plugin_server().is_shut_down()

        #self.then.logs_get_permissions()
        #delete the files created and copied across (if not already done in teardown)