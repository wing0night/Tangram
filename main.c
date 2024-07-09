#include "assets.h"
#include "event_functions.h"
#include "libgraphics.h"

extern Level_Num;

const double WINDOW_WIDTH = 32.00;
const double WINDOW_HEIGHT = 20.00;
string WINDOW_TITLE = "Tangram Game";

void Main()
{
    // Window settings
    SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    SetWindowTitle(WINDOW_TITLE);

    // library init
    InitGraphics();
    InitGUI();

    // register event
    registerMouseEvent(MyMouseEvent);
    registerTimerEvent(TimerEventProcess);

    // load assets
    LoadAllAssets(Level_Num);

    // 先把东西显示出来
    UpdateAll();
}
