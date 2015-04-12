#
# Copyright 2013-2015 Comcast Cable Communications Management, LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
{
  "targets": [
    {
      "target_name": "xqjs",
      "include_dirs": [
#        "<!(node -e \"console.log(require('path').dirname(require.resolve('libxmljs')))\")",
#        "<!(node -e \"var p = require('path'); console.log(p.join(p.dirname(require.resolve('libxmljs')),'src'))\")",
        "<!(node -e \"require('nan')\")",
        "deps/libxq"
      ],
      "sources": [
        "ext/xqjs.cpp",
#        "ext/xQWrapper.cpp"
        "ext/CharacterData.cpp",
        "ext/Document.cpp",
        "ext/Element.cpp",
        "ext/Node.cpp"
      ],
      "dependencies": [
        "deps/libxml2.gyp:xml2",
        "deps/libxq/libxq.gyp:xq"
      ]
    }
  ]
}
