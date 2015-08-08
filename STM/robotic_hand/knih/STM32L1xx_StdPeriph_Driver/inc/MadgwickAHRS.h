//=====================================================================================================
// MadgwickAHRS.h
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
//=====================================================================================================
#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h

//----------------------------------------------------------------------------------------------------
// Variable declaration

extern volatile float beta;				// algorithm gain


//---------------------------------------------------------------------------------------------------
// Function declarations
void filterUpdate(float w_x, float w_y, float w_z, float a_x, float a_y, float a_z, float m_x, float m_y, float m_z,float deltat,float *q0,float *q1,float *q2,float *q3);
void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz,float dt,float *q0,float *q1,float *q2,float *q3);
void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az,float dt,volatile float *q0,volatile float *q1,volatile float *q2,volatile float *q3);

#endif
//=====================================================================================================
// End of file
//=====================================================================================================
