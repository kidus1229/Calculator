#include"LPC214X.H"
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include"timer.h"
#include"lcd.h"
#include"keypad.h"
#include"system.h"

char res[10],num[10];
int val,display,result=-1;
char op,opp='*';

int main(void)
{
    LCD_INIT();
    LCD_CMD(0x01);
    LCD_STRING("**Calculator**");
    LCD_CMD(0x01);
 
    while(1){
        for(int i=0;i<10;i++)
        {            
            num[i]=get_key();
            LCD_CMD(0x0E);
            if(num[i] != 'e' && num[i] != 'c')
                LCD_CHAR(num[i]); 
            if(num[i] == '*' || num[i] == '/' || num[i] == '+' || num[i] == '-')
            {
                op = num[i];
                num[i] = '\0';
                if (num[0] != '\0')
                    val = atoi(num);
                result = GET_RESULT(result,val,opp);
                opp=op;
                break;
            }
            else if(num[i] == 'e')
            {
                num[i] = '\0';
                val = atoi(num);
                result = GET_RESULT(result,val,op);
                LCD_CMD(0x01);
                LCD_CMD(0x0C);
                if(result == 0)
                {
                    res[9]='0';
                }
                display = result;
                for(int i=0;i<10;i++)
                {
                    if(display > 0)
                    res[i] = display % 10 + '0';
                    display = display / 10;
                }
                for(int i=10;i>=0;i--)
                {
                    if(res[i] != '\0')
                    {
                        LCD_CHAR(res[i]);
                    }
                }
                val=-1;
                for(int i=0;i<10;i++)
                {
                    res[i] = '\0';
                }
                break;
            }
            else if(num[i] == 'c')
            {
                LCD_CMD(0x01);
                result = 0;
                val = -1;
                for(int i=0;i<10;i++)
                {
                    res[i] = '\0';
                }
                break;
            }
        }
    }
}