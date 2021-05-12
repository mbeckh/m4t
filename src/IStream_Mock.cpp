/*
Copyright 2019 Michael Beckh

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/// @file

#include "m4t/IStream_Mock.h"

namespace m4t {

// cf. googlemock docs on "making the compilation faster"
IStream_Mock::IStream_Mock() noexcept = default;
IStream_Mock::~IStream_Mock() noexcept = default;

}  // namespace m4t
