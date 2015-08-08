/***************************************************/
/**\name	REGISTER ADDRESS DEFINITION  */
/***************************************************/
/* Page id register definition*/
#define BNO055_PAGE_ID_ADDR				    0X07

/* PAGE0 REGISTER DEFINITION START*/
#define BNO055_CHIP_ID_ADDR                 0x00
#define BNO055_ACCEL_REV_ID_ADDR			0x01
#define BNO055_MAG_REV_ID_ADDR              0x02
#define BNO055_GYRO_REV_ID_ADDR             0x03
#define BNO055_SW_REV_ID_LSB_ADDR			0x04
#define BNO055_SW_REV_ID_MSB_ADDR			0x05
#define BNO055_BL_REV_ID_ADDR				0X06

/* Accel data register*/
#define BNO055_ACCEL_DATA_X_LSB_ADDR			0X08
#define BNO055_ACCEL_DATA_X_MSB_ADDR			0X09
#define BNO055_ACCEL_DATA_Y_LSB_ADDR			0X0A
#define BNO055_ACCEL_DATA_Y_MSB_ADDR			0X0B
#define BNO055_ACCEL_DATA_Z_LSB_ADDR			0X0C
#define BNO055_ACCEL_DATA_Z_MSB_ADDR			0X0D

/*Mag data register*/
#define BNO055_MAG_DATA_X_LSB_ADDR			0X0E
#define BNO055_MAG_DATA_X_MSB_ADDR			0X0F
#define BNO055_MAG_DATA_Y_LSB_ADDR			0X10
#define BNO055_MAG_DATA_Y_MSB_ADDR			0X11
#define BNO055_MAG_DATA_Z_LSB_ADDR			0X12
#define BNO055_MAG_DATA_Z_MSB_ADDR			0X13

/*Gyro data registers*/
#define BNO055_GYRO_DATA_X_LSB_ADDR			0X14
#define BNO055_GYRO_DATA_X_MSB_ADDR			0X15
#define BNO055_GYRO_DATA_Y_LSB_ADDR			0X16
#define BNO055_GYRO_DATA_Y_MSB_ADDR			0X17
#define BNO055_GYRO_DATA_Z_LSB_ADDR			0X18
#define BNO055_GYRO_DATA_Z_MSB_ADDR			0X19

/*Euler data registers*/
#define BNO055_EULER_H_LSB_ADDR			0X1A
#define BNO055_EULER_H_MSB_ADDR			0X1B

#define BNO055_EULER_R_LSB_ADDR			0X1C
#define BNO055_EULER_R_MSB_ADDR			0X1D

#define BNO055_EULER_P_LSB_ADDR			0X1E
#define BNO055_EULER_P_MSB_ADDR			0X1F

/*Quaternion data registers*/
#define BNO055_QUATERNION_DATA_W_LSB_ADDR	0X20
#define BNO055_QUATERNION_DATA_W_MSB_ADDR	0X21
#define BNO055_QUATERNION_DATA_X_LSB_ADDR	0X22
#define BNO055_QUATERNION_DATA_X_MSB_ADDR	0X23
#define BNO055_QUATERNION_DATA_Y_LSB_ADDR	0X24
#define BNO055_QUATERNION_DATA_Y_MSB_ADDR	0X25
#define BNO055_QUATERNION_DATA_Z_LSB_ADDR	0X26
#define BNO055_QUATERNION_DATA_Z_MSB_ADDR	0X27

/* Linear acceleration data registers*/
#define BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR			0X28
#define BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR			0X29
#define BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR			0X2A
#define BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR			0X2B
#define BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR			0X2C
#define BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR			0X2D

/*Gravity data registers*/
#define BNO055_GRAVITY_DATA_X_LSB_ADDR			0X2E
#define BNO055_GRAVITY_DATA_X_MSB_ADDR			0X2F
#define BNO055_GRAVITY_DATA_Y_LSB_ADDR			0X30
#define BNO055_GRAVITY_DATA_Y_MSB_ADDR			0X31
#define BNO055_GRAVITY_DATA_Z_LSB_ADDR			0X32
#define BNO055_GRAVITY_DATA_Z_MSB_ADDR			0X33

/* Temperature data register*/
#define BNO055_TEMP_ADDR					0X34

/* Status registers*/
#define BNO055_CALIB_STAT_ADDR				0X35
#define BNO055_SELFTEST_RESULT_ADDR			0X36
#define BNO055_INTR_STAT_ADDR				0X37
#define BNO055_SYS_CLK_STAT_ADDR			0X38
#define BNO055_SYS_STAT_ADDR				0X39
#define BNO055_SYS_ERR_ADDR					0X3A

/* Unit selection register*/
#define BNO055_UNIT_SEL_ADDR				0X3B
#define BNO055_DATA_SELECT_ADDR				0X3C

