/*
 Derived from source code of TrueCrypt 7.1a, which is
 Copyright (c) 2008-2012 TrueCrypt Developers Association and which is governed
 by the TrueCrypt License 3.0.

 Modifications and additions to the original source code (contained in this file)
 and all other portions of this file are Copyright (c) 2013-2025 AM Crypto
 and are governed by the Apache License 2.0 the full text of which is
 contained in the file License.txt included in VeraCrypt binary and source
 code distribution packages.
*/

#ifndef TC_HEADER_Core_CoreSolaris
#define TC_HEADER_Core_CoreSolaris

#include "System.h"
#include "Core/Unix/CoreUnix.h"

namespace VeraCrypt
{
	class CoreSolaris : public CoreUnix
	{
	public:
		CoreSolaris ();
		virtual ~CoreSolaris ();

		virtual HostDeviceList GetHostDevices (bool pathListOnly = false) const;

	protected:
		virtual DevicePath AttachFileToLoopDevice (const FilePath &filePath, bool readOnly) const;
		virtual void DetachLoopDevice (const DevicePath &devicePath) const;
		virtual MountedFilesystemList GetMountedFilesystems (const DevicePath &devicePath = DevicePath(), const DirectoryPath &mountPoint = DirectoryPath()) const;
		virtual void MountFilesystem (const DevicePath &devicePath, const DirectoryPath &mountPoint, const string &filesystemType, bool readOnly, const string &systemMountOptions) const;

	private:
		CoreSolaris (const CoreSolaris &);
		CoreSolaris &operator= (const CoreSolaris &);
	};
}

#endif // TC_HEADER_Core_CoreSolaris
