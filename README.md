## How to build

Run `scons platform=linux custom_api_file=extension_api.json target=template_debug`. `platform` might be equal to linux/windows/android/ios/mac. `target` might be either template_debug or template_release.

When everything compiles, your binary will be in `bin` folder.

To speed things up, you can use [Godot build containers](https://github.com/godotengine/build-containers). They include all dependeces needed to build this GDExtension.
