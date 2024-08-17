#pragma once


class StartupManager {
public:
    static void addToStartup();

    static bool IsRunningAsAdmin();
    static void RunAsAdmin();
};