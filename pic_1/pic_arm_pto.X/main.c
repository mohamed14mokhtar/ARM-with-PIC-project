/* 
 * File:   main.c
 * Author: mokhtar
 *
 * Created on September 1, 2024, 2:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#define SLAVE_ADDRESS 0x50

 void interrupt_usart_rx(void);
 void int0_interrupt (void);
/********************************************* UART ***********************************************************/
usart_t usart_1 ={
   .baudrate= 9600,.buadrate_gen=BAUDRATE_ASY_8BIT_LOW_SPEED ,.usart_tx.usart_tx_enable=USART_ASYNCHRONOUS_TX_ENABLE,
   .usart_tx.usart_tx_interrupt_enable=USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE,
   .usart_tx.usart_tx_9bits_enable=USART_ASYNCHRONOUS_9BITS_TX_DISABLE,.usart_rx.usart_rx_enable=USART_ASYNCHRONOUS_RX_ENABLE,
   .usart_rx.usart_rx_interrupt_enable=USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE,
   .usart_rx.usart_rx_9bits_enable=USART_ASYNCHRONOUS_9BITS_RX_DISABLE,.USART_RX_INTERRUPT_HANDLER=interrupt_usart_rx
};
ADC_conf_t ADC_ = {.ADC_CHANNAL_SELECT=ADC_CHANNEL_AN3,.ADC_interruptHandler=NULL,.Acquisition_time=ADC_12_TAD,
.Conversion_Clock=FOSC_div_16,.result_format=ADC_result_right,.voltage_ref=voltage_ref_disable};
ADC_conf_t ADC_2 = {.ADC_CHANNAL_SELECT=ADC_CHANNEL_AN0,.ADC_interruptHandler=NULL,.Acquisition_time=ADC_12_TAD,
.Conversion_Clock=FOSC_div_16,.result_format=ADC_result_right,.voltage_ref=voltage_ref_disable};
/********************************************* pins ***********************************************************/
pin_config_t LED_ROOM_1 = {.port=PORTC_INDEX,.pin=pin0,.logic=GPIO_LOW,.direction=GPIO_OUTPUT};
/********************************************* I2C ***********************************************************/
mssp_i2c_t mssp_i2c = {.i2c_clock=100000,.i2c_cfg.i2c_SMBus_control=I2C_SMBus_DISABLE,
.i2c_cfg.i2c_general_call=I2C_GENERAL_CALL_DISABLE,.i2c_cfg.i2c_master_rec_mode=I2C_MASTER_RECEIVE_DISABLE,
.i2c_cfg.i2c_mode=I2C_MSSP_MASTER_MODE,.i2c_cfg.i2c_mode_cfg=I2C_MASTER_MODE_DEFINED_CLOCK,
.I2C_DefaultInterruptHandler=NULL,.I2C_Report_Receive_Overflow=NULL,.I2C_Report_Write_Collision=NULL};
/********************************************* LCD ***********************************************************/
chr_lcd_4bit_t lcd_4bit = {.lcd_en.port=PORTD_INDEX,.lcd_en.pin=pin5,.lcd_en.direction=GPIO_OUTPUT,.lcd_en.logic=GPIO_LOW,
.lcd_rs.port=PORTD_INDEX,.lcd_rs.pin=pin6,.lcd_rs.direction=GPIO_OUTPUT,.lcd_rs.logic=GPIO_LOW,
.lcd_data[0].port=PORTD_INDEX,.lcd_data[0].pin=pin0,.lcd_data[0].direction=GPIO_OUTPUT,.lcd_data[0].logic=GPIO_LOW,
.lcd_data[1].port=PORTD_INDEX,.lcd_data[1].pin=pin1,.lcd_data[1].direction=GPIO_OUTPUT,.lcd_data[1].logic=GPIO_LOW,
.lcd_data[2].port=PORTD_INDEX,.lcd_data[2].pin=pin2,.lcd_data[2].direction=GPIO_OUTPUT,.lcd_data[2].logic=GPIO_LOW,
.lcd_data[3].port=PORTD_INDEX,.lcd_data[3].pin=pin3,.lcd_data[3].direction=GPIO_OUTPUT,.lcd_data[3].logic=GPIO_LOW};
/********************************************* CCP ***********************************************************/
ccp2_t ccp2_={.CCP2_handler = NULL ,.ccp2_mode=ccp2_pwm_initialize,.ccp2_pwm_frequence=10000,.pin_config.port=PORTC_INDEX,
.pin_config.pin=pin2,.pin_config.direction=GPIO_OUTPUT,.ccp2_timer2_postscaler_cfg=ccp2_Postscale_div_by_1,
.ccp2_timer2_prescaler_cfg=ccp2_prescale_div_by_1,.ccp2_mode_variant=ccp2_pwm_initialize};
ccp1_t ccp1_={.CCP1_handler = NULL ,.ccp1_mode=ccp1_pwm_initialize,.pwm_frequence=10000,.pin_config.port=PORTC_INDEX,
.pin_config.pin=pin2,.pin_config.direction=GPIO_OUTPUT,.timer2_postscaler_cfg=ccp1_Postscale_div_by_1,
.timer2_prescaler_cfg=ccp1_prescale_div_by_1,.ccp1_mode_variant=ccp1_pwm_initialize};
/********************************************* timer2 ***********************************************************/
Timer2_t Timer2 ={.Timer2_handler=NULL,
                    .timer1_preload_value=0,.timer2_postscaler_cfg=Postscale_div_by_1,
                    .timer2_prescaler_cfg=prescale_div_by_1};
