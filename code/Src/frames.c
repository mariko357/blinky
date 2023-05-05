#include "frames.h"

cframe scFrame;
uint32_t lClick = 0;
uint8_t aSleep = 0;
uint8_t cFrame = 0;
uint8_t cNum = 0;
cframe sconvert(frame* input){
    cframe out;
    for(uint8_t i = 0; i < 12; i++){
        uint8_t temp[] = {0, 0, 0};
        if(input->p[i] != 0){
            if(i <= 3){
                temp[1] |= (1 << (i + 4));
            }
            else{
                temp[2] |= (1 << (i - 4));
            }
            for(uint8_t j = 0; j < 12; j++){
                if(j <= 7){
                    if(input->p[i] & (1 << j)) {
                        temp[0] |= (1 << (j));
                    }
                }
                else{
                    if(input->p[i] & (1 << j)) {
                        temp[1] |= (1 << (j - 8));
                    }
                }
            }
        }
        out.p[i][0] = temp[2];
        out.p[i][1] = temp[1];
        out.p[i][2] = temp[0];
    }
    return out;
}

void sdraw(cframe* inFrame, SPI_HandleTypeDef* hspi){

	static uint8_t cLine = 0;
	if(cLine == 12){cLine = 0;};
	HAL_SPI_Transmit(hspi, inFrame->p[cLine], 3, 1);
	strobe();
	cLine++;

}

void strobe(void){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
}

void enterSleep(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
	aSleep = 1;
	HAL_SuspendTick();
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}

void exitSleep(void){
	SystemClock_Config();
	HAL_ResumeTick();
	lClick = HAL_GetTick();
	aSleep = 0;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
}
