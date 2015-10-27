/*----------------------------------------Copyright (c)---------------------------------------------------
ÉîÛÚÊÐ¿­ÈðÀ³¿Æ¼¼¿ª·¢

*
*      ÉîÛÚÊÐ¿­ÈðÀ³¿Æ¼¼¿ª·¢Ìá¹©µÄËùÓÐST¡¢TI¡¢Freescale¡¢AlteraµÈÆ½Ì¨µÄÀý³Ì¡¢ÎÄµµ¡¢·½°¸µÈ×ÊÁÏÐÅÏ¢Ö¼ÔÚÎªÑ§Ï°ÕßÌá¹©Ñ§Ï°²Î¿¼£¬ÈôÊ¹ÓÃÕßÔÚÊ¹ÓÃ¹ý³ÌÖÐÒòÈÎºÎÔ­ÒòÔì³ÉÖ±½Ó»ò¼ä½ÓµÄËðÊ§£¬ÉîÛÚÊÐ¿­ÈðÀ³¿Æ¼¼¿ª·¢²»³Ðµ£ÈÎºÎÔðÈÎ¡£
*
*
*
*                                                                             ÉîÛÚÊÐ¿­ÈðÀ³¿Æ¼¼¿ª·¢*
*----------------------------------------------------------------------------------------------------------
* File name:          spi_flash.c
* Author:             alvan wang
* Version:            V1.0
* Date:               2014-01-03
* Description:
* Function List:
* History:
*-----------------------------------------------------------------------------------------------------------
*/

#include "stm32f4xx.h"
#include "spi_flash.h"
#include <stdio.h>
#include <stdint.h>


/*
*--------------------------------------------------------------------------------------------------------
* Function:         spi_flash_init
* Description:      ¸Ãº¯Êý¶Ôspi_flash ÓÃµ½µÄSPI1½øÐÐ³õÊ¼»¯£¬spi_flash_cs--GPIOA.4,spi1_sck--GPIOA.5,
                    spi1_miso--GPIOA.6,spi1_mosi--GPIOA.7
* Input:            none
* Output:           none
* Return:           none
* Created by:       alvan wang
* Created date:     2014-01-02
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void  spi_flash_init (void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

    /*!< Enable the SPI clock */
    sFLASH_SPI_CLK_INIT(sFLASH_SPI_CLK, ENABLE);

    /*!< Enable GPIO clocks */
    RCC_AHB1PeriphClockCmd(sFLASH_SPI_SCK_GPIO_CLK  | sFLASH_SPI_MISO_GPIO_CLK |
                           sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_CS_GPIO_CLK, ENABLE);

    /*!< SPI pins configuration *************************************************/

    /*!< Connect SPI pins to AF5 */
    GPIO_PinAFConfig(sFLASH_SPI_SCK_GPIO_PORT, sFLASH_SPI_SCK_SOURCE, sFLASH_SPI_SCK_AF);
    GPIO_PinAFConfig(sFLASH_SPI_MISO_GPIO_PORT, sFLASH_SPI_MISO_SOURCE, sFLASH_SPI_MISO_AF);
    GPIO_PinAFConfig(sFLASH_SPI_MOSI_GPIO_PORT, sFLASH_SPI_MOSI_SOURCE, sFLASH_SPI_MOSI_AF);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

    /*!< SPI SCK pin configuration */
    GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
    GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    /*!< SPI MOSI pin configuration */
    GPIO_InitStructure.GPIO_Pin =  sFLASH_SPI_MOSI_PIN;
    GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

    /*!< SPI MISO pin configuration */
    GPIO_InitStructure.GPIO_Pin =  sFLASH_SPI_MISO_PIN;
    GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH Card CS pin in output pushpull mode ********************/
    GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);

    /*!< SPI configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;

    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(sFLASH_SPI, &SPI_InitStructure);

    /*!< Enable the sFLASH_SPI  */
    SPI_Cmd(sFLASH_SPI, ENABLE);
}

