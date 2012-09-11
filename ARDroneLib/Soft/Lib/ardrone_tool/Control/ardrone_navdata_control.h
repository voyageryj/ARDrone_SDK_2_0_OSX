#ifndef _ARDRONE_NAVDATA_CONTROL_H_
#define _ARDRONE_NAVDATA_CONTROL_H_

#include <ardrone_tool/Navdata/ardrone_navdata_client.h>

//
// Handler that resume ardrone control thread when new navdatas are received
//
#ifdef __cplusplus
extern "C" {
#endif
	
C_RESULT ardrone_navdata_control_init( void* data );
C_RESULT ardrone_navdata_control_process( const navdata_unpacked_t* const navdata );
C_RESULT ardrone_navdata_control_release( void );

#ifdef __cplusplus
}
#endif
	
#endif // _ARDRONE_NAVDATA_CONTROL_H_
