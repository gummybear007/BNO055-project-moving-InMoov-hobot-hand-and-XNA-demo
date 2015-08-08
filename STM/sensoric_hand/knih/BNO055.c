#include "BNO055.h"
#include <stm32l1xx.h>
#include "i2c.h"
//#include "systick_ms.h"
#include "main.h"

void init_imu(unsigned char adr)
{

	unsigned char temp;
//	write_byte_am(adr,BNO055_AXIS_MAP_CONFIG_ADDR,0x24);
//	write_byte_am(adr,BNO055_AXIS_MAP_SIGN_ADDR,0x03);
	write_byte_am(adr,BNO055_OPR_MODE_ADDR,OPERATION_MODE_NDOF);
	write_byte_am(adr,BNO055_UNIT_SEL_ADDR,0x0E);
}


void init_imu2(unsigned char adr)
{

	unsigned char temp;
	
	//write_byte_am2(adr,BNO055_AXIS_MAP_SIGN_ADDR,0x06);
	write_byte_am2(adr,BNO055_OPR_MODE_ADDR,OPERATION_MODE_NDOF);
	write_byte_am2(adr,BNO055_UNIT_SEL_ADDR,0x0E);
}

unsigned char cti_reg(unsigned char ad,int dev,unsigned char adr)
{
	unsigned char temp;
	if(dev)
	{
		temp=read_byte_am(adr,ad);
	}
	else
	{
		//temp=read_byte_g(adr,ad);
	}
	return temp;
}

void cti_quat(float *qw, float *qx,float *qy, float *qz,unsigned char adr)
{
	unsigned char qxl,qxh,qyl,qyh,qzl,qzh,qwl,qwh;
	long xi,yi,zi,wi;
	float recipNorm;
	qwl=read_byte_am(adr,BNO055_QUATERNION_DATA_W_LSB_ADDR);
	qwh=read_byte_am(adr,BNO055_QUATERNION_DATA_W_MSB_ADDR);
	qxl=read_byte_am(adr,BNO055_QUATERNION_DATA_X_LSB_ADDR);
	qxh=read_byte_am(adr,BNO055_QUATERNION_DATA_X_MSB_ADDR);
	qyl=read_byte_am(adr,BNO055_QUATERNION_DATA_Y_LSB_ADDR);
	qyh=read_byte_am(adr,BNO055_QUATERNION_DATA_Y_MSB_ADDR);
	qzl=read_byte_am(adr,BNO055_QUATERNION_DATA_Z_LSB_ADDR);
	qzh=read_byte_am(adr,BNO055_QUATERNION_DATA_Z_MSB_ADDR);
	
	wi=(float)(qwh<<8|qwl);
	xi=(float)(qxh<<8|qxl);
	yi=(float)(qyh<<8|qyl);
	zi=(float)(qzh<<8|qzl);

	if(xi&1<<15)
		xi=	-(float)(0xFFFF-xi);
	if(yi&1<<15)
		yi=	-(float)(0xFFFF-yi);
	if(zi&1<<15)
		zi=	-(float)(0xFFFF-zi);
	if(wi&1<<15)
		wi=	-(float)(0xFFFF-wi);	

	
	recipNorm = invSqrt(wi * wi + xi * xi + yi * yi + zi * zi);
	*qw= wi;// * recipNorm;
	*qx= xi;// * recipNorm;
	*qy= yi;// * recipNorm;
	*qz= zi;// * recipNorm;
	
}

void cti_quat2(float *qw, float *qx,float *qy, float *qz,unsigned char adr)
{
	unsigned char qxl,qxh,qyl,qyh,qzl,qzh,qwl,qwh;
	long xi,yi,zi,wi;
	float recipNorm;
	qwl=read_byte_am2(adr,BNO055_QUATERNION_DATA_W_LSB_ADDR);
	qwh=read_byte_am2(adr,BNO055_QUATERNION_DATA_W_MSB_ADDR);
	qxl=read_byte_am2(adr,BNO055_QUATERNION_DATA_X_LSB_ADDR);
	qxh=read_byte_am2(adr,BNO055_QUATERNION_DATA_X_MSB_ADDR);
	qyl=read_byte_am2(adr,BNO055_QUATERNION_DATA_Y_LSB_ADDR);
	qyh=read_byte_am2(adr,BNO055_QUATERNION_DATA_Y_MSB_ADDR);
	qzl=read_byte_am2(adr,BNO055_QUATERNION_DATA_Z_LSB_ADDR);
	qzh=read_byte_am2(adr,BNO055_QUATERNION_DATA_Z_MSB_ADDR);
	
	wi=(float)(qwh<<8|qwl);
	xi=(float)(qxh<<8|qxl);
	yi=(float)(qyh<<8|qyl);
	zi=(float)(qzh<<8|qzl);

	if(xi&1<<15)
		xi=	-(float)(0xFFFF-xi);
	if(yi&1<<15)
		yi=	-(float)(0xFFFF-yi);
	if(zi&1<<15)
		zi=	-(float)(0xFFFF-zi);
	if(wi&1<<15)
		wi=	-(float)(0xFFFF-wi);	

	
	recipNorm = invSqrt(wi * wi + xi * xi + yi * yi + zi * zi);
	*qw= wi;// * recipNorm;
	*qx= xi;// * recipNorm;
	*qy= yi;// * recipNorm;
	*qz= zi;// * recipNorm;
	
}
void cti_eul(float *roll, float *pitch,float *yaw,unsigned char adr)
{
	unsigned char qxl,qxh,qyl,qyh,qzl,qzh,qwl,qwh;
	long xi,yi,zi,wi,recipNorm;

	qxl=read_byte_am2(adr,BNO055_EULER_R_LSB_ADDR);
	qxh=read_byte_am2(adr,BNO055_EULER_R_MSB_ADDR);
	qyl=read_byte_am2(adr,BNO055_EULER_P_LSB_ADDR);
	qyh=read_byte_am2(adr,BNO055_EULER_P_MSB_ADDR);
	qzl=read_byte_am2(adr,BNO055_EULER_H_LSB_ADDR);
	qzh=read_byte_am2(adr,BNO055_EULER_H_MSB_ADDR);
	

	xi=(float)(qxh<<8|qxl);
	yi=(float)(qyh<<8|qyl);
	zi=(float)(qzh<<8|qzl);
	
	if(xi&1<<15)
		xi=	-(float)(0xFFFF-xi);
	if(yi&1<<15)
		yi=	-(float)(0xFFFF-yi);
	if(zi&1<<15)
		zi=	-(float)(0xFFFF-zi);
	
		*roll= wi;// * recipNorm;
	*pitch= xi;// * recipNorm;
	*yaw= yi;

}

