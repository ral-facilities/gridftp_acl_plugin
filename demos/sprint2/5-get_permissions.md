# Documentation for the gridftp plugin

## Stories covered:

#5 - Get the permissions from a file

## Demo
1. Preconditions- code base is up-to-date with issue #5, demo scipt ftpClient.py is accessible on the server
1. Once branch 5 has been checked out, re build the code (from within the build directory run "cmake3 -GNinja ../", followed by "ninja")
1. Run the gridFTP server in the background "../run-gridftp-server.sh &" or from another ssh session
1. Run the ftpClient script, which will get the permissions on the "test" directory in the "src" directory. This will return "250 PERMISSIONS: mode: 16895 groupID: 1000 userID: 1000". This is the return value for a successful call. Mode is the integer value when converted into an octal this refers to: 40777 (40 refers to a directory followed by permissions). You can confirm these permissions by using "ls -ld ../test" (run "id" to check you user and groups and which numbers they refer to)