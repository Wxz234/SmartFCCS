#include <Windows.h>
#include <SmartFCCS/SmartFCCS.h>
using namespace SmartFCCS;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    auto device = CreateDevice();
    //CompileShaderFromFile(nullptr, SHADERTYPE::VERTEX, SHADERMODEL::SM_5_1);
    return 0;
}
