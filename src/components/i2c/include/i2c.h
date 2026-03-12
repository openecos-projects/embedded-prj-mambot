#ifndef __I2C_H__
#define __I2C_H__

#include "i2c_type.h"

/**
 * @brief I2C初始化函数
 * 
 * 根据给定的配置结构体，初始化I2C模块。
 * 
 * @param config 指向i2c_config_t结构体的指针，包含I2C预分频寄存器值
 */
void i2c_init(i2c_config_t* config);

/**
 * @brief I2C写入多个字节函数
 * 
 * 向指定的I2C从设备写入多个字节数据。
 * 
 * @param slave_addr I2C从设备地址
 * @param reg_addr 寄存器地址
 * @param reg_addr_len 寄存器地址长度，I2C_REG_8或I2C_REG_16
 * @param data 指向要写入数据的指针
 * @param len 要写入的字节数
 */
void i2c_write_nbyte(uint8_t slave_addr, uint16_t reg_addr, i2c_reg_addr_len_t reg_addr_len,uint8_t* data, uint32_t len);

/**
 * @brief I2C读取多个字节函数
 * 
 * 从指定的I2C从设备读取多个字节数据。
 * 
 * @param slave_addr I2C从设备地址
 * @param reg_addr 寄存器地址
 * @param reg_addr_len 寄存器地址长度，I2C_REG_8或I2C_REG_16
 * @param data 指向存储读取数据的指针
 * @param len 要读取的字节数
 */
void i2c_read_nbyte(uint8_t slave_addr, uint16_t reg_addr, i2c_reg_addr_len_t reg_addr_len,uint8_t* data, uint32_t len);
#endif