void cti_acc(float *x, float *y,float *z,unsigned char adr)
{
		
		unsigned char xl,xh,yl,yh,zl,zh;
	long xi,yi,zi,wi,recipNorm;

	xl=read_byte_am(adr,BNO055_ACCEL_DATA_X_LSB_ADDR);
	xh=read_byte_am(adr,BNO055_ACCEL_DATA_X_MSB_ADDR);
	yl=read_byte_am(adr,BNO055_ACCEL_DATA_Y_LSB_ADDR);
	yh=read_byte_am(adr,BNO055_ACCEL_DATA_Y_MSB_ADDR);
	zl=read_byte_am(adr,BNO055_ACCEL_DATA_Z_LSB_ADDR);
	zh=read_byte_am(adr,BNO055_ACCEL_DATA_Z_MSB_ADDR);
	
	xi=(float)(xh<<8|xl);
	yi=(float)(yh<<8|yl);
	zi=(float)(zh<<8|zl);
	
	if(xi&1<<15)
		*x=	-(float)(0xFFFF-xi);
	else
		*x=(xi);
	if(yi&1<<15)
		*y=	-(float)(0xFFFF-yi);
	else
		*y=yi;
	if(zi&1<<15)
		*z=	-(float)(0xFFFF-zi);
	else
		*z=zi;
	
}

void cti_mag(float *x, float *y,float *z,unsigned char adr)
{
		
		unsigned char xl,xh,yl,yh,zl,zh;
	long xi,yi,zi,wi,recipNorm;

	xl=read_byte_am(adr,BNO055_MAG_DATA_X_LSB_ADDR);
	xh=read_byte_am(adr,BNO055_MAG_DATA_X_MSB_ADDR);
	yl=read_byte_am(adr,BNO055_MAG_DATA_Y_LSB_ADDR);
	yh=read_byte_am(adr,BNO055_MAG_DATA_Y_MSB_ADDR);
	zl=read_byte_am(adr,BNO055_MAG_DATA_Z_LSB_ADDR);
	zh=read_byte_am(adr,BNO055_MAG_DATA_Z_MSB_ADDR);
	
	xi=(float)(xh<<8|xl);
	yi=(float)(yh<<8|yl);
	zi=(float)(zh<<8|zl);
	
	if(xi&1<<15)
		*x=	-(float)(0xFFFF-xi);
	else
		*x=(xi);
	if(yi&1<<15)
		*y=	-(float)(0xFFFF-yi);
	else
		*y=yi;
	if(zi&1<<15)
		*z=	-(float)(0xFFFF-zi);
	else
		*z=zi;
	
}

void cti_lin_acc(float *x, float *y,float *z,unsigned char adr)
{
		
		unsigned char xl,xh,yl,yh,zl,zh;
	long xi,yi,zi,wi,recipNorm;

	xl=read_byte_am2(adr,BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR);
	xh=read_byte_am2(adr,BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR);
	yl=read_byte_am2(adr,BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR);
	yh=read_byte_am2(adr,BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR);
	zl=read_byte_am2(adr,BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR);
	zh=read_byte_am2(adr,BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR);
	
	xi=(float)(xh<<8|xl);
	yi=(float)(yh<<8|yl);
	zi=(float)(zh<<8|zl);
	
	if(xi&1<<15)
		*x=	-(float)(0xFFFF-xi);
	else
		*x=(xi);
	if(yi&1<<15)
		*y=	-(float)(0xFFFF-yi);
	else
		*y=yi;
	if(zi&1<<15)
		*z=	-(float)(0xFFFF-zi);
	else
		*z=zi;
	
	
}