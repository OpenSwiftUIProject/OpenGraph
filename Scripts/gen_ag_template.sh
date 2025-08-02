#!/bin/zsh

# A `realpath` alternative using the default C implementation.
filepath() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

gen_interface() {
  swift build -c release -Xswiftc -emit-module-interface -Xswiftc -enable-library-evolution -Xswiftc -no-verify-emitted-module-interface -Xswiftc -package-name -Xswiftc OpenGraph -Xswiftc -Osize

  mkdir -p .ag_template
  cp .build/release/Modules/OpenGraph.swiftinterface .ag_template/template.swiftinterface

  sed -i '' '1,4d' .ag_template/template.swiftinterface
  sed -i '' 's/@_exported public import OpenGraphCxx/@_exported public import AttributeGraph/g' .ag_template/template.swiftinterface
  sed -i '' 's/OpenGraphCxx\.//g' .ag_template/template.swiftinterface
  sed -i '' 's/OpenGraph/AttributeGraph/g' .ag_template/template.swiftinterface
  sed -i '' 's/OPENGRAPH/ATTRIBUTEGRAPH/g' .ag_template/template.swiftinterface
  sed -i '' 's/OG/AG/g' .ag_template/template.swiftinterface

  echo "Generated template.swiftinterface successfully"
}

gen_header() {
  mkdir -p .ag_template/Headers
  
  cp -r Sources/OpenGraphCxx/include/OpenGraph/* .ag_template/Headers/
  
  # Rename files from OGxx to AGxx and OpenGraphxx to AttributeGraphxx
  find .ag_template/Headers -name "OG*" -type f | while read file; do
    new_name=$(echo "$file" | sed 's/OG/AG/g')
    mv "$file" "$new_name"
  done
  
  find .ag_template/Headers -name "OpenGraph*" -type f | while read file; do
    new_name=$(echo "$file" | sed 's/OpenGraph/AttributeGraph/g')
    mv "$file" "$new_name"
  done
  
  # Update content in all header files
  find .ag_template/Headers -name "*.h" -type f | while read file; do
    sed -i '' 's/OpenGraphCxx/AttributeGraph/g' "$file"
    sed -i '' 's/OpenGraph/AttributeGraph/g' "$file"
    sed -i '' 's/OPENGRAPH/ATTRIBUTEGRAPH/g' "$file"
    sed -i '' 's/OG/AG/g' "$file"
  done
  
  echo "Generated template headers successfully"
}

OPENGRAPH_ROOT="$(dirname $(dirname $(filepath $0)))"

cd $OPENGRAPH_ROOT

gen_interface
gen_header