/********************************************* MOTORS ***********************************************************/
motor_t motor_2 = {.motor_pin_config[0].port=PORTC_INDEX,.motor_pin_config[0].pin=pin1,.motor_pin_config[0].direction=GPIO_OUTPUT,
.motor_pin_config[1].port=PORTD_INDEX,.motor_pin_config[1].pin=pin7,.motor_pin_config[0].direction=GPIO_OUTPUT};
motor_t motor_1 = {.motor_pin_config[0].port=PORTC_INDEX,.motor_pin_config[0].pin=pin5,.motor_pin_config[0].direction=GPIO_OUTPUT,
.motor_pin_config[1].port=PORTC_INDEX,.motor_pin_config[1].pin=pin2,.motor_pin_config[0].direction=GPIO_OUTPUT};
/********************************************* INT ***********************************************************/
INTERRUPT_INTX_t INT_0 ={.EXT_INTERRUPTHANDLE =int0_interrupt,.edge=INTERRUPT_RISING_EDGE,.priority=INTERRUPT_HUGH_PRIORITY,
.sorce=INTERRUPT_INT0,.pin_config.pin=pin0,.pin_config.port=PORTB_INDEX,.pin_config.direction=GPIO_INPUT,.pin_config.logic=GPIO_LOW};
/*
 * 
 */
