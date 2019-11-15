/*-----------------------------------------------
  名称：外部中断1电平触发
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：通过中断接口P3.3连接的独立按键测试，按一次P1.0口的LED灯反向，
        作用效果和中断0相同，启用按键去抖，所以适合实际按键
------------------------------------------------*/
#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义

sbit LED=P1^0; //定义LED端口

void DelayUs2x(unsigned char t);//us级延时函数声明 
void DelayMs(unsigned char t); //ms级延时
/*------------------------------------------------
                    主程序
------------------------------------------------*/
main()
{
  LED=0;         //LED灯点亮
  EA=1;          //全局中断开
  EX1=1;         //外部中断0开
  IT1=0;         //琁T1=0表示电平触发
  while(1)
  {
                 //在此添加其他程序
  }
}
/*------------------------------------------------
                 外部中断程序
------------------------------------------------*/
void ISR_INT1(void) interrupt 2 
{
 
 if(!INT1)
   {
   DelayMs(10);//在此处可以添加去抖动程序，防止按键抖动造成错误
   if(!INT1)
   while(!INT1);//等待按键释放
     {
     LED=!LED;   
     }
   }
}

/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
