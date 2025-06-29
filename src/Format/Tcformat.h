/*
 Legal Notice: Some portions of the source code contained in this file were
 derived from the source code of TrueCrypt 7.1a, which is
 Copyright (c) 2003-2012 TrueCrypt Developers Association and which is
 governed by the TrueCrypt License 3.0, also from the source code of
 Encryption for the Masses 2.02a, which is Copyright (c) 1998-2000 Paul Le Roux
 and which is governed by the 'License Agreement for Encryption for the Masses'
 Modifications and additions to the original source code (contained in this file)
 and all other portions of this file are Copyright (c) 2013-2025 AM Crypto
 and are governed by the Apache License 2.0 the full text of which is
 contained in the file License.txt included in VeraCrypt binary and source
 code distribution packages. */

#include "Common/Common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NBR_KEY_BYTES_TO_DISPLAY	16
#define KEY_GUI_VIEW_SIZE			64		// Max characters of the key hex dump to display

enum timer_ids
{
	TIMER_ID_RANDVIEW = 0xff,
	TIMER_ID_SYSENC_PROGRESS,
	TIMER_ID_NONSYS_INPLACE_ENC_PROGRESS,
	TIMER_ID_WIPE_PROGRESS,
	TIMER_ID_SYSENC_DRIVE_ANALYSIS_PROGRESS,
	TIMER_ID_KEYB_LAYOUT_GUARD
};

static void localcleanup ( void );
static void LoadSettings ( HWND hwndDlg );
void SaveSettings ( HWND hwndDlg );
static void EndMainDlg ( HWND hwndDlg );
void ComboSelChangeEA ( HWND hwndDlg );
static void VerifySizeAndUpdate ( HWND hwndDlg , BOOL bUpdate );
static void __cdecl sysEncDriveAnalysisThread (void *hwndDlgArg);
static void __cdecl volTransformThreadFunction ( void *hwndDlg );
static void LoadPage ( HWND hwndDlg , int nPageNo );
__int64 PrintFreeSpace ( HWND hwndTextBox , wchar_t *lpszDrive , PLARGE_INTEGER lDiskFree );
void DisplaySizingErrorText ( HWND hwndTextBox );
void EnableDisableFileNext ( HWND hComboBox , HWND hMainButton );
BOOL QueryFreeSpace (HWND hwndDlg, HWND hwndTextBox, BOOL display, LONGLONG *pFreeSpaceValue, BOOL* pbIsSparseFilesSupported);
static BOOL FinalPreTransformPrompts (void);
void UpdateLastDialogId (void);
void HandleOldAssignedDriveLetter (void);
void AddCipher ( HWND hComboBox , char *lpszCipher , int nCipher );
BOOL CALLBACK PageDialogProc ( HWND hwndDlg , UINT uMsg , WPARAM wParam , LPARAM lParam );
BOOL CALLBACK MainDialogProc ( HWND hwndDlg , UINT uMsg , WPARAM wParam , LPARAM lParam );
void ExtractCommandLine ( HWND hwndDlg , wchar_t *lpszCommandLine );
void DisplayRandPool (HWND hwndDlg, HWND hPoolDisplay, BOOL bShow);
void DisplayPortionsOfKeys (HWND headerKeyHandle, HWND masterKeyHandle, wchar_t *headerKeyStr, wchar_t *masterKeyStr, BOOL hideKeys);
int DetermineMaxHiddenVolSize (HWND hwndDlg);
BOOL IsSparseFile (HWND hwndDlg);
BOOL GetFileVolSize (HWND hwndDlg, unsigned __int64 *size);
BOOL SwitchWizardToSysEncMode (void);
void SwitchWizardToFileContainerMode (void);
static BOOL ResolveUnknownSysEncDirection (void);
static BOOL WipeHiddenOSCreationConfig (void);
static void AfterWMInitTasks (HWND hwndDlg);
static void AfterSysEncProgressWMInitTasks (HWND hwndDlg);
static void InitSysEncProgressBar (void);
static void InitNonSysInplaceEncProgressBar (void);
static void UpdateNonSysInplaceEncProgressBar (void);
static BOOL SysEncInEffect (void);
static BOOL CreatingHiddenSysVol(void);
static void NonSysInplaceEncPause (void);
static void NonSysInplaceEncResume (void);
void ShowNonSysInPlaceEncUIStatus (void);
void UpdateNonSysInPlaceEncControls (void);
int MountHiddenVolHost ( HWND hwndDlg, wchar_t *volumePath, int *driveNo, Password *password, int pkcs5_prf, int pim, BOOL bReadOnly );
int AnalyzeHiddenVolumeHost (HWND hwndDlg, int *driveNo, __int64 hiddenVolHostSize, int *realClusterSize, __int64 *pnbrFreeClusters);
int ScanVolClusterBitmap ( HWND hwndDlg, int *driveNo, __int64 nbrClusters, __int64 *nbrFreeClusters);
static void WipeStart (void);
static void WipeAbort (void);
static void UpdateWipeProgressBar (void);
static void InitWipeProgressBar (void);
static void UpdateWipeControls (void);
DWORD GetFormatSectorSize ();

extern BOOL showKeys;
extern volatile HWND hMasterKey;
extern volatile HWND hHeaderKey;
extern volatile BOOL bHiddenVolHost;
extern volatile BOOL bHiddenVolDirect;
extern BOOL bRemovableHostDevice;
extern BOOL bWarnDeviceFormatAdvanced;
extern HWND hCurPage;
extern HWND hProgressBar;
extern volatile BOOL bVolTransformThreadCancel;
extern volatile BOOL bInPlaceEncNonSysResumed;
extern volatile BOOL bFirstNonSysInPlaceEncResumeDone;
extern volatile BOOL bInPlaceEncNonSys;
extern volatile BOOL bInPlaceDecNonSys;
extern __int64 NonSysInplaceEncBytesDone;
extern __int64 NonSysInplaceEncTotalSize;
extern int nPbar;
extern volatile int WizardMode;
extern volatile BOOL bInPlaceEncNonSysResumed;

extern wchar_t HeaderKeyGUIView [KEY_GUI_VIEW_SIZE];
extern wchar_t MasterKeyGUIView [KEY_GUI_VIEW_SIZE];
extern volatile int NonSysInplaceEncStatus;

#ifdef __cplusplus
}
#endif
