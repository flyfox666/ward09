# Selected implementation files

These are selected, unmodified project-authored files from the V1.7 Unreal runtime, provided for inspection of how the demo works. They are not a standalone build or a complete Unreal project. No third-party models, audio, or textures are included here.

- `WardMusic.cpp`: eight score layers, visibility-aware enemy sampling, combat hold timers, state transitions, crossfades, and dialogue ducking.
- `WardLanguage.cpp`: language selection, cached translation, formatted labels, and width-aware English wrapping.
- `WardLanguage.h`: public language helper declarations.
- `WardEnglishCatalog.inl`: the English translation catalog used by the runtime.

The files depend on Unreal Engine and other Ward runtime classes such as `WardGame.h` and `WardAudio.h`, which are not included in this excerpt. Play the packaged Windows build; do not expect this folder to compile by itself.

Source visibility does not grant an open-source license. No broad reuse license has been selected by the author. Asset references in source are project paths, not embedded assets or permission to redistribute them.
