/*******************************************************************************************************************
 * x02_menu.h
 *
 * Created: 13.07.2024 
 *  Author: Wiki
 */ 
#include "_include.h"
#ifdef _INC_x02_MENU_H

#include "LCD_application.h"
///#include "converion_methods.h"

/********************************************************************************************************************
 * @name		MenuApplication: Ref(LCD_application, ConvertTime)
 * @brief		Class that call other class throught reference
 * @note	    Inheritace two children class
 *              This calass is created to manipulate aplication 
 */
class MenuApplication_1x4
{
private:
//**********************************************
// Reference variables to external class objects
    LCD_application&    Ref_LCD_application;
    //ConvertTime&        RefConvertTime;
    KeyPad1x4&          RefKeypad1x4;
//==============================================
    char arrChars1[4];
    char arrChars2[4];
    volatile uint8_t _keypad_state;
    volatile bool _display_data_order_active;
    volatile uint8_t _data_from_keypad_IRQ;
//==============================================
public:
//==============================================================================================================
// Setup external reference for internal manipulation. Now inside this class access is set to intialized external class
    MenuApplication_1x4(LCD_application& Ref_LCD_application,  KeyPad1x4& RefKeypad1x4):
        Ref_LCD_application(Ref_LCD_application), RefKeypad1x4(RefKeypad1x4){;}
    ~MenuApplication_1x4(){;}
//==============================================================================================================
    void Display_App_Test1(void);
    void Display_App_Test2(void);
    void IRQ_TIM1_Display(void);
    void IRQ_TIM2_Keypad(void);
//==============================================
};
//===================================================================================================================
#endif // _INC_x01_MENU_H
//===================================================================================================================