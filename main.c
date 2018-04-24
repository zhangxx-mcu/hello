//zhangxx modifed

#include "LPC11XX.H"
uint8_t table[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
/******************************************************************************
* FunctionName   : Delay()
* Description    : ��ʱ����
* EntryParameter : None
* ReturnValue    : None
*******************************************************************************/
void delay()
{
    uint16_t i = 10000;
    while(i--);
}
/******************************************************************************
* FunctionName   : GPIOInit()
* Description    : �����IO�ڳ�ʼ��������ռ��P2.0��P2.7��P2.8��P2.11
* EntryParameter : None
* ReturnValue    : None
*******************************************************************************/
void GPIOInit(void)
{
    LPC_GPIO2 ->DIR = 0xFFF;				//����P2_0~P2_11Ϊ���
}
/******************************************************************************
* FunctionName   : Display()
* Description    : ��ʾ����
* EntryParameter : value������ʾ����
* ReturnValue    : None
*******************************************************************************/
void Display(uint32_t value)
{

    uint32_t i;
    uint32_t temp;
    i = value;

    temp = table[i / 1000];
    temp &= ~(1 << 8);
    temp |= (1 << 9);
    temp |= (1 << 10);
    temp |= (1 << 11);
    LPC_GPIO2->DATA	= temp;
    delay();
    temp |= 0xFF;
    LPC_GPIO2->DATA |= (1 << 8);

    temp = table[i % 1000 / 100];
    temp |= (1 << 8);
    temp &= ~(1 << 9);
    temp |= (1 << 10);
    temp |= (1 << 11);
    LPC_GPIO2->DATA	= temp;
    delay();
    temp |= 0xFF;
    LPC_GPIO2->DATA |= (1 << 9);

    temp = table[i % 1000 % 100 / 10];
    temp |= (1 << 8);
    temp |= (1 << 9);
    temp &= ~(1 << 10);
    temp |= (1 << 11);
    LPC_GPIO2->DATA	= temp;
    delay();
    temp |= 0xFF;
    LPC_GPIO2->DATA |= (1 << 10);

    temp = table[i % 1000 % 100 % 10];
    temp |= (1 << 8);
    temp |= (1 << 9);
    temp |= (1 << 10);
    temp &= ~(1 << 11);
    LPC_GPIO2->DATA	= temp;
    delay();
    temp |= 0xFF;
    LPC_GPIO2->DATA |= (1 << 11);
}
/******************************************************************************
* FunctionName   : main()
* Description    : ������
* EntryParameter : None
* ReturnValue    : None
*******************************************************************************/
int main()
{
    GPIOInit();
    while(1)
    {
        Display(1234);
//     LPC_GPIO2->DATA = 0x00;
    }
}