/* Mode registers*/
#define BNO055_OPR_MODE_ADDR				0X3D
#define BNO055_PWR_MODE_ADDR				0X3E

#define BNO055_SYS_TRIGGER_ADDR				0X3F
#define BNO055_TEMP_SOURCE_ADDR				0X40
/* Axis remap registers*/
#define BNO055_AXIS_MAP_CONFIG_ADDR			0X41
#define BNO055_AXIS_MAP_SIGN_ADDR			0X42

/* SIC registers*/
#define BNO055_SIC_MATRIX_0_LSB_ADDR		0X43
#define BNO055_SIC_MATRIX_0_MSB_ADDR		0X44
#define BNO055_SIC_MATRIX_1_LSB_ADDR		0X45
#define BNO055_SIC_MATRIX_1_MSB_ADDR		0X46
#define BNO055_SIC_MATRIX_2_LSB_ADDR		0X47
#define BNO055_SIC_MATRIX_2_MSB_ADDR		0X48
#define BNO055_SIC_MATRIX_3_LSB_ADDR		0X49
#define BNO055_SIC_MATRIX_3_MSB_ADDR		0X4A
#define BNO055_SIC_MATRIX_4_LSB_ADDR		0X4B
#define BNO055_SIC_MATRIX_4_MSB_ADDR		0X4C
#define BNO055_SIC_MATRIX_5_LSB_ADDR		0X4D
#define BNO055_SIC_MATRIX_5_MSB_ADDR		0X4E
#define BNO055_SIC_MATRIX_6_LSB_ADDR		0X4F
#define BNO055_SIC_MATRIX_6_MSB_ADDR		0X50
#define BNO055_SIC_MATRIX_7_LSB_ADDR		0X51
#define BNO055_SIC_MATRIX_7_MSB_ADDR		0X52
#define BNO055_SIC_MATRIX_8_LSB_ADDR		0X53
#define BNO055_SIC_MATRIX_8_MSB_ADDR		0X54

/* Accelerometer Offset registers*/
#define ACCEL_OFFSET_X_LSB_ADDR				0X55
#define ACCEL_OFFSET_X_MSB_ADDR				0X56
#define ACCEL_OFFSET_Y_LSB_ADDR				0X57
#define ACCEL_OFFSET_Y_MSB_ADDR				0X58
#define ACCEL_OFFSET_Z_LSB_ADDR				0X59
#define ACCEL_OFFSET_Z_MSB_ADDR				0X5A

/* Magnetometer Offset registers*/
#define MAG_OFFSET_X_LSB_ADDR				0X5B
#define MAG_OFFSET_X_MSB_ADDR				0X5C
#define MAG_OFFSET_Y_LSB_ADDR				0X5D
#define MAG_OFFSET_Y_MSB_ADDR				0X5E
#define MAG_OFFSET_Z_LSB_ADDR				0X5F
#define MAG_OFFSET_Z_MSB_ADDR				0X60

/* Gyroscope Offset registers*/
#define GYRO_OFFSET_X_LSB_ADDR				0X61
#define GYRO_OFFSET_X_MSB_ADDR				0X62
#define GYRO_OFFSET_Y_LSB_ADDR				0X63
#define GYRO_OFFSET_Y_MSB_ADDR				0X64
#define GYRO_OFFSET_Z_LSB_ADDR				0X65
#define GYRO_OFFSET_Z_MSB_ADDR				0X66

/* Radius registers*/
#define	ACCEL_RADIUS_LSB_ADDR				0X67
#define	ACCEL_RADIUS_MSB_ADDR				0X68
#define	MAG_RADIUS_LSB_ADDR					0X69
#define	MAG_RADIUS_MSB_ADDR					0X6A
/* PAGE0 REGISTERS DEFINITION END*/

/* PAGE1 REGISTERS DEFINITION START*/
/* Configuration registers*/
#define ACCEL_CONFIG_ADDR					0X08
#define MAG_CONFIG_ADDR						0X09
#define GYRO_CONFIG_ADDR					0X0A
#define GYRO_MODE_CONFIG_ADDR				0X0B
#define ACCEL_SLEEP_CONFIG_ADDR				0X0C
#define GYRO_SLEEP_CONFIG_ADDR				0X0D
#define MAG_SLEEP_CONFIG_ADDR				0x0E

