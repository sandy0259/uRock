#include "stm32f4xx_hal.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"
#include "stm32f4xx_hal_gpio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "setting.h"
#include "spu.h"
#include "ui.h"
#include "cfgFunc.h"
#include "base-effect.h"
#include "helper.h"

#include "tab_list.h"
#include "tab_param.h"
#include "tab_select_effect.h"

#include "gfxconf.h"
#include "gfx.h"

#include "ff.h"

extern ADC_HandleTypeDef hadc2;

struct tab_t *tabs[TAB_NUM];
static uint32_t currentTabNumber = 0;

struct tab_list_t listTab;
struct tab_param_t paramTab;
struct tab_select_effect_t selectEffectTab;

uint32_t selectedEffectStage = 0;

void UserInterface(void const *argument){
	uint32_t i;
	uint32_t diff_flag;

    static GListener gl;
	GEvent* event;

    uint8_t potValues[2][4];
    uint8_t potApply[4];
    GPIO_PinState buttonPrevValue[MAX_CONFIG_NUM];
    uint8_t currentConfig = 0;

	ReadStageSetting(currentConfig);

	gfxInit();
	gdispClear(Black);

	gwinSetDefaultFont(gdispOpenFont("DejaVuSans20"));
	gwinSetDefaultStyle(&BlackWidgetStyle, FALSE);
    geventListenerInit(&gl);
    gwinAttachListener(&gl);
    
	// create the widget
	tabs[LIST_TAB] = tab_list_init(&listTab); 
	tabs[PARAM_TAB] = tab_param_init(&paramTab); 
	tabs[SELECT_EFFECT_TAB] = tab_select_effect_init(&selectEffectTab); 
	SwitchTab(LIST_TAB);

	HAL_ADC_Start_DMA(&hadc2, (uint32_t*)potValues[0], 3); //TODO: Make 4
    for(i = 0; i < CONFIG_BUTTON_NUM; i++){
        buttonPrevValue[i] = HAL_GPIO_ReadPin(CONFIG_BUTTON_PORT, CONFIG_BUTTON_PINS[i]);
    }


	while(1) {
		// Get an Event
		event = geventEventWait(&gl, 50);

		switch(event->type) {
            case GEVENT_GWIN_BUTTON:
                tabs[currentTabNumber]->bHandle(tabs[currentTabNumber], (GEventGWinButton*)event);
                break;
		}


        //XXX: Use Event System and Callback
        //TODO: Sync Pots before set new value
        if(currentTabNumber == PARAM_TAB){
            diff_flag = 0;

            for(i = 0; i < 4; i++){
                if(((potValues[1][i] - potValues[0][i]) > 5) || ((potValues[0][i] - potValues[1][i]) > 5)){
                    potApply[i] = potValues[0][i];
                    diff_flag++;
                }else{
                   potApply[i] = potValues[1][i];
                }
            }

            if(diff_flag){
                if (retriveStagedEffect(selectedEffectStage))
                    retriveStagedEffect(selectedEffectStage)->adj((void*)retriveStagedEffect(selectedEffectStage), potApply);

                for(i = 0; i < 4; i++){
                    potValues[1][i] = potApply[i];
                }
                tabs[currentTabNumber]->refresh(tabs[currentTabNumber]);
            }
        }
        
        if(currentTabNumber == LIST_TAB){
            for(i = 0; i < CONFIG_BUTTON_NUM; i++){
                if (buttonPrevValue[i] != HAL_GPIO_ReadPin(CONFIG_BUTTON_PORT, CONFIG_BUTTON_PINS[i])){
                    buttonPrevValue[i] = HAL_GPIO_ReadPin(CONFIG_BUTTON_PORT, CONFIG_BUTTON_PINS[i]);
                    SaveStageSetting(currentConfig);
                    currentConfig = i;
                    ReadStageSetting(currentConfig);
                }
            }
            tabs[currentTabNumber]->refresh(tabs[currentTabNumber]);
        }
	}

	while(1);
}

void SwitchTab(uint32_t tabSwitching){
	tabs[currentTabNumber]->hide(tabs[currentTabNumber]);
	currentTabNumber = tabSwitching;
	tabs[currentTabNumber]->show(tabs[currentTabNumber]);
    tabs[currentTabNumber]->refresh(tabs[currentTabNumber]);

	return;
}
