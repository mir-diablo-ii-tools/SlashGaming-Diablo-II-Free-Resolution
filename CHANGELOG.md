# SGD2FreeRes Changelog

## SGD2FreeRes 3.1.0.0 (Not yet available)
- Refactor and compile on Visual C++ 6.0.
  - Improve compatability with every Windows system that can play
    Diablo II.
  - Remove requirement to install C/C++ runtime files, as they are
    included with every Windows since Windows 95 OSR 2.

## SGD2FreeRes 3.0.4.0 (April 15, 2023)
- Add support for the D2GL Glide and DDraw wrappers. Credits to
  bayaraa for the implementation.

## SGD2FreeRes 3.0.3.1d (April 15, 2023)
- Add NOWD server to the supported server list.

## SGD2FreeRes 3.0.3.1c (April 15, 2023)
- Add D2infinitum server to the supported server list.

## SGD2FreeRes 3.0.3.1b (November 11, 2022)
- Add Firesnake's ESR servers to the supported server list.

## SGD2FreeRes 3.0.3.1 (October 27, 2022)
- Extended the tile culling even more, to lessen the tile culling
  problem in D2DX with motion prediction enabled.
- Fix issue preventing Windows 7 from loading the library.
- Add Diablo2Online server to the supported server list.

## SGD2FreeRes 3.0.3.0 (October 17, 2022)
- Add support for 1.10 and 1.12A. Credits to Jarcho for the ports.
- Fix a New Stats and New Skill button 800x600 alignment issue in
  1.09D after using a waypoint.
- Extend the tile culling limit, so that tiles stay rendered with
  extended field of vision and perspective mode enabled. Credits to
  Szumigajowy for the starting point to fix this issue.
  - Note that this does not fix room rendering boundary issues. Rooms
    beyond the current adjacent rooms remain unrendered.
- Fix a Glide-only window resize issue when 800x600 isn't the second
  resolution in the resolution list.
- Fix a crash caused by switching resolutions when 640x480 is the only
  resolution in the resolution list.

## SGD2FreeRes 3.0.2.6d (September 18, 2022)
- Add Vahsify's "The Fury Within 1.02" server to the supported server
  list.

## SGD2FreeRes 3.0.2.6c (August 15, 2022)
- Add Casual Nostalgia server to the supported server list.

## SGD2FreeRes 3.0.2.6b (August 3, 2022)
- Update Diablo09's event server in the supported server list.

## SGD2FreeRes 3.0.2.6 (June 26, 2022)
- Fix black rectangle being drawn when the Scroll of Inifuss screen is
  open.

## SGD2FreeRes 3.0.2.5c (April 3, 2022)
- Updated timer's server in the supported server list.

## SGD2FreeRes 3.0.2.5b (February 5, 2022)
- Add Diablo 09's public test realm.

## SGD2FreeRes 3.0.2.5 (January 12, 2022)
- Fix crash in closed online games due to incorrectly-sized buffer for
  storing the server's IP's SHA-1 hash.

## SGD2FreeRes 3.0.2.4d (January 10, 2022)
- Updated timer's server in the supported server list.

## SGD2FreeRes 3.0.2.4c (December 2, 2021)
- Add timer's server to the supported server list.

## SGD2FreeRes 3.0.2.4b (November 29, 2021)
- Add 1.09 DiabloFans to the supported server list.

## SGD2FreeRes 3.0.2.4 (November 05, 2021)
- Fix gateway IPv4 hash verification crash with code NTE_BAD_KEYSET.

## SGD2FreeRes 3.0.2.3b (November 05, 2021)
- Add Diablo II Evolution to the supported server list.

## SGD2FreeRes 3.0.2.3 (October 17, 2021)
- Add ZombiesRUs and D2 Rebirth to the supported server list.
- Fix D2Resurgence server not being properly detected. The IP address
  entry has been updated.

Developer notes:
- MDC uses commit 30bda2723b8a18d1ddc3dca8e12f94c7aa2517c9.
- SGD2MAPI uses commit 7586477cd25d2bfd6a95e62199d885a2ac3543f2.

## SGD2FreeRes 3.0.2.2 (August 12, 2021)
- Fix interface bar background position cut off one pixel at the
  bottom.

SGD2MAPI:
- Fix potential crash associated with game library paths.

Developer notes:
- MDC uses commit d86ca4fed14f08743c511d6d9fde323d5c66c5c3.
- SGD2MAPI uses commit 7586477cd25d2bfd6a95e62199d885a2ac3543f2.

## SGD2FreeRes 3.0.2.1 (June 9, 2021)
- Fix resolution reverting to 640x480 on gateway play, caused
  by the number of config resolution being less than that on the
  gateway.
- Fix a possible cause of D2SE version detection failing due to
  improper string zero-termination.