// global variable initialization 
Std_ReturnType ret ;             // return status 
uint8 dataSendUART[2] ={0} ;    // data transmit 
adc_result_t ADC_VALUE;          // data reed from ADC
volatile uint32 ADC_VALUE_2;        // data reed from ADC 2
volatile uint8 ADC_VALUE_convert;  // convert to uint8
volatile uint8 dataReceiveUART;
volatile uint8 tc74;             //temperature reed value 
uint8 i2c_ack;                   //i2c acknowladge 
volatile uint8 ds13_data[6];     //date reed value 
uint8 mes[5];                    //convert uint8 to string
uint8 ds13_data_decimal[6];      //date with decimal  
uint8 chick = 0 ;                     //while statement chick
int main() {
    
    intitialized_functions(); // initialization function
    
    /* lcd send data*/
    ret = lcd_4bit_send_string_pos(&lcd_4bit,1,2,"date : ");
    ret = lcd_4bit_send_string_pos(&lcd_4bit,2,2,"temperature : ");
    
    
    while(1){
       
        
        //ADC value reed
        ret = ADC_get_conversion_blocking(&ADC_,ADC_CHANNEL_AN3,&ADC_VALUE);/*min = 854 max max = 915 middle = 893 */
        ADC_VALUE_convert = ADC_VALUE - 854;
        dataSendUART[0]= ADC_VALUE_convert; //first byte send with UART
        
        ret = ADC_get_conversion_blocking(&ADC_,ADC_CHANNEL_AN0,&ADC_VALUE_2);
        ADC_VALUE_2 = ((ADC_VALUE_2*100)/1022);
        
       
            ret = morot_turn_left(&motor_2);
            ccp2_pwm_set_duty(ADC_VALUE_2);
            CCP2_select_statues(ccp2_pwm_initialize);
            
        //temp reed with i2c
        tc74_read_value(&mssp_i2c,ADDRESS_A7,REDISTER_READ_0,&tc74,&i2c_ack);
        dataSendUART[1]= tc74; //second byte send with UART
        sprintf(mes , "%i",tc74);
        ret = lcd_4bit_send_string_pos(&lcd_4bit,2,15,mes);
        if((tc74 > 25) && (tc74 <= 27)){
            ret = morot_turn_right(&motor_1);
            ccp1_pwm_set_duty(80);
            CCP1_select_statues(ccp1_pwm_initialize);
           }else if((tc74 > 27) && (tc74 <= 30)){
            ret = morot_turn_right(&motor_1);
            ccp1_pwm_set_duty(50);
            CCP1_select_statues(ccp1_pwm_initialize);
            } 
            else if((tc74 > 30) && (tc74 <= 33)){
            ret = morot_turn_right(&motor_1);
            ccp1_pwm_set_duty(20);
            CCP1_select_statues(ccp1_pwm_initialize);
            }
            else if(tc74 >= 34){
            ret = morot_turn_right(&motor_1);
            ccp1_pwm_set_duty(1);
            CCP1_select_statues(ccp1_pwm_initialize);
            }
           else{
            ret = morot_stop(&motor_1);
            CCP1_select_statues(ccp1_module_disabled);
            }
        
        /*temp more than or equal 40 */
        while(tc74 >= 40){
            ret = GPIO_pIN_TOGGLE_LOGIC(&LED_ROOM_1);
            lcd_4bit_send_command(&lcd_4bit,_LCD_CLEAR);
            ret = lcd_4bit_send_string_pos(&lcd_4bit,1,2,"wrong");
            __delay_ms(1);
            ret = lcd_4bit_send_string_pos(&lcd_4bit,1,8,"!");
            __delay_ms(1);
            ret = lcd_4bit_send_string_pos(&lcd_4bit,1,9,"!");
            __delay_ms(1);
            ret = lcd_4bit_send_string_pos(&lcd_4bit,1,10,"!");
            __delay_ms(1);
            ret = lcd_4bit_send_string_pos(&lcd_4bit,1,11,"!");
            __delay_ms(1);
            ret = lcd_4bit_send_string_pos(&lcd_4bit,1,12,"!");
            __delay_ms(1);
            ret = lcd_4bit_send_string_pos(&lcd_4bit,2,2,"temperature : ");
            ret = lcd_4bit_send_string_pos(&lcd_4bit,2,15,mes);
            __delay_ms(20);
            tc74_read_value(&mssp_i2c,ADDRESS_A7,REDISTER_READ_0,&tc74,&i2c_ack);
            dataSendUART[1]= tc74; //second byte send with UART
            sprintf(mes , "%i",tc74);
            lcd_4bit_send_command(&lcd_4bit,_LCD_CLEAR);
            for(uint8 i = 0 ; i< sizeof(dataSendUART); i++){
            ret = usart_ASYNC_write_byte_blocking(dataSendUART[i]);
            }
            chick = 1;  
        }
        if(1 == chick){
            chick = 0;
            ret = lcd_4bit_send_string_pos(&lcd_4bit,1,2,"date : ");
            ret = lcd_4bit_send_string_pos(&lcd_4bit,2,2,"temperature : ");
        }
        //date reed value 
        ds1307_read_values(&mssp_i2c,DS13_ADDRESS,ds13_data,&i2c_ack);
        for(uint8 i =0 ; i<6 ;i++){
            ds13_data_decimal[i] = convert_hex_to_dec(ds13_data[i]);  
        }
        /* send string to lcd  */
        sprintf(mes , "%i",ds13_data_decimal[3]);
        ret = lcd_4bit_send_string_pos(&lcd_4bit,1,8,mes);
        ret = lcd_4bit_send_char_data_pos(&lcd_4bit,1,11,'/');
        sprintf(mes , "%i",ds13_data_decimal[4]);
        ret = lcd_4bit_send_string_pos(&lcd_4bit,1,12,mes);
        ret = lcd_4bit_send_char_data_pos(&lcd_4bit,1,14,'/');
        sprintf(mes , "%i",ds13_data_decimal[5]);
        ret = lcd_4bit_send_string_pos(&lcd_4bit,1,15,mes);
        
        /* send data throw UART*/
        for(uint8 i = 0 ; i< sizeof(dataSendUART); i++){
            ret = usart_ASYNC_write_byte_blocking(dataSendUART[i]);
        }
        
        if(ADC_VALUE_convert > 38 ){
            GPIO_pIN_WRITE_LOGIC(&LED_ROOM_1,GPIO_LOW);
        }
    }
    return (EXIT_SUCCESS);
}




void intitialized_functions (void){
    usart_ASYNC_init(&usart_1);
    ret = ADC_inti(&ADC_);
    ret = ADC_inti(&ADC_2);
    ret = GPIO_pIN_INTIALIZE(&LED_ROOM_1);
    ret = MSSP_I2C_Init(&mssp_i2c);
    ret = lcd_4bit_intialize(&lcd_4bit);
    ret = Timer2_init(&Timer2);
    ret = ccp2_init(&ccp2_);
    ret = motor_intialize(&motor_2);
    ret = Interrupt_Intx_Inti(&INT_0);
    ret = ccp1_init(&ccp1_);
    ret = motor_intialize(&motor_1);
}

 

 void interrupt_usart_rx(void){
    volatile uint8 ret_data = 0;
    ret = usart_ASYNC_read_byte_blocking (&dataReceiveUART);
        if(dataReceiveUART == 'a'){
        }
}
 
uint8 convert_hex_to_dec(uint8 num){
    uint8 l_num = num >> 4;
    return (num - (l_num*6));

}

void int0_interrupt (void){
     if(ADC_VALUE_convert > 38 ){
         GPIO_PORT_WRITE_LOGIC(&LED_ROOM_1,GPIO_LOW);
     }else{
         ret = GPIO_pIN_TOGGLE_LOGIC(&LED_ROOM_1);
     }
}
