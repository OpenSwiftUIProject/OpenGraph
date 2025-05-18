#!/bin/zsh

# A `realpath` alternative using the default C implementation.
filepath() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

OPENGRAPH_ROOT="$(dirname $(dirname $(filepath $0)))"

cd $OPENGRAPH_ROOT

swift build -c release -Xswiftc -emit-module-interface -Xswiftc -enable-library-evolution -Xswiftc -no-verify-emitted-module-interface -Xswiftc -package-name -Xswiftc OpenGraph -Xswiftc -Osize

cp .build/release/Modules/OpenGraph.swiftinterface ./template.swiftinterface

sed -i '' '1,4d' ./template.swiftinterface
sed -i '' 's/@_exported public import AttributeGraph/@_exported public import OpenGraph_SPI/g' ./template.swiftinterface
sed -i '' 's/OpenGraph_SPI\.//g' ./template.swiftinterface
sed -i '' 's/OpenGraph/AttributeGraph/g' ./template.swiftinterface
sed -i '' 's/OG/AG/g' ./template.swiftinterface

echo "Generated template.swiftinterface successfully"

