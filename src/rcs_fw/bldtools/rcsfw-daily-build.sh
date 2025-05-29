#!/bin/bash
#
set -xe

# Script to build, package and publish RCS firmware for daily builds.

SCRIPT_DIR=$(dirname "$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )")

cd $SCRIPT_DIR

source src.env Austin
git submodule update --init --recursive
make all doxygen package publish
