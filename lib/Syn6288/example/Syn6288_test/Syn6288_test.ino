#include <Syn6288.h>

Syn6288 syn;
uint8_t text1[]={0xB3,0xC9,0xB6,0xBC,0xBC,0xAB,0xC8,0xA4,0xBF,0xC6,0xBC,0xBC,0xD3,0xD0,0xCF,0xDE,0xB9,0xAB,0xCB,0xBE}; //成都极趣科技有限公司
uint8_t text2[]={0x77,0x77,0x77,0x2E,0x64,0x66,0x72,0x6F,0x62,0x6F,0x74,0x2E,0x63,0x6F,0x6D,0x2E,0x63,0x6E}; //www.dfrobot.com.cn
uint8_t text3[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};//0,1,2,3,4,5,6,7,8,9
void setup()
{
Serial.begin(9600);
//syn.Slaveboudset(19200);
//Serial.begin(19200);
}
void loop()
{
syn.play(text1,sizeof(text1),1);//播放文本1，选择背景音乐1
syn.play(text2,sizeof(text2),2);//播放文本2，选择背景音乐2
syn.play(text3,sizeof(text3),3);//播放文本3，选择背景音乐3
}
