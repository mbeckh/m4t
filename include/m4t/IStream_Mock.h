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

#pragma once

#include <gmock/gmock.h>

#include <objbase.h>
#include <objidl.h>
#include <windows.h>

#include <cstring>
#include <cwchar>
#include <new>
#include <type_traits>  // IWYU pragma: keep

namespace m4t {

/// @brief Mock class for `IStream`.
class IStream_Mock : public IStream {  // NOLINT(readability-identifier-naming)
public:
	IStream_Mock() noexcept;
	IStream_Mock(const IStream_Mock&) = delete;
	IStream_Mock(IStream_Mock&&) = delete;
	virtual ~IStream_Mock() noexcept;

public:
	IStream_Mock& operator=(const IStream_Mock&) = delete;
	IStream_Mock& operator=(IStream_Mock&&) = delete;

public:
	// IUnknown
	MOCK_METHOD(HRESULT, QueryInterface, (REFIID riid, void** ppvObject), (Calltype(__stdcall), override));  // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(ULONG, AddRef, (), (Calltype(__stdcall), override));                                         // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(ULONG, Release, (), (Calltype(__stdcall), override));                                        // NOLINT(misc-non-private-member-variables-in-classes)

public:
	// ISequentialStream
	MOCK_METHOD(HRESULT, Read, (void* pv, ULONG cb, ULONG* pcbRead), (Calltype(__stdcall), override));            // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(HRESULT, Write, (const void* pv, ULONG cb, ULONG* pcbWritten), (Calltype(__stdcall), override));  // NOLINT(misc-non-private-member-variables-in-classes)

public:
	// IStream
	MOCK_METHOD(HRESULT, Seek, (LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition), (Calltype(__stdcall), override));                   // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(HRESULT, SetSize, (ULARGE_INTEGER libNewSize), (Calltype(__stdcall), override));                                                              // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(HRESULT, CopyTo, (IStream * pstm, ULARGE_INTEGER cb, ULARGE_INTEGER* pcbRead, ULARGE_INTEGER* pcbWritten), (Calltype(__stdcall), override));  // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(HRESULT, Commit, (DWORD grfCommitFlags), (Calltype(__stdcall), override));                                                                    // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(HRESULT, Revert, (), (Calltype(__stdcall), override));                                                                                        // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(HRESULT, LockRegion, (ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType), (Calltype(__stdcall), override));                       // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(HRESULT, UnlockRegion, (ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType), (Calltype(__stdcall), override));                     // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(HRESULT, Stat, (STATSTG * pstatstg, DWORD grfStatFlag), (Calltype(__stdcall), override));                                                     // NOLINT(misc-non-private-member-variables-in-classes)
	MOCK_METHOD(HRESULT, Clone, (IStream * *ppstm), (Calltype(__stdcall), override));                                                                         // NOLINT(misc-non-private-member-variables-in-classes)
};

/// @brief Default action for `IStream::Stat`.
ACTION_P(IStream_Stat, wszName) {  // NOLINT(cppcoreguidelines-special-member-functions, misc-non-private-member-variables-in-classes)
	static_assert(std::is_same_v<STATSTG*, arg0_type>);
	static_assert(std::is_convertible_v<wszName_type, const wchar_t*>);

	if ((wszName)) {
		const wchar_t* const wsz = (wszName);
		const size_t cch = wcslen(wsz) + 1;
		wchar_t* const pName = static_cast<wchar_t*>(CoTaskMemAlloc(cch * sizeof(wchar_t)));
		if (!pName) [[unlikely]] {
			throw std::bad_alloc();
		}
		std::memcpy(pName, wsz, cch * sizeof(wchar_t));
		arg0->pwcsName = pName;
	} else {
		arg0->pwcsName = nullptr;
	}

	return S_OK;
}

}  // namespace m4t
