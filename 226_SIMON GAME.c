/* ###################################################################
**     Filename    : main.c
**     Project     : SIMONGAME
**     Processor   : MKL05Z32VLF4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2022-12-12, 11:59, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
* ###################################################################/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "TSS1.h"
#include "RED_LED.h"
#include "TU1.h"
#include "BLUE_LED.h"
#include "GREEN_LED.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
 void wait(int wait_ms) {
  	unsigned int i,j;
  	for(i=0;i<wait_ms;i++){
  		for(j=0;j<785;j++) {
  			__asm("nop");
  		}

  	}
  }

 void REDLED() {
     RED_LED_SetRatio16(RED_LED_DeviceData, 0xFFFF);
     wait(1000);
     RED_LED_SetRatio16(RED_LED_DeviceData, 0x0);
     wait(1000);
 }
 void GREENLED() {
     GREEN_LED_SetRatio16(GREEN_LED_DeviceData, 0xFFFF);
     wait(1000);
     GREEN_LED_SetRatio16(GREEN_LED_DeviceData, 0x0);
     wait(1000);
 }

 void BLUELED() {
     BLUE_LED_SetRatio16(BLUE_LED_DeviceData, 0xFFFF);
     wait(1000);
     BLUE_LED_SetRatio16(BLUE_LED_DeviceData, 0x0);
     wait(1000);
 }

 void TURQOISELED(){
	 RED_LED_SetRatio16(RED_LED_DeviceData,0x0);
	 BLUE_LED_SetRatio16(BLUE_LED_DeviceData,0xFFFF);
	 GREEN_LED_SetRatio16(GREEN_LED_DeviceData,0xFFFF);
	 wait(500);

	 RED_LED_SetRatio16(RED_LED_DeviceData,0x0);
	 BLUE_LED_SetRatio16(BLUE_LED_DeviceData,0x0);
	 GREEN_LED_SetRatio16(GREEN_LED_DeviceData,0x0);
	 wait(500);

 }
void ORANGELED(){
	  RED_LED_SetRatio16(RED_LED_DeviceData,0xFFFF);
	  BLUE_LED_SetRatio16(BLUE_LED_DeviceData,0x0);
	  GREEN_LED_SetRatio16(GREEN_LED_DeviceData,0xFFFF);
	  wait(500);

	  RED_LED_SetRatio16(RED_LED_DeviceData,0x0);
	  BLUE_LED_SetRatio16(BLUE_LED_DeviceData,0x0);
	  GREEN_LED_SetRatio16(GREEN_LED_DeviceData,0x0);
	  wait(500);
}

void PINKLED(){
	  RED_LED_SetRatio16(RED_LED_DeviceData,0xFFFF);
	  BLUE_LED_SetRatio16(BLUE_LED_DeviceData,0xFFFF);
	  GREEN_LED_SetRatio16(GREEN_LED_DeviceData,0x0);
	  wait (1000);
	  RED_LED_SetRatio16(RED_LED_DeviceData,0x0);
	  BLUE_LED_SetRatio16(BLUE_LED_DeviceData,0x0);
	  GREEN_LED_SetRatio16(GREEN_LED_DeviceData,0x0);
	  wait(1000);

}
void OFFLED(){
	  RED_LED_SetRatio16(RED_LED_DeviceData,0x0);
	  BLUE_LED_SetRatio16(BLUE_LED_DeviceData,0x0);
	  GREEN_LED_SetRatio16(GREEN_LED_DeviceData,0x0);

}

int led_sequence[50];
int colour=0;
int maxlevel=50;
int level=1;
int ispressed=0;
int usertap=0;
int play=0;
int show=0;
int check=0;

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /* Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! */
  PE_low_level_init();
  /* End of Processor Expert internal initialization.                    */

  /* Write your code here */
  /* For example: for(;;) { } */

  for(;;){

  		 OFFLED();
  		 start:
		 level=1;// initialise game at level 1
  				  ispressed=0;
  		 while(ispressed <2){
  			 	 TSS_Task();}
  		 if (TSS1_cKey0.Position > 0) {//When touchpad is touched, game will start and blink Pink,Orange and Turqoise LED

  		 PINKLED();
  		 ORANGELED();
  		 TURQOISELED();


  		 }


  		 wait (2000);//game waits 2 second before initialising the random led sequence

  		srand(TSS1_cKey0.Position);
  		 for (colour=0;colour<maxlevel;colour++){
  			 led_sequence[colour]= rand()%3;//random sequence generator
  		 }
  		for(play=0;play<level;play++){

  		 for (show=0;show<level;show++){
  		 switch (led_sequence[show]){   //switch cases to display random sequence of the LEDs
  		 case 0: REDLED();
  		 break;
  		 case 1: BLUELED();
  		 break;
  		 case 2: GREENLED();
  		 break;
  		 }

  		 }


  		for(usertap=0;usertap<level;usertap++){//after random led sequence user will input using touchpad
  				ispressed=0;
  		  		 while(ispressed <2){
  		  			 	 TSS_Task();}
  			if(TSS1_cKey0.Position > 50) {check=0;}
  			if(TSS1_cKey0.Position <15) {check=1;}
  			if(TSS1_cKey0.Position <50 && TSS1_cKey0.Position >15) {check=2;}
  			switch(check){
  			case 0: REDLED();OFFLED;
  			break;
  			case 1: BLUELED();OFFLED:
  			break;
  			case 2: GREENLED();OFFLED;
  			break;
  			}
  			if (check!=led_sequence[usertap]){//when input is wrong, Orange led will blink twice
  					ORANGELED();
  					ORANGELED();

  					wait(2000);
  					goto start; // when player enters wrong sequence, the game will return to start
  			}

		}

  		TURQOISELED();//if input = led sequence, Turqoise led will blink twice and level increases
  		TURQOISELED();
  		wait(1000);
  		level++;
  		}
  	if (level=maxlevel){
  		PINKLED();
  		PINKLED();
  		PINKLED();
  	}
  }




  /* Don't write any code pass this line, or it will be deleted during code generation. */
  /* RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! */
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /* End of RTOS startup code.  */
  /* Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! */
  for(;;){}
  /* Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! */
} /* End of main routine. DO NOT MODIFY THIS TEXT!!! */

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/