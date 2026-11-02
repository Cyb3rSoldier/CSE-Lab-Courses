#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <windows.h>

namespace fs = std::filesystem;

const std::wstring MESA_DIR = L"C:\\msys64\\opt\\mesa3d";

void ensure_mesa_dlls(const fs::path& target_dir) {
    try {
        if (!fs::exists(MESA_DIR)) return;
        if (!fs::exists(target_dir)) return;

        fs::path src_gl = fs::path(MESA_DIR) / L"opengl32.dll";
        fs::path src_gallium = fs::path(MESA_DIR) / L"libgallium_wgl.dll";

        if (fs::exists(src_gl)) {
            fs::path dst_gl = target_dir / L"opengl32.dll";
            if (!fs::exists(dst_gl)) {
                fs::copy_file(src_gl, dst_gl, fs::copy_options::overwrite_existing);
            }
        }
        if (fs::exists(src_gallium)) {
            fs::path dst_gallium = target_dir / L"libgallium_wgl.dll";
            if (!fs::exists(dst_gallium)) {
                fs::copy_file(src_gallium, dst_gallium, fs::copy_options::overwrite_existing);
            }
        }
    } catch (...) {}
}

int main(int argc, char* argv[]) {
    // 1. Determine current executable directory and base name
    wchar_t exePathBuf[MAX_PATH];
    GetModuleFileNameW(NULL, exePathBuf, MAX_PATH);
    fs::path exePath(exePathBuf);
    fs::path exeDir = exePath.parent_path();
    std::string stem = exePath.stem().string();

    // 2. Locate original executable (<stem>_orig.exe)
    fs::path origExe = exeDir / (stem + "_orig.exe");
    if (!fs::exists(origExe)) {
        std::cerr << "[Mesa-Wrapper] Error: Original executable not found: " << origExe.string() << std::endl;
        return 1;
    }

    // 3. Prepare argv with original executable as argv[0]
    std::vector<char*> childArgv(argc + 1);
    std::string origExeStr = origExe.string();
    childArgv[0] = const_cast<char*>(origExeStr.c_str());
    for (int i = 1; i < argc; ++i) {
        childArgv[i] = argv[i];
    }
    childArgv[argc] = nullptr;

    // 4. Synchronously execute the original binary using fork/execv/waitpid
    int exitCode = 0;
    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "[Mesa-Wrapper] Failed to fork process" << std::endl;
        return 1;
    } else if (pid == 0) {
        execv(origExeStr.c_str(), childArgv.data());
        std::cerr << "[Mesa-Wrapper] Failed to execute: " << origExeStr << std::endl;
        _exit(127);
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            exitCode = WEXITSTATUS(status);
        } else {
            exitCode = 1;
        }
    }

    // 5. If compilation / command succeeded, ensure Mesa3D DLLs are in target output directory
    if (exitCode == 0 && fs::exists(MESA_DIR)) {
        fs::path outDir;
        bool foundOut = false;
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-o" && i + 1 < argc) {
                fs::path outPath(argv[i + 1]);
                if (outPath.has_parent_path()) {
                    outDir = outPath.parent_path();
                } else {
                    outDir = fs::current_path();
                }
                foundOut = true;
                break;
            } else if (arg.rfind("-o", 0) == 0 && arg.length() > 2) {
                fs::path outPath(arg.substr(2));
                if (outPath.has_parent_path()) {
                    outDir = outPath.parent_path();
                } else {
                    outDir = fs::current_path();
                }
                foundOut = true;
                break;
            }
        }

        if (foundOut && !outDir.empty()) {
            ensure_mesa_dlls(outDir);
        }

        // Also check if current directory has a ./build folder
        fs::path localBuild = fs::current_path() / L"build";
        if (fs::exists(localBuild) && fs::is_directory(localBuild)) {
            ensure_mesa_dlls(localBuild);
        }
    }

    return exitCode;
}
