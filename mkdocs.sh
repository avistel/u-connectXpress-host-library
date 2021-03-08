#!/bin/bash
set -e

rm -rf html
doxygen | grep -v ...\$
