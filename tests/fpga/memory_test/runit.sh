#!/bin/sh
# 
# Copyright 2011-2015 Jeff Bush
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 

/usr/local/llvm-nyuzi/bin/clang -o memory_test.elf memory_test.S
/usr/local/llvm-nyuzi/bin/elf2hex -o memory_test.hex memory_test.elf
../../../bin/serial_boot $SERIAL_PORT memory_test.hex

