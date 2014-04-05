#!/usr/bin/env ruby

require 'rubygems'        # if you use RubyGems
require 'daemons'

# Initialize the app while we're not a daemon
init()

# Become a daemon
Daemons.daemonize

# The server loop
loop {
  conn = accept_conn()
  serve(conn)
}
