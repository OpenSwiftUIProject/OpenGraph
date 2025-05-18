#!/bin/zsh

# A `realpath` alternative using the default C implementation.
filepath() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

OPENGRAPH_ROOT="$(dirname $(dirname $(filepath $0)))"

cd $OPENGRAPH_ROOT

# Build the swiftinterface file
./Scripts/build_swiftinterface.sh

# Copy to template file
cp .build/debug/OpenGraph.build/OpenGraph.swiftinterface ./template.swiftinterface

# Process the template file
# 1. Remove the first 5 lines
# 2. Remove all references of "OpenGraph_SPI."
# 3. Replace all references of "OpenGraph" to "AttributeGraph"
# 4. Replace all references of "OG" to "AG"
sed -i '' '1,5d' ./template.swiftinterface
sed -i '' 's/OpenGraph_SPI\.//g' ./template.swiftinterface
sed -i '' 's/OpenGraph/AttributeGraph/g' ./template.swiftinterface
sed -i '' 's/OG/AG/g' ./template.swiftinterface

echo "Generated template.swiftinterface successfully"