1.09D Only:
- Fix crash after Act transition cutscene.

Developer notes:
- MDC uses commit e090165d9ce21534641104915bd0c75efad3dc2e.
- SGD2MAPI uses commit 8616bc941548fdf3541969694788e25c48dd2739.

## SGD2FreeRes 3.0.2.0 (May 1, 2021)
- Restore support for 1.13D.
- Add support for 1.14C and 1.14D.
- Add support for D2DX Glide wrapper. Special thanks to bolrog for
  providing the extended API in D2DX.
- Add 856x480 resolution to all existing gateways.
- Add 1068x600 resolution to D2LOD.NET.
- Fix potential incorrect display of DirectDraw video mode.
- Fix config wiping when JSON is not valid.
  - Display a warning and exit if the config is not valid JSON.

## SGD2FreeRes 3.0.1.1B (March 27, 2021)
- Add D2LOD.NET support. The custom resolution is 1024x768.

## SGD2FreeRes 3.0.1.1 (March 23, 2021)
- Add ProjectDiablo 2 support.
- Fix version detection bug that prevented D2SE from launching even
  with valid values.
- Fix incorrect inventory positions caused by some resolution
  configurations.
- Fix transfer of inventory arrangement positions between SP and MP.

## SGD2FreeRes 3.0.1.0 (March 13, 2021)
- Restore support for 1.13C.
- Support D2SE. Must be loaded using the PlugY.ini config.
- Fix video mode detection always incorrectly detecting DirectDraw
  when game video mode is not controlled by command line options.
- Fix default assets mismatch for the right screen's border.
- Fix potential bug that may result in the New Skill button not
  appearing correctly.

1.13C Only:
- Fix the aspect ratio window scaling when the maximize button is
  pressed. Previously, the maximize button only scaled for 4:3 aspect
  ratio even when the resolution's aspect ratio was different.
- Fix the restore down functionality when the maximize button is
  pressed. Previously, the button would prevent re-maximizing the
  game window when pressed.

Known issues:
- In 1.09D, Glide mode will sometimes crash from failed ingame
  assertion "nIndex != INVALID_HARDWARE". It is currently unknown how
  to consistently replicate the error.
- Glide mode displays incorrectly when the maximize button is pressed.

## SGD2FreeRes 3.0.0.1 (Feb 26, 2021)
- Support usage of CnC-DDraw as the DDraw wrapper.
- Reduce file size through optimization and the removal of code bloat.
- Fix incompatibility with PlugY.
- Fix improper resolution selection when largest resolution is set,
  and 640x480 is excluded in resolution definitions.

Known issues (since last patch):
- In 1.09D, Glide mode will sometimes crash from failed ingame
  assertion "nIndex != INVALID_HARDWARE". It is currently unknown how
  to consistently replicate the error.

## SGD2FreeRes 3.0.0.0 (Dec 12, 2020)
- Rename the project to SGD2FreeRes, as the project can provide more
  than just HD. Also sorts out confusion from folks who conflate HD
  with higher quality graphics.
- Rewrite from the ground up, replacing D2Template with SGD2MAPI as
  its core.
- Supports 1.09D, support for the other version need to be
  ported back in at a later time.
- Use JSON format for config file.
- Uncap single player resolution. Resolutions can be added in the
  config file.
- Cap multiplayer resolution is depending on the gateway.
- Support usage of nGlide as the Glide wrapper.
- Fix video option selection crash that would occur when Lighting
  Quality is selected under certain circumstances.
- Fix Windows 10 error on game exit, when Sven's Glide Wrapper is
  present, but the video mode was not Glide.

## D2HD 2.0.1.1 (Approx. Mar 2018 - Nov 2018)
- Add support for 1.12.
- Fix window resize issue upon game exit.
- Fix crash when using a non-standard resolution in DirectDraw or
  Direct3D video mode.

## D2HD 2.0.1.0 (Approx. Mar 2018 - Nov 2018)
- Set resolution to 1068x600, as Slash wants to maintain consistency
  with Resurgence.

## D2HD 2.0.1.0 Internal Release Candidate (Approx. Mar 2018 - Nov 2018)
- Set resolution to 1344x700, in case Slash wants to go with the
  higher resolution.

## D2HD 2.0.0.1 (Approx. Dec 2017 - Mar 2018)
- Fix resolution reload on first game created. Would lag the game,
  especially in Chaos Sanctuary.

## D2HD 2.0 (Approx. June - July 2017)
- Restore 640x480 resolution. New resolutions are added on top of
  existing resolutions.
- (Possibly) added support for 1.13D.

## D2HD 1.0 (Approx. May 2017)
- Replace 640x480 with 1068x600.
- Only supports 1.13C.
