LD_LIBRARY_PATH="$(pwd)"
export LD_LIBRARY_PATH

echo $LD_LIBRARY_PATH

sudo globus-gridftp-server -control-interface 127.0.0.1 -aa -p 5000 -dsi permissions_plugin -d ALL -debug
