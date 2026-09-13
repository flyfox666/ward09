# From prototype to playable demo

Ward 09 evolved through three implementations: a browser prototype, a Godot iteration, and the current Unreal Engine Windows demo. The goal was a playable survival-horror experience with a credible delivery path, rather than a single generated scene.

## Human direction and agent work

The creator selected the visual direction, acquired third-party assets, played builds, and reported problems. Codex assisted with implementation, production scripts, debugging, integration, testing, documentation, and packaging. This was an iterative collaboration; there is no audited project-wide time or cost total presented here.

## Milestones

1. Browser prototype: connected levels, weapons, enemies, and offline play.
2. Godot iteration: native-game exploration and weapon presentation.
3. Unreal implementation: lighting, hospital props, character integration, and a standalone campaign.
4. Gameplay repair: knife swing, firearm alignment, grenade explosions, corpse cleanup, and supplies.
5. Complete demo controls: sensitivity, window/display modes, help, and quitting.
6. Campaign presentation: medical-ward prologue, minimap, enemy health bars, short radio exchanges, and adaptive music.
7. V1.7: Chinese/English interface and recorded synthesized dialogue, plus installer and portable Windows packaging.

## Evidence and limits

The Windows installer delivery record reports 358 checks covering an isolated install, file hashes, shortcuts, reinstall, game checks, and uninstall. These are recorded checks on the author's machine, not 358 independent gameplay features or a broad hardware certification.

The current demo saves preferences but not campaign progress. A native macOS build has not been delivered. Some character foundations and the soundtrack come from licensed third-party sources; see CREDITS.md.

The linked YouTube video includes edited development and gameplay footage. A separate 104-second English gameplay cut has also been prepared locally. It is not described as an uncut run, and its public URL will be added after publication.

## Inspect the implementation

See [selected source files](code/README.md) for dynamic music and bilingual display. The repository intentionally does not contain the entire Unreal project or third-party source assets.