/* Interrupt registers*/
#define INT_MASK_ADDR						0X0F
#define INT_ADDR							0X10
#define ACCEL_ANY_MOTION_THRES_ADDR			0X11
#define ACCEL_INTR_SETTINGS_ADDR				0X12
#define ACCEL_HIGH_G_DURN_ADDR				0X13
#define ACCEL_HIGH_G_THRES_ADDR				0X14
#define ACCEL_NO_MOTION_THRES_ADDR			0X15
#define ACCEL_NO_MOTION_SET_ADDR				0X16
#define GYRO_INTR_SETING_ADDR				0X17
#define GYRO_HIGHRATE_X_SET_ADDR			0X18
#define GYRO_DURN_X_ADDR						0X19
#define GYRO_HIGHRATE_Y_SET_ADDR			0X1A
#define GYRO_DURN_Y_ADDR						0X1B
#define GYRO_HIGHRATE_Z_SET_ADDR			0X1C
#define GYRO_DURN_Z_ADDR						0X1D
#define GYRO_ANY_MOTION_THRES_ADDR			0X1E
#define GYRO_ANY_MOTION_SET_ADDR				0X1F


//--------------------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////
//nastavení

/* Operation mode settings*/
#define OPERATION_MODE_CONFIG			0X00
#define OPERATION_MODE_ACCONLY			0X01
#define OPERATION_MODE_MAGONLY			0X02
#define OPERATION_MODE_GYRONLY			0X03
#define OPERATION_MODE_ACCMAG			0X04
#define OPERATION_MODE_ACCGYRO			0X05
#define OPERATION_MODE_MAGGYRO			0X06
#define OPERATION_MODE_AMG				0X07
#define OPERATION_MODE_IMUPLUS			0X08
#define OPERATION_MODE_COMPASS			0X09
#define OPERATION_MODE_M4G				0X0A
#define OPERATION_MODE_NDOF_FMC_OFF		0X0B
#define OPERATION_MODE_NDOF				0X0C

/* Power mode*/
#define POWER_MODE_NORMAL	0X00
#define POWER_MODE_LOWPOWER	0X01
#define POWER_MODE_SUSPEND	0X02

/* PAGE-1 definitions*/
/* Accel Range */

#define ACCEL_RANGE_2G		0X00
#define ACCEL_RANGE_4G		0X01
#define ACCEL_RANGE_8G		0X02
#define ACCEL_RANGE_16G		0X03

/* Accel Bandwidth*/
#define ACCEL_BW_7_81HZ		0x00
#define ACCEL_BW_15_63HZ	0x01
#define ACCEL_BW_31_25HZ	0x02
#define ACCEL_BW_62_5HZ		0X03
#define ACCEL_BW_125HZ		0X04
#define ACCEL_BW_250HZ		0X05
#define ACCEL_BW_500HZ		0X06
#define ACCEL_BW_1000HZ		0X07

/* Accel Power mode*/
#define ACCEL_NORMAL			0X00
#define ACCEL_SUSPEND			0X01
#define ACCEL_LOWPOWER_1		0X02
#define ACCEL_STANDBY			0X03
#define ACCEL_LOWPOWER_2		0X04
#define ACCEL_DEEPSUSPEND		0X05

/* Mag data output rate*/
#define MAG_DATA_OUTRATE_2HZ		0X00
#define MAG_DATA_OUTRATE_6HZ		0X01
#define MAG_DATA_OUTRATE_8HZ		0X02
#define MAG_DATA_OUTRATE_10HZ		0X03
#define MAG_DATA_OUTRATE_15HZ		0X04
#define MAG_DATA_OUTRATE_20HZ		0X05
#define MAG_DATA_OUTRATE_25HZ		0X06
#define MAG_DATA_OUTRATE_30HZ		0X07

/* Mag Operation mode*/
#define MAG_OPERATION_MODE_LOWPOWER				0X00
#define MAG_OPERATION_MODE_REGULAR				0X01
#define MAG_OPERATION_MODE_ENHANCED_REGULAR		0X02
#define MAG_OPERATION_MODE_HIGH_ACCURACY		0X03

/* Mag power mode*/
#define MAG_POWER_MODE_NORMAL					0X00
#define MAG_POWER_MODE_SLEEP					0X01
#define MAG_POWER_MODE_SUSPEND					0X02
#define MAG_POWER_MODE_FORCE_MODE				0X03

/* Gyro range*/
#define GYRO_RANGE_2000DPS		0x00
#define GYRO_RANGE_1000DPS		0x01
#define GYRO_RANGE_500DPS		0x02
#define GYRO_RANGE_250DPS		0x03
#define GYRO_RANGE_125DPS		0x04

/* Gyro Bandwidth*/
#define GYRO_BW_523HZ		0x00
#define GYRO_BW_230HZ		0x01
#define GYRO_BW_116HZ		0x02
#define GYRO_BW_47HZ		0x03
#define GYRO_BW_23HZ		0x04
#define GYRO_BW_12HZ		0x05
#define GYRO_BW_64HZ		0x06
#define GYRO_BW_32HZ		0x07

