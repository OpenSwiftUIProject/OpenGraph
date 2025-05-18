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

sed -i '' '1,5d' ./template.swiftinterface
sed -i '' '1i\
@_exported public import AttributeGraph
' ./template.swiftinterface
sed -i '' 's/OpenGraph_SPI\.//g' ./template.swiftinterface
sed -i '' 's/OpenGraph/AttributeGraph/g' ./template.swiftinterface
sed -i '' 's/OG/AG/g' ./template.swiftinterface

echo "Generated template.swiftinterface successfully"

