#!/usr/bin/env bash

python_file="/table_utils.py"
script_base_path="$( cd "$(dirname $(readlink -f ${BASH_SOURCE[0]}))" && pwd)"
python_file=$script_base_path$python_file

`which python3` "$python_file" "$@"