/* Gyro power mode*/
#define GYRO_POWER_MODE_NORMAL				0X00
#define GYRO_POWER_MODE_FASTPOWERUP			0X01
#define GYRO_POWER_MODE_DEEPSUSPEND			0X02
#define GYRO_POWER_MODE_SUSPEND				0X03
#define GYRO_POWER_MODE_ADVANCE_POWERSAVE	0X04

/* Accel Sleep Duration */
#define BNO055_ACCEL_SLEEP_DURN_0_5MS        0x05
/* sets sleep duration to 0.5 ms  */
#define BNO055_ACCEL_SLEEP_DURN_1MS          0x06
/* sets sleep duration to 1 ms */
#define BNO055_ACCEL_SLEEP_DURN_2MS          0x07
/* sets sleep duration to 2 ms */
#define BNO055_ACCEL_SLEEP_DURN_4MS          0x08
/* sets sleep duration to 4 ms */
#define BNO055_ACCEL_SLEEP_DURN_6MS          0x09
/* sets sleep duration to 6 ms*/
#define BNO055_ACCEL_SLEEP_DURN_10MS         0x0A
/* sets sleep duration to 10 ms */
#define BNO055_ACCEL_SLEEP_DURN_25MS         0x0B
 /* sets sleep duration to 25 ms */
#define BNO055_ACCEL_SLEEP_DURN_50MS         0x0C
 /* sets sleep duration to 50 ms */
#define BNO055_ACCEL_SLEEP_DURN_100MS        0x0D
 /* sets sleep duration to 100 ms */
#define BNO055_ACCEL_SLEEP_DURN_500MS        0x0E
 /* sets sleep duration to 500 ms */
#define BNO055_ACCEL_SLEEP_DURN_1S           0x0F
/* sets sleep duration to 1 s */

/* Gyro Auto sleep duration*/
#define BNO055_GYRO_No_AUTOSLPDUR		0x00
#define	BNO055_GYRO_4MS_AUTOSLPDUR		0x01
#define	BNO055_GYRO_5MS_AUTOSLPDUR		0x02
#define	BNO055_GYRO_8MS_AUTOSLPDUR		0x03
#define	BNO055_GYRO_10MS_AUTOSLPDUR		0x04
#define	BNO055_GYRO_15MS_AUTOSLPDUR		0x05
#define	BNO055_GYRO_20MS_AUTOSLPDUR		0x06
#define	BNO055_GYRO_40MS_AUTOSLPDUR		0x07

/* Accel Any/No motion axis selection*/
#define BNO055_ACCEL_ANY_MOTION_NO_MOTION_X_AXIS		0
#define BNO055_ACCEL_ANY_MOTION_NO_MOTION_Y_AXIS		1
#define BNO055_ACCEL_ANY_MOTION_NO_MOTION_Z_AXIS		2

/* Accel High g axis selection*/
#define BNO055_ACCEL_HIGH_G_X_AXIS		0
#define BNO055_ACCEL_HIGH_G_Y_AXIS		1
#define BNO055_ACCEL_HIGH_G_Z_AXIS		2

/* Gyro Any motion axis selection*/
#define BNO055_GYRO_ANY_MOTION_X_AXIS		0
#define BNO055_GYRO_ANY_MOTION_Y_AXIS		1
#define BNO055_GYRO_ANY_MOTION_Z_AXIS		2


/* Gyro High rate axis selection*/
#define BNO055_GYRO_HIGHRATE_X_AXIS		0
#define BNO055_GYRO_HIGHRATE_Y_AXIS		1
#define BNO055_GYRO_HIGHRATE_Z_AXIS		2

/* Axis remap values*/
#define REMAP_X_Y			0X21
#define REMAP_Y_Z			0X18
#define REMAP_Z_X			0X06
#define REMAP_X_Y_Z_TYPE0	0X12
#define REMAP_X_Y_Z_TYPE1	0X09
#define DEFAULT_AXIS		0X24

/* Axis remap sign */
#define	REMAP_AXIS_POSITIVE	0X00
#define	REMAP_AXIS_NEGATIVE	0X01

/* Gyro anymotion and high rate filter configuration */
#define	FILTERED	0x00
#define	UNFILTERED	0x01


void init_imu(unsigned char adr);
void init_imu2(unsigned char adr);
void cti_quat(float *qw, float *qx,float *qy, float *qz,unsigned char adr);
void cti_quat2(float *qw, float *qx,float *qy, float *qz,unsigned char adr);
void cti_eul(float *roll, float *pitch,float *yaw,unsigned char adr);
void cti_acc(float *x, float *y,float *z,unsigned char adr);
void cti_lin_acc(float *x, float *y,float *z,unsigned char adr);
void cti_mag(float *x, float *y,float *z,unsigned char adr);

