# Tools

## bin2header.exe

[bin2header](https://github.com/AntumDeluge/bin2header) may be a good alternative

## ico files

[icon.ico](icon.ico) files are converted from [icon.png](icon.png) with `ffmpeg`

```cmd
ffmpeg -i icon.png -vf scale=32:32 icon.ico
```

## font

The font files can be converted with tools in imgui:[binary_to_compressed_c](../deps/imgui/misc/../imgui/misc/fonts/binary_to_compressed_c.cpp)

[Nota Sans](https://fonts.google.com/specimen/Noto+Sans+SC#standard-styles) is from google.
