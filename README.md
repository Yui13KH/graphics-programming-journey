# graphics-programming-journey
my journey of learning graphics programming from the very bottom

Hey! So I am very interested in graphics programming. I know it’s insanely hard, especially since I'm more interested in the physics and simulation side of things not that the graphics part isn't interesting, but the math behind movement is what really gets me.

The current job market is a mess, so I am learning this half because I really like the field and the math/physics involved, and half for potential job opportunities. My plan is to show off my progress on YouTube every month—short videos showing milestones or devlogs—while this GitHub repo stays as the comprehensive, step-by-step record of everything I did.

I'll also be adding Xournal++ files of the math I am learning and how I calculate things. I think math and physics are best learned when they are handwritten rather than typed, and those files will serve as my "handbook."

Hopefully, with enough time and study, I'll reach a level that is employable and high-skill.

---

# 🛠️ Development Environment Setup

This project uses **Modern C++20**, **CMake**, and **SDL3**. Setting up a low-level graphics environment on Windows can be tricky, especially when moving away from heavy IDEs like Visual Studio to a lightweight environment like VS Code / VSCodium. 

Follow this quick guide to configure your local compiler, extensions, and external libraries.

---

## 📋 Prerequisites & Tools

Before configuring the project, ensure you have the following installed on your Windows system:

1. **VSCodium / VS Code**
2. **MinGW-w64 (GCC)** — Ensure your compiler version is modern (e.g., GCC 15.2.0) and added to your Windows system Environment variables (`PATH`).

---

## 🚀 Setup Sequence

### Step 1: Install VSCodium Extensions
Open VSCodium, press `Ctrl + Shift + X` to open the Marketplace, and install:
* **CMake Tools** (by Microsoft or the open-source variant)

### Step 2: Configure Your Compiler Kit
To tell VSCodium which compiler to use to parse the build tree:
1. Press `Ctrl + Shift + P` to open the Command Palette.
2. Type and select: `CMake: Select a Kit`
3. Choose your MinGW installation from the dropdown menu (e.g., `GCC 15.2.0 x86_64-w64-mingw32`).

### Step 3: Download & Place SDL3 Dependencies
Because third-party libraries aren't committed directly to the raw repository structure, you must download the pre-compiled binaries manually:

1. Head to the official [SDL GitHub Releases](https://github.com/libsdl-org/SDL/releases).
2. Scroll down to the assets (click *"Show all assets"* if hidden) and download the VC development package (e.g., `SDL3-devel-X.X.X-VC.zip`).
3. Extract the contents and place them directly into the `external/` directory. 

Ensure your folder structure matches this layout exactly:
```text
graphics-programming-journey/
└── external/
    └── SDL3/
        ├── include/   <-- Contains all the SDL3 .h headers
        └── lib/       <-- Contains instruction-set libraries (x64, etc.)
```

```bash
# 1. Initialize and configure the build directory
cmake -G "MinGW Makefiles" -B build

# 2. Jump into the build environment
cd build

# 3. Compile a specific binary module
cmake --build . --target 02_RedWindow

# 4. Launch the application
.\examples\02_RedWindow\02_RedWindow.exe
```