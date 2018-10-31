# Investigate example GridFTP plugins

## Stories covered
#2 - investigate an example GridFTP plugin

## DSI route
1. Talk through the various sources of information
1. Show the ceph plugin which has been used as a model
1. Show the openscience dsi which shows how to do a custom command
1. Show the barebones dsi in our code base
1. Show that the shared library gets built (hand over to Conor to demo the functionality)

## GridFTP alternative?
1. Talk about how development is hard and we have had discussions with Frazer about how this might be hard to maintain.
1. I've independently gone looking for alternatives and there doesn't seem to be anythign else around that provides the same distribution of load as well as security through certificates.
   - other alternatives for the large file transfer include
      - IBM Aspera FASP but this has a paid for patented implementation
      - Google QUIC, this is generally part of Chromium and used for streaming on all google services - this will likely be the big player in a few years but is not ready for production yet

1. We're planning to have a discussion tomorrow about what might need to be in an alternative and look at whether this would be a better bet or not

1. I've been working on a prototype for a segmented zero-buffer file transfer using python that only took a couple of hours - demo this.

