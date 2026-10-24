# Veil
 
**Veil** is a free, open-source screen color overlay for Linux desktops. It places an adjustable, semi-transparent tint over your screen to make reading and long screen sessions more comfortable.
 
## Purpose
 
Many people find that a colored tint over a page or screen makes text easier to read and reduces eye strain and visual discomfort. Physical colored overlays and tinted lenses are common in classrooms and reading support. On a computer, though, the options are usually limited, platform-specific, or proprietary.
 
Veil exists to make a software color overlay that is:
 
- **Free and open:** anyone can use, study, modify, and share it.
- **Accessible:** easy to adjust and control, built for everyday use by students, educators, and anyone who reads on a screen.
- **Supported long-term:** intended as a maintained accessibility tool, not a one-off experiment.
The long-term goal is for Veil to be a tool that schools, universities, and accessibility programs can adopt freely, and that will stay free for every user who depends on it.
 
## Features
 
- Full-screen color overlay that sits above your desktop without blocking input
- Adjustable tint color and opacity
- System tray controls for quick on/off and adjustments
- Native Wayland support via LayerShellQt
## Roadmap
 
1. **Simple overlay:** an editable, transparent color overlay on Linux, then macOS
2. **Shader-based color transformation:** a GLSL shader layer using the OKLCh color space for perceptually accurate color adjustment, on Linux first, then macOS
3. **Windows support**
## Platform support
 
| Platform | Status |
|---|---|
| Linux (Wayland, tested on CachyOS) | In development |
| macOS | Planned |
| Windows | Planned |
 
## Building from source
 
**Requirements**
 
- C++ compiler with C++17 support or newer
- Qt 6
- LayerShellQt
- CMake
```bash
git clone https://github.com/Jacekhacking/veil.git
cd veil
cmake -B build
cmake --build build
```
 
## Contributing
 
Bug reports, feature ideas, and pull requests are welcome. If Veil helps you, or doesn't work well for your needs, please open an issue. Feedback from people who actually use color overlays is especially valuable.
 
## License
 
Veil is free software, licensed under the **GNU General Public License v3.0**. See [LICENSE.txt](LICENSE.txt) for the full text.
 
In short, you are free to use, study, modify, and redistribute Veil. If you distribute a modified version, it must also be released under GPLv3 with its source code available, so that Veil and its derivatives stay open for everyone.
 
Veil uses [Qt](https://www.qt.io/), which is available under the GNU LGPLv3, and LayerShellQt from the KDE project. Those components are covered by their own licenses.
 
Copyright © 2026 Jacek
 
