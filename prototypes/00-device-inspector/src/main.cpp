#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

static std::wstring DeviceName(HANDLE device) {
    UINT chars = 0;
    if (GetRawInputDeviceInfoW(device, RIDI_DEVICENAME, nullptr, &chars) == static_cast<UINT>(-1) || chars == 0) {
        return L"<unknown>";
    }

    std::wstring name(chars, L'\0');
    if (GetRawInputDeviceInfoW(device, RIDI_DEVICENAME, name.data(), &chars) == static_cast<UINT>(-1)) {
        return L"<unknown>";
    }
    if (!name.empty() && name.back() == L'\0') name.pop_back();
    return name;
}

static void ListMouseDevices() {
    UINT count = 0;
    if (GetRawInputDeviceList(nullptr, &count, sizeof(RAWINPUTDEVICELIST)) == static_cast<UINT>(-1)) {
        std::wcerr << L"GetRawInputDeviceList failed.\n";
        return;
    }

    std::vector<RAWINPUTDEVICELIST> devices(count);
    if (count && GetRawInputDeviceList(devices.data(), &count, sizeof(RAWINPUTDEVICELIST)) == static_cast<UINT>(-1)) {
        std::wcerr << L"GetRawInputDeviceList failed.\n";
        return;
    }

    std::wcout << L"Raw Input mouse devices:\n";
    for (const auto& d : devices) {
        if (d.dwType != RIM_TYPEMOUSE) continue;
        std::wcout << L"  handle=" << d.hDevice << L"\n"
                   << L"  name=" << DeviceName(d.hDevice) << L"\n\n";
    }
}

static void PrintMouseEvent(const RAWINPUT& raw) {
    if (raw.header.dwType != RIM_TYPEMOUSE) return;
    const RAWMOUSE& m = raw.data.mouse;

    std::wcout << L"device=" << raw.header.hDevice
               << L" dx=" << m.lLastX
               << L" dy=" << m.lLastY;

    if (m.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)  std::wcout << L" L_DOWN";
    if (m.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP)    std::wcout << L" L_UP";
    if (m.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) std::wcout << L" R_DOWN";
    if (m.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP)   std::wcout << L" R_UP";
    if (m.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) std::wcout << L" M_DOWN";
    if (m.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP)   std::wcout << L" M_UP";
    if (m.usButtonFlags & RI_MOUSE_WHEEL) {
        std::wcout << L" WHEEL=" << static_cast<SHORT>(m.usButtonData);
    }
    std::wcout << L"\n";
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_INPUT: {
        UINT size = 0;
        GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));
        if (!size) return 0;
        std::vector<BYTE> buffer(size);
        if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, buffer.data(), &size, sizeof(RAWINPUTHEADER)) == size) {
            PrintMouseEvent(*reinterpret_cast<RAWINPUT*>(buffer.data()));
        }
        return 0;
    }
    case WM_INPUT_DEVICE_CHANGE:
        std::wcout << (wParam == GIDC_ARRIVAL ? L"DEVICE_ARRIVAL " : L"DEVICE_REMOVAL ")
                   << reinterpret_cast<HANDLE>(lParam) << L"\n";
        ListMouseDevices();
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int main() {
    ListMouseDevices();

    HINSTANCE instance = GetModuleHandleW(nullptr);
    const wchar_t CLASS_NAME[] = L"DualMouseInspectorMessageWindow";

    WNDCLASSW wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = instance;
    wc.lpszClassName = CLASS_NAME;
    if (!RegisterClassW(&wc)) {
        std::wcerr << L"RegisterClassW failed.\n";
        return 1;
    }

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"Dual Mouse Inspector", 0,
                                0, 0, 0, 0, HWND_MESSAGE, nullptr, instance, nullptr);
    if (!hwnd) {
        std::wcerr << L"CreateWindowExW failed.\n";
        return 1;
    }

    RAWINPUTDEVICE rid{};
    rid.usUsagePage = 0x01;
    rid.usUsage = 0x02;
    rid.dwFlags = RIDEV_INPUTSINK | RIDEV_DEVNOTIFY;
    rid.hwndTarget = hwnd;

    if (!RegisterRawInputDevices(&rid, 1, sizeof(rid))) {
        std::wcerr << L"RegisterRawInputDevices failed.\n";
        return 1;
    }

    std::wcout << L"Listening for mouse input. Press Ctrl+C to stop.\n\n";

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}
