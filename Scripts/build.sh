#!/bin/zsh

# A `realpath` alternative using the default C implementation.
filepath() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

OPENGRAPH_ROOT="$(dirname $(dirname $(filepath $0)))"

cd $OPENGRAPH_ROOT

swift build
