#include <SmartFCCS/SmartFCCS.h>
using namespace SmartFCCS;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    auto window = CreateWindowF(L"fccs", 800, 600);
    window->ShowWindow();
    while (window->IsRun()) {

    }
    return 0;
}
