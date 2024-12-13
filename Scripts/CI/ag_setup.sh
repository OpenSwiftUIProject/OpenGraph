#!/bin/bash

# A `realpath` alternative using the default C implementation.
filepath() {
    [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

REPO_ROOT="$(dirname $(dirname $(dirname $(filepath $0))))"

clone_checkout_ag() {
  cd $REPO_ROOT
  revision=$(Scripts/CI/get_revision.sh darwinprivateframeworks)
  cd ..
  gh repo clone OpenSwiftUIProject/DarwinPrivateFrameworks
  cd DarwinPrivateFrameworks
  git checkout --quiet $revision
}

update_ag() {
  cd $REPO_ROOT/../DarwinPrivateFrameworks
  DARWIN_PRIVATE_FRAMEWORKS_TARGET_RELEASE=2021 ./AG/update.sh
  DARWIN_PRIVATE_FRAMEWORKS_TARGET_RELEASE=2024 ./AG/update.sh
}

clone_checkout_ag
update_ag
