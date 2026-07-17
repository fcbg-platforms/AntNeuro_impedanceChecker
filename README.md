# AntNeuro_impedanceChecker
Impedance checker for the ANTneuro caps

## Executables:
The executables for Linux and Windows can be found in the branch dev

## Encrypted SDK binaries

This repository supports storing encrypted ANT Neuro SDK binaries and decrypting them only during GitHub Actions builds.

Expected encrypted files in repo root:
- `eego-SDK.dll.enc`
- `eego-SDK.lib.enc`
- `libeego-SDK.so.enc`

Required GitHub secret:
- `SDK_DECRYPT_PASSPHRASE`

Create encrypted files locally (from repository root):

```powershell
powershell -ExecutionPolicy Bypass -File .\scripts\encrypt-sdk.ps1 -Passphrase "<your-passphrase>"
```

The CI workflows decrypt these files at runtime:
- Windows workflow decrypts `.dll` and `.lib`
- Linux workflow decrypts `.so`
