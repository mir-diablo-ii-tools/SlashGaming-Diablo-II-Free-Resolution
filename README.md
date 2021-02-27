# SlashGaming Diablo II Free Resolution (SGD2FreeRes)
This is a project aimed at modding Diablo II to support any resolution.

## Usage
The DLL does nothing on its own and must be loaded into the game via external tools. Once loaded, the game will need to be run in order to generate the config file for the first time. Singleplayer resolutions, along with other configuration options can be configured to the preferences of the user.

Multiplayer use is restricted to certain gateways. This cannot be changed easily and prevents unintentional abuse where it is not allowed (i.e. Battle.net). If used in unpermitted environments, the resolution is hardcoded to run with only 640x480 or 800x600. It is also still possible to be detected by anti-cheat systems and be banned for unauthorized modification of the game client, even if the functionality is ineffective. Where it is permitted, the resolutions are preset for the server.

Currently, the project supports Diablo II: Lord of Destruction, version 1.09D.

## Contribution
SGD2FreeRes is coded in C++20. It currently is intended to compile with Visual Studio 2019.

The linker needs to be configured to link the DLL to version.lib, MDCc.lib, MDCcpp98.lib and SGD2MAPI.lib.

When you submit a pull request, you certify that the code in the pull request is AGPLv3+ compatible. You also certify that you have authorization to submit the pull request with the code changes. You certify that the merging of the pull request with those changes is authorized under the license terms of the AGPLv3+. Finally, you certify that the contribution is licensed under the AGPLv3+.

## Thanks
- [/r/SlashDiablo](https://www.reddit.com/r/slashdiablo/): The community that got me started. The whole reason the project took off.
- [PhrozenKeep](https://d2mods.info/): Community with plenty of information on Diablo II, modding, and resources.

## Legal
The project is licensed under the terms of the AGPLv3. Components may be licensed under other terms, so check LICENSE for more details. If you wish to apply for a proprietary license exception, please contact me on the SlashDiablo Discord channel.

Diablo II and Diablo II: Lord of Destruction are registered trademarks of Blizzard Entertainment. This project is not affiliated with Blizzard Entertainment in any way.
