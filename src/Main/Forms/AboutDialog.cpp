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

#include "System.h"
#include "Volume/Version.h"
#include "Main/Application.h"
#include "Main/GraphicUserInterface.h"
#include "Main/Resources.h"
#include "AboutDialog.h"

namespace VeraCrypt
{
	AboutDialog::AboutDialog (wxWindow* parent) : AboutDialogBase (parent)
	{
		LogoBitmap->SetBitmap (Resources::GetTextualLogoBitmap());

		wxFont versionStaticTextFont = VersionStaticText->GetFont();
		versionStaticTextFont.SetWeight (wxFONTWEIGHT_BOLD);
		VersionStaticText->SetFont (versionStaticTextFont);

		wstring versionStr = StringConverter::ToWide (Version::String());
#ifdef VC_MACOSX_FUSET
		versionStr += L" (FUSE-T build)";
#endif
		VersionStaticText->SetLabel (Application::GetName() + L" " + versionStr);
		CopyrightStaticText->SetLabel (TC_STR_RELEASED_BY);
		WebsiteHyperlink->SetLabel (L"amcrypto.jp");

		CreditsTextCtrl->SetMinSize (wxSize (
			Gui->GetCharWidth (CreditsTextCtrl) * 70,
			Gui->GetCharHeight (CreditsTextCtrl) * 6
#ifdef TC_WINDOWS
			- 5
#else
			- 11
#endif
			));

		Layout();
		Fit();
		Center();

		CreditsTextCtrl->ChangeValue (
			L"Portions of this software are based in part on the works of the following people: "
			L"Paul Le Roux, "
			L"Bruce Schneier, John Kelsey, Doug Whiting, David Wagner, Chris Hall, Niels Ferguson, "
			L"Lars Knudsen, Ross Anderson, Eli Biham, "
			L"Joan Daemen, Vincent Rijmen, "
			L"Jean-loup Gailly, Mark Adler, "
			L"Phillip Rogaway, "
			L"Hans Dobbertin, Antoon Bosselaers, Bart Preneel, Jack Lloyd"
			L"Paulo Barreto, Brian Gladman, Wei Dai, Peter Gutmann, and many others.\n\n"

			L"Portions of this software:\n"
			L"Copyright \xA9 2025 AM Crypto. All rights reserved.\n"
			L"Copyright \xA9 2013-2025 IDRIX. All rights reserved.\n"
			L"Copyright \xA9 2003-2012 TrueCrypt Developers Association. All Rights Reserved.\n"
			L"Copyright \xA9 1998-2000 Paul Le Roux. All Rights Reserved.\n"
			L"Copyright \xA9 1998-2008 Brian Gladman. All Rights Reserved.\n"
			L"Copyright \xA9 1995-2023 Jean-loup Gailly and Mark Adler.\n"
			L"Copyright \xA9 2016 Disk Cryptography Services for EFI (DCS), Alex Kolotnikov.\n"
			L"Copyright \xA9 1999-2023 Dieter Baron and Thomas Klausner.\n"
			L"Copyright \xA9 2013, Alexey Degtyarev. All rights reserved.\n"
			L"Copyright \xA9 1999-2016 Jack Lloyd. All rights reserved.\n"
			L"Copyright \xA9 2013-2019 Stephan Mueller <smueller@chronox.de>\n"
			L"Copyright \xA9 1999-2023 Igor Pavlov\n\n"

			L"\nThis software as a whole:\n"
			L"Copyright \xA9 2025 AM Crypto. All rights reserved.\n\n"

			L"This software uses wxWidgets library, which is copyright \xA9 1998-2011 Julian Smart, Robert Roebling et al.\n\n"

			L"An AM Crypto Release");
	}
}
