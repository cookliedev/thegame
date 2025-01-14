#pragma once
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

struct EXECPATH {
    static std::string getPath() {
        char buffer[1024];

        #if defined(_WIN32) || defined(_WIN64)
            GetModuleFileNameA(nullptr, buffer, sizeof(buffer));
        #else
            ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
            if (len == -1) {
                return "";
            }
            buffer[len] = '\0';
        #endif

        return std::string(buffer);
    }

    static std::string getDir() {
        std::string exePath = EXECPATH::getPath();
    
        #if defined(_WIN32) || defined(_WIN64)
            size_t lastSlashIdx = exePath.find_last_of("\\/");
            if (lastSlashIdx != std::string::npos) {
                return exePath.substr(0, lastSlashIdx);
            }
            return "";
        #else
            char *dir = dirname(&exePath[0]);
            return std::string(dir);
        #endif
    }
};
