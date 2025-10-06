/**
 * @brief  延时函数 (11.0592MHz)
 * @param  xms: 延时毫秒数
 * @retval 无
 */

void Delay(unsigned int xms)	
{
	unsigned char data i, j;

    while(xms--){
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);
    }
}
