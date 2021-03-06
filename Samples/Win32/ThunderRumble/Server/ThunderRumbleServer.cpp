// TankBattle.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include "PlayerState.h"
#include "GameServer.h"
#include "PeerToPeerNetworkManager.h"

void Usage()
{
    std::wcout << L"Usage: ThunderRumbleServer.exe -host 127.0.0.1 -port 45000 -logpath [OPTIONAL] C:\\Temp" << std::endl;
}

int main()
{
    int numArgs = 0;
    int argCounter = 0;
    LPWSTR *argArray = nullptr;

    argArray = CommandLineToArgvW(GetCommandLine(), &numArgs);

    if (argArray == nullptr)
    {
        Usage();
        return -1;
    }

    std::wstring hostName;
    uint16_t portNumber = 0;
    std::wstring logPath;

    while (argCounter < numArgs)
    {
        auto command = argArray[argCounter];

        if (command[0] == L'-')
        {
            if (_wcsicmp(command + 1, L"host") == 0)
            {
                if (argCounter + 1 < numArgs)
                {
                    hostName = argArray[argCounter + 1];
                    argCounter += 2;
                }
                else
                {
                    Usage();
                    return -1;
                }
            }
            else if (_wcsicmp(command + 1, L"port") == 0)
            {
                if (argCounter + 1 < numArgs)
                {
                    portNumber = static_cast<uint16_t>(_wtoi(argArray[argCounter + 1]));
                    argCounter += 2;
                }
                else
                {
                    Usage();
                    return -1;
                }
            }
            else if (_wcsicmp(command + 1, L"logpath") == 0)
            {
                if (argCounter + 1 < numArgs)
                {
                    logPath = argArray[argCounter + 1];
                    argCounter += 2;
                }
                else
                {
                    Usage();
                    return -1;
                }
            }
            else
            {
                std::wcout << L"Unknown option: " << command << std::endl;
                Usage();
                return -1;
            }
        }
        else
        {
            argCounter++;
        }
    }

    if (hostName.empty() || portNumber == 0)
    {
        Usage();
        return -1;
    }

    std::wcout << L"Starting ThunderRumble server on " << hostName << L":" << portNumber << std::endl;

    PeerMeshForSamples::SetNetworkLogPath(logPath);

    std::wcout << L"Network log file location: " << PeerMeshForSamples::GetNetworkLogPath() << std::endl;

    GameServer server(hostName, portNumber);

    auto result = server.Run();

    std::wcout << L"Server exited with: " << result << std::endl;

    return result;
}

