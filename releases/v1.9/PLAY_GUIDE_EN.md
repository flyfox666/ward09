# Ward09 V1.9 — Last Survivor: Lockdown Extraction

Windows playtest edition. Standalone automated gameplay and scoped runtime checks are recorded in `VALIDATION.md`. First-human-run timing and subjective listening remain unverified.

## Start and select a mode

Fully extract the package to a writable local folder. Keep `Ward09.exe`, `Engine`, `Ward09` and the other package files together, then double-click the adjacent `StartGame.cmd`. You can also start `Ward09.exe` directly. Playing does not require Unreal Engine, Epic Games Launcher or an internet connection.

This Windows x64 build defaults to **DirectX 12 and Shader Model 6** rendering. Use a GPU and driver that support that path. No minimum CPU, RAM, VRAM or frame-rate guarantee has been established; low-spec and clean-Windows compatibility need separate testing. A DirectX 11 shader format is listed in the project configuration, but a DX11 fallback has not been verified for this package.

The start menu offers:

- **Story Campaign:** the existing medical-ward prologue followed by the five-area campaign.
- **Last Survivor — Standard:** the new independent special operation, with a 12-minute overall deadline.
- **Last Survivor — Hard:** the same route, with fewer reserve rounds, faster contamination and an 11-minute deadline.

Use the Chinese / English switch in the start or Esc menu. Menus, objectives, subtitles and dialogue change together; changing language does not restart the run. The choice is saved locally.

## Mission

The transfer team has disappeared. Ash carries a sealed sample out of the failing facility while Lin Cen guides him over the radio. This is a parallel special operation, separate from campaign progression.

1. Follow the current objective and minimap marker to authorize the **three transfer terminals in order**. Get close to the marked terminal and press **E**.
2. Reach the north airlock control and press **E** to send the extraction signal.
3. Survive the **45-second airlock cycle**. The final airlock sector is free of sector contamination, but enemies can still follow you there.
4. When the airlock is ready, **physically enter the marked extraction zone**. Waiting for the timer alone does not win.

You do not need to clear every enemy. Fight, use a stagger window to pass an ordinary threat, or take a side service route. Armored and heavy threats have different resistance; do not assume every hit will stop them.

## Equipment and contamination

Start with a knife, pistol, shotgun, SMG, a bolt-action sniper rifle, **two grenades and two medical kits**. The heavy machine gun is unavailable in this operation. Each medical kit restores up to 40 health, capped at 100.

| Weapon | Loaded rounds | Standard reserve | Hard reserve |
|---|---:|---:|---:|
| Pistol | 15 | 45 | 30 |
| Shotgun | 7 | 14 | 7 |
| SMG | 32 | 96 | 64 |
| Sniper | 5 | 15 | 10 |

There are three fixed supply points: ammunition, medical supplies and a grenade. Nearby reachable supplies can be collected with E or by approaching closely. Supplies are consumed once; special-operation kills do not drop more supplies.

Rear sectors become contaminated progressively. The countdown, warning lamps and minimap use the same operation clock. Each sector gives **30 seconds of warning** before contamination; red sectors deal continuing damage. Move forward rather than remaining in a red area. Contamination does not physically seal the only forward route.

## Controls and settings

| Input | Action |
|---|---|
| WASD / mouse | Move / look |
| Hold Shift | Sprint; release to walk. Aiming, shooting and reloading interrupt sprint |
| Left / right mouse button | Attack / aim a firearm |
| 1 / 2 / 3 / 4 / 6 | Knife / pistol / shotgun / SMG / sniper rifle |
| Mouse wheel | Change available weapon |
| R / G / Q | Reload / grenade / medical kit |
| E | Use terminal, collect supplies, or mount/dismount the electric board |
| Space | Jump on foot; brake while riding |
| M / H | Toggle minimap / enemy health bars |
| J | Open the campaign action journal |
| Esc | Pause, settings, help, mode selection or quit |
| F9 | Immediately restart the current mode; operation difficulty is retained |

The campaign also has a heavy machine gun on **5**. Menu controls support mouse clicks, Up/Down or Tab to select, Left/Right to adjust, and Enter to confirm.

Esc settings include sensitivity, mouse Y inversion, resolution, fullscreen/borderless/windowed display and audio. After applying a display change, confirm it within 15 seconds or the previous display settings return. Music, effects and ambience have separate volumes. **Story Voice** independently switches both speakers off; subtitles and other sounds remain available. Dialogue uses original short lines with synthetic male/female voices and local/radio processing, rather than actor recordings.

Standalone pause/resume checks cover the operation and reload clocks, movement, voice/language settings, and an actual airlock cycle with four active moving enemies. Recorded master audio is silent during the measured pauses and returns after resume. See `VALIDATION.md` for the precise scope; these checks do not replace subjective listening.

## Results and local data

Success, death and deadline expiry end the run. Results show the reason, time, kills, shots, medical-kit use and this difficulty's best successful time. Successful faster runs replace that difficulty's record; failed runs do not. Standard and Hard have separate local records. Settings are saved, but a partially completed campaign or operation is not saved between sessions.

Use F9 for an immediate restart, or Esc for the restart confirmation, return to mode selection or quit confirmation. Restarting or returning to mode selection discards the current run.

Read `KNOWN_LIMITS.md` for unverified first-run timing, listening and hardware compatibility. V1.9 uses a separate folder and does not replace the preserved V1.7 package or existing public downloads.

## V1.9 route and electric board

The special operation now turns through a medical ward, mechanical services, loading yard, tall transfer hall and north airlock. The campaign keeps its existing maps. A standing electric board is near the starting ward: E mount/dismount, W/S forward/reverse, A/D steer, Space brake. It has 45 seconds of moving charge; pause freezes it. Dismount before shooting or using a terminal. The board is a flat-floor arcade prototype and does not climb stairs. The sniper is available in both modes, on key 6; the machine gun remains campaign-only.
