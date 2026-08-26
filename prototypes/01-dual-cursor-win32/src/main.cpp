#include <windows.h>
#include <algorithm>
#include <array>
#include <cstdint>
#include <unordered_map>
#include <vector>

struct PointerState {
    HANDLE device = nullptr;
    float x = 0.0f;
    float y = 0.0f;
    bool primaryDown = false;
    bool active = false;
};

static std::array<PointerState, 2> g_pointer{};
static std::unordered_map<std::uintptr_t, int> g_binding;

static std::uintptr_t Key(HANDLE h) {
    return reinterpret_cast<std::uintptr_t>(h);
}

static void Clamp(HWND hwnd, PointerState& p) {
    RECT rc{};
    GetClientRect(hwnd, &rc);
    p.x = std::clamp(p.x, 0.0f, static_cast<float>(std::max(0L, rc.right - 1)));
    p.y = std::clamp(p.y, 0.0f, static_cast<float>(std::max(0L, rc.bottom - 1)));
}

static void Reset(HWND hwnd) {
    RECT rc{};
    GetClientRect(hwnd, &rc);
    float cx = (rc.right - rc.left) * 0.5f;
    float cy = (rc.bottom - rc.top) * 0.5f;

    g_binding.clear();
    g_pointer = {};
    g_pointer[0].x = cx - 100.0f;
    g_pointer[0].y = cy;
    g_pointer[1].x = cx + 100.0f;
    g_pointer[1].y = cy;
    InvalidateRect(hwnd, nullptr, FALSE);
}

static int Bind(HANDLE device) {
    if (!device) return -1;
    auto it = g_binding.find(Key(device));
    if (it != g_binding.end()) return it->second;

    for (int i = 0; i < 2; ++i) {
        if (!g_pointer[i].active) {
            g_pointer[i].active = true;
            g_pointer[i].device = device;
            g_binding[Key(device)] = i;
            return i;
        }
    }
    return -1;
}

static void HandleRaw(HWND hwnd, const RAWINPUT& raw) {
    if (raw.header.dwType != RIM_TYPEMOUSE || !raw.header.hDevice) return;

    const RAWMOUSE& m = raw.data.mouse;
    bool activity = m.lLastX != 0 || m.lLastY != 0 || m.usButtonFlags != 0;
    if (!activity) return;

    int index = Bind(raw.header.hDevice);
    if (index < 0) return;
    PointerState& p = g_pointer[index];

    if ((m.usFlags & MOUSE_MOVE_ABSOLUTE) == 0) {
        p.x += static_cast<float>(m.lLastX);
        p.y += static_cast<float>(m.lLastY);
    }

    if (m.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) p.primaryDown = true;
    if (m.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) p.primaryDown = false;

    Clamp(hwnd, p);
    InvalidateRect(hwnd, nullptr, FALSE);
}

static void DrawPointer(HDC dc, const PointerState& p, int index) {
    const COLORREF colors[2] = { RGB(60, 150, 255), RGB(255, 100, 120) };
    COLORREF color = colors[index];
    int x = static_cast<int>(p.x);
    int y = static_cast<int>(p.y);
    int r = p.primaryDown ? 15 : 11;

    HPEN pen = CreatePen(PS_SOLID, 2, color);
    HBRUSH brush = CreateSolidBrush(p.primaryDown ? color : RGB(245, 245, 245));
    HGDIOBJ oldPen = SelectObject(dc, pen);
    HGDIOBJ oldBrush = SelectObject(dc, brush);

    if (index == 0) {
        Ellipse(dc, x-r, y-r, x+r, y+r);
    } else {
        POINT pts[4] = {{x, y-r-3}, {x+r+3, y}, {x, y+r+3}, {x-r-3, y}};
        Polygon(dc, pts, 4);
    }

    MoveToEx(dc, x-r-7, y, nullptr); LineTo(dc, x+r+7, y);
    MoveToEx(dc, x, y-r-7, nullptr); LineTo(dc, x, y+r+7);

    SelectObject(dc, oldPen);
    SelectObject(dc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);

    wchar_t label[32]{};
    wsprintfW(label, index == 0 ? L"A%s" : L"B%s", p.active ? L"" : L" (waiting)");
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, color);
    TextOutW(dc, x + 18, y + 14, label, lstrlenW(label));
}

static void Paint(HWND hwnd) {
    PAINTSTRUCT ps{};
    HDC dc = BeginPaint(hwnd, &ps);
    RECT rc{};
    GetClientRect(hwnd, &rc);

    HDC mem = CreateCompatibleDC(dc);
    HBITMAP bmp = CreateCompatibleBitmap(dc, std::max(1L, rc.right), std::max(1L, rc.bottom));
    HGDIOBJ oldBmp = SelectObject(mem, bmp);

    HBRUSH bg = CreateSolidBrush(RGB(22, 24, 30));
    FillRect(mem, &rc, bg);
    DeleteObject(bg);

    SetBkMode(mem, TRANSPARENT);
    SetTextColor(mem, RGB(235, 235, 235));
    const wchar_t* title = L"Dual Mouse Lab — Raw Input dual-cursor prototype";
    const wchar_t* help = L"Move two different mice to bind A/B. R: reset   Esc: exit";
    TextOutW(mem, 24, 20, title, lstrlenW(title));
    TextOutW(mem, 24, 46, help, lstrlenW(help));

    DrawPointer(mem, g_pointer[0], 0);
    DrawPointer(mem, g_pointer[1], 1);

    BitBlt(dc, 0, 0, rc.right, rc.bottom, mem, 0, 0, SRCCOPY);
    SelectObject(mem, oldBmp);
    DeleteObject(bmp);
    DeleteDC(mem);
    EndPaint(hwnd, &ps);
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        RAWINPUTDEVICE rid{};
        rid.usUsagePage = 0x01;
        rid.usUsage = 0x02;
        rid.dwFlags = RIDEV_DEVNOTIFY;
        rid.hwndTarget = hwnd;
        if (!RegisterRawInputDevices(&rid, 1, sizeof(rid))) return -1;
        Reset(hwnd);
        return 0;
    }
    case WM_INPUT: {
        UINT size = 0;
        GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));
        if (!size) return 0;
        std::vector<BYTE> buffer(size);
        if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, buffer.data(), &size, sizeof(RAWINPUTHEADER)) == size) {
            HandleRaw(hwnd, *reinterpret_cast<RAWINPUT*>(buffer.data()));
        }
        return 0;
    }
    case WM_INPUT_DEVICE_CHANGE:
        return 0;
    case WM_KEYDOWN:
        if (wParam == 'R') { Reset(hwnd); return 0; }
        if (wParam == VK_ESCAPE) { DestroyWindow(hwnd); return 0; }
        break;
    case WM_SIZE:
        for (auto& p : g_pointer) Clamp(hwnd, p);
        return 0;
    case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT) { SetCursor(nullptr); return TRUE; }
        break;
    case WM_ERASEBKGND:
        return 1;
    case WM_PAINT:
        Paint(hwnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int show) {
    const wchar_t CLASS_NAME[] = L"DualMouseLabWindow";
    WNDCLASSW wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = instance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    if (!RegisterClassW(&wc)) return 1;

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"Dual Mouse Lab", WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT, 1000, 700,
                                nullptr, nullptr, instance, nullptr);
    if (!hwnd) return 1;

    ShowWindow(hwnd, show);
    UpdateWindow(hwnd);

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return static_cast<int>(msg.wParam);
}