/*
*--------------------------------------------------------------------------------------------------------
* Function:     	spi_flash_send_byte()
* Description:      SPI1·¢ËÍÒ»¸ö×Ö½ÚµÄÊý¾Ý
* Input:            Òª·¢ËÍµ½Êý¾Ý
* Output:           none
* Return:           ½ÓÊÕµ½µÄÊý¾Ý
* Created by:       alvan wang
* Created date:     2014-01-02
* Others:
*---------------------------------------------------------------------------------------------------------
*/
u8 spi_flash_send_byte (u8 data)
{
    while((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET);   /* µÈ´ý·¢ËÍ»º³åÇø¿Õ                             */
    SPI1->DR = data;                                 /* ·¢ËÍÒ»¸ö×Ö½ÚÊý¾Ý                             */
    while((SPI1->SR & SPI_I2S_FLAG_RXNE) == RESET);  /* µÈ´ý½ÓÊÕÍêÒ»¸ö×Ö½ÚÊý¾Ý                       */
    return(SPI1->DR);                                /* ·µ»Ø½ÓÊÕµ½µÄÊý¾Ý                             */
}

/*
*--------------------------------------------------------------------------------------------------------
* Function:         spi_flash_cs_low
* Description:      spi_flash_csÊä³öµÍ
* Input:            none
* Output:           none
* Return:           none
* Created by:       alvan wang
* Created date:     2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void spi_flash_cs_low (void)
{
    GPIO_ResetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN);
}

/*
*--------------------------------------------------------------------------------------------------------
* Function:         spi_flash_cs_high
* Description:      spi_flash_csÊä³ö¸ß
* Input:            none
* Output:           none
* Return:           none
* Created by:       alvan wang
* Created date:     2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void spi_flash_cs_high (void)
{
    GPIO_SetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN);
}

/*
*--------------------------------------------------------------------------------------------------------
* Function:         spi_flash_write_enable
* Description:      Ð¾Æ¬Ð´Ê¹ÄÜ
* Input:            none
* Output:           none
* Return:           none
* Created by:       alvan wang
* Created date:     2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void spi_flash_write_enable(void)
{
    spi_flash_cs_low();
    spi_flash_send_byte(SPI_FLASH_WRITE_ENABLE);
    spi_flash_cs_high();
}

/*
*--------------------------------------------------------------------------------------------------------
* Function:         spi_flash_wait_for_write_end
* Description:      µÈ´ýÐ´½áÊø
* Input:            none
* Output:           none
* Return:           none
* Created by:       alvan wang
* Created date:     2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void spi_flash_wait_for_write_end (void)
{
    u8 flash_status = 0;

    spi_flash_cs_low();
    spi_flash_send_byte(SPI_FLASH_READ_STATUS_REG);
    do
    {
        flash_status = spi_flash_send_byte(0x00);
    }while ((flash_status & 0x01) == 0x01);

    spi_flash_cs_high();
}

/*
*--------------------------------------------------------------------------------------------------------
* Function:       spi_flash_read_device_ID
* Description:    ¶ÁÈ¡Ð¾Æ¬ID
* Input:          none
* Output:         Ð¾Æ¬ID
* Return:         none
* Created by:     alvan wang
* Created date:   2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
uint8_t spi_flash_read_device_ID(void)
{
    u8 data_buf;

    spi_flash_cs_low();
    spi_flash_send_byte(SPI_FLASH_DEVICE_ID);
    spi_flash_send_byte(0x00);
    spi_flash_send_byte(0x00);
    spi_flash_send_byte(0x00);
    data_buf = spi_flash_send_byte(0x00);
    spi_flash_cs_high();

    return 	data_buf;
}

/*
*--------------------------------------------------------------------------------------------------------
* Function:         spi_flash_sector_erase
* Description:      ÉÈÇø²Á³ýº¯Êý
* Input:            Òª²Á³ýµÄÉÈÇøµØÖ·
* Output:           none
* Return:           none
* Created by:       alvan wang
* Created date:     2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void spi_flash_sector_erase (uint32_t sector_addr)
{
    spi_flash_write_enable();

    spi_flash_cs_low();
    spi_flash_send_byte(SPI_FLASH_SECTOR_ERASE);
    spi_flash_send_byte((sector_addr & 0xFFFFFF) >> 16);
    spi_flash_send_byte((sector_addr & 0xFFFF) >> 8);
    spi_flash_send_byte(sector_addr & 0xFF);
    spi_flash_cs_high();

    spi_flash_wait_for_write_end();
}

/*
*--------------------------------------------------------------------------------------------------------
* Function:         spi_flash_block_erase
* Description:      ¿é²Á³ýº¯Êý
* Input:            Òª²Á³ýµÄ¿éµØÖ·
* Output:           none
* Return:           none
* Created by:       alvan wang
* Created date:     2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void spi_flash_block_erase (uint32_t block_addr)
{
    spi_flash_write_enable();

    spi_flash_cs_low();
    spi_flash_send_byte(SPI_FLASH_BLOCK_ERASE);
    spi_flash_send_byte((block_addr & 0xFFFFFF) >> 16);
    spi_flash_send_byte((block_addr & 0xFFFF) >> 8);
    spi_flash_send_byte(block_addr & 0xFF);
    spi_flash_cs_high();

    spi_flash_wait_for_write_end();
}

/*
*--------------------------------------------------------------------------------------------------------
* Function:           spi_flash_chip_erase
* Description:        È«Æ¬²Á³ýº¯Êý
* Input:              none
* Output:             none
* Return:             none
* Created by:         alvan wang
* Created date:       2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void spi_flash_chip_erase (void)
{
    spi_flash_write_enable();

    spi_flash_cs_low();
    spi_flash_send_byte(SPI_FLASH_CHIP_ERASE);
    spi_flash_cs_high();

    spi_flash_wait_for_write_end();
}


/*
*--------------------------------------------------------------------------------------------------------
* Function:           spi_flash_page_write
* Description:        Ð´Êý¾Ýº¯Êý
* Input:              write_addr£ºÐ´ÈëµÄÊý¾ÝµØÖ·
                      p_buffer£ºÒªÐ´ÈëµÄÊý¾ÝÖ¸Õë
                      num_byte_to_write£ºÐ´ÈëµÄÊý¾ÝÊýÁ¿(×î´óÎª256×Ö½Ú)
* Output:             none
* Return:             none
* Created by:         alvan wang
* Created date:       2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void spi_flash_page_write (u32 write_addr, u8* p_buffer, u16 num_byte_to_write)
{
    spi_flash_write_enable();

    spi_flash_cs_low();
    spi_flash_send_byte(SPI_FLASH_PAGE_PROGRAM);
    spi_flash_send_byte((write_addr & 0xFFFFFF) >> 16);
    spi_flash_send_byte((write_addr & 0xFFFF) >> 8);
    spi_flash_send_byte(write_addr & 0xFF);
    while (num_byte_to_write--)
    {
        spi_flash_send_byte(*p_buffer);
        p_buffer++;
    }
    spi_flash_cs_high();
    spi_flash_wait_for_write_end();
}


/*
*--------------------------------------------------------------------------------------------------------
* Function:           spi_flash_Write
* Description:        Ð´Êý¾Ýº¯Êý
* Input:              write_addr£ºÐ´ÈëµÄÊý¾ÝµØÖ·
                      p_buffer£ºÒªÐ´ÈëµÄÊý¾ÝÖ¸Õë
                      num_byte_to_write£ºÐ´ÈëµÄÊý¾ÝÊýÁ¿
* Output:             none
* Return:             none
* Created by:         alvan wang
* Created date:       2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void spi_falsh_write (uint32_t write_addr, uint8_t* p_buffer, uint16_t num_byte_to_write)
{
    unsigned int num_of_page = 0, num_of_sigle = 0, page_addr = 0,
            count = 0, temp = 0, byte_addr = write_addr;

    page_addr = byte_addr  % SPI_FLASH_PAGE_SIZE;
    count = SPI_FLASH_PAGE_SIZE - page_addr;
    num_of_page =  num_byte_to_write / SPI_FLASH_PAGE_SIZE;
    num_of_sigle = num_byte_to_write % SPI_FLASH_PAGE_SIZE;

    if (page_addr == 0)
    {
        if (num_of_page == 0) /* num_byte_to_write < SPI_FLASH_PageSize */
        {
            if((byte_addr % 4096) == 0)
            {
                spi_flash_sector_erase(byte_addr);
            }
            spi_flash_page_write (byte_addr, p_buffer, num_byte_to_write);
        }
        else /* num_byte_to_write > SPI_FLASH_PageSize */
        {
            while (num_of_page--)
            {
                if((byte_addr % 4096) == 0)
                {
                    spi_flash_sector_erase(byte_addr);
                }

                spi_flash_page_write (byte_addr, p_buffer, SPI_FLASH_PAGE_SIZE);
                byte_addr +=  SPI_FLASH_PAGE_SIZE;
                p_buffer += SPI_FLASH_PAGE_SIZE;
            }

            if((byte_addr % 4096) == 0)
            {
                spi_flash_sector_erase(byte_addr);
            }

            spi_flash_page_write (byte_addr, p_buffer, num_of_sigle);
        }
    }
    else
    {
        if (num_of_page == 0) /* num_byte_to_write < SPI_FLASH_PageSize */
        {
            if (num_of_sigle > count) /* (num_byte_to_write + write_addr) > SPI_FLASH_PageSize */
            {
                temp = num_of_sigle - count;
                if((byte_addr % 4096) == 0)
                {
                    spi_flash_sector_erase(byte_addr);
                }
                spi_flash_page_write (byte_addr, p_buffer, count);
                byte_addr +=  count;
                p_buffer += count;
                if((byte_addr % 4096) == 0)
                {
                    spi_flash_sector_erase(byte_addr);
                }
                spi_flash_page_write (byte_addr, p_buffer, temp);
            }
            else
            {
                if((byte_addr % 4096) == 0)
                {
                    spi_flash_sector_erase(byte_addr);
                }
                spi_flash_page_write (byte_addr, p_buffer, num_byte_to_write);
            }
        }
        else /* num_byte_to_write > SPI_FLASH_PageSize */
        {
            num_byte_to_write -= count;
            num_of_page =  num_byte_to_write / SPI_FLASH_PAGE_SIZE;
            num_of_sigle = num_byte_to_write % SPI_FLASH_PAGE_SIZE;

            if((byte_addr % 4096) == 0)
            {
                spi_flash_sector_erase(byte_addr);
            }
            spi_flash_page_write (byte_addr, p_buffer, count);
            byte_addr +=  count;
            p_buffer += count;

            while (num_of_page--)
            {
                if((byte_addr % 4096) == 0)
                {
                    spi_flash_sector_erase(byte_addr);
                }
                spi_flash_page_write (byte_addr, p_buffer, SPI_FLASH_PAGE_SIZE);
                byte_addr +=  SPI_FLASH_PAGE_SIZE;
                p_buffer += SPI_FLASH_PAGE_SIZE;
            }

            if (num_of_sigle != 0)
            {
                if((byte_addr % 4096) == 0)
                {
                    spi_flash_sector_erase(byte_addr);
                }
                spi_flash_page_write (byte_addr, p_buffer, num_of_sigle);
            }
        }
    }
}

