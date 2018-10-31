# Documentation for the gridftp plugin

## Stories covered:

#3 - investigate dev process for working with gridFTP

## Demo
1. Preconditions- vagrant machine is up to date with master for provisioning and you have copied the demo-script "ftpClient.py" to a location that is accessible on the vagrant machine (e.g. src/build)
1. From within the "build" directory, start the gridFTP server: "../run-gridftp-server.sh"
1. Run "./ftpClient.py", which will call the "GETPERMISSIONS" command which we added to the dsi interface.
1. Stop the server (CTL-C) and check the logs created: "cat /usr/tmp/gridftp_acl_plugin.log"
1. open the plugin source code in an editor: "vi ../permissions_plugin" and add an extra log message for GETPERMISSIONS e.g. "logger.LogTrace("This is the updated plugin");", save these changes (ESC -> : -> wq)
1. The plugin can be updated by rerruning ninja from the build directory.
1. Restart the server and run "./ftpClient.py". Then stop the server and check the log file again. The penultimate line should have your updated log message.