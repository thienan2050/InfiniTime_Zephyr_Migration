#include "displayapp/screens/MyApp.h"
#include "displayapp/screens/Symbols.h"
#include "displayapp/InfiniTimeTheme.h"
#include <lvgl/lvgl.h>


using namespace Pinetime::Applications::Screens;

MyApp::MyApp(AppControllers& /*controllers*/) {
    
  lv_obj_t* title = lv_label_create(lv_scr_act(), nullptr);  
  lv_label_set_text_static(title, "My Be Be \nSleep all day\nAlways go to work\n LATE");
  lv_obj_align(title, nullptr, LV_ALIGN_CENTER, 0, 0);  
}

void MyApp::Refresh() {
    taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
}

bool MyApp::OnButtonPushed() {
  return true;
}

MyApp::~MyApp() {
    lv_task_del(taskRefresh);
    lv_obj_clean(lv_scr_act());
}