/*
*--------------------------------------------------------------------------------------------------------
* Function:         spi_falsh_read
* Description:      ¶ÁÊý¾Ýº¯Êý
* Input:            read_addr£º¶ÁÈ¡µÄÊý¾ÝµØÖ·
                    num_byte_to_write£º¶ÁÈ¡Êý¾ÝµÄÊýÁ¿
* Output:           p_buffer£º¶ÁÈ¡Êý¾ÝµÄ»º³åÇøÖ¸Õë
* Return:           none
* Created by:       alvan wang
* Created date:     2014-01-03
* Others:
*---------------------------------------------------------------------------------------------------------
*/
void spi_falsh_read (u32 read_addr, u8* p_buffer, u16 num_byte_to_read)
{
    spi_flash_cs_low();
    spi_flash_send_byte(SPI_FLASH_FAST_READ_DATA);
    spi_flash_send_byte((read_addr & 0xFFFFFF) >> 16);
    spi_flash_send_byte((read_addr & 0xFFFF) >> 8);
    spi_flash_send_byte(read_addr & 0xFF);
    spi_flash_send_byte(0x00);

    while (num_byte_to_read--)
    {
        *p_buffer = spi_flash_send_byte(0xff);
        p_buffer++;
    }
    spi_flash_cs_high();
}

void spi_flash_test(void)
{
    spi_flash_init();
    printf("Writting data\r\n");
    uint32_t i;
    for(i = 0; i <68000000; ++i)
    {
        uint8_t data = 0xAA;
        spi_falsh_write(i,&data,1);
        spi_falsh_read(i,&data,1);
        if(data != 0xAA)
            printf("Unreachable memory, address: 0x%x",i);
        if(i%1000 == 0)
            printf("checked %d Byte Memory",i);
    }
}

