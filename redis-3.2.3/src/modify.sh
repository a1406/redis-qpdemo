#!/bin/sh
git log  4fb1f2...  --raw | grep "^:[0-9]*.*" | grep -v "README.md" |  sed 's/^.*redis-3\.2\.3\/src\/\(.*\)/\1/g' 
