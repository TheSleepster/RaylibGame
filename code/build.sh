#!/bin/bash
bear --output "../misc/compile_commands.json" -- make -k -B SILENT=@ DEBUG=1
