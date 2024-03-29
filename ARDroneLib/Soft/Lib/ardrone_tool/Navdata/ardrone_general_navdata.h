#ifndef _ARDRONE_NAVDATA_GENERAL_H_
#define _ARDRONE_NAVDATA_GENERAL_H_

#include <ardrone_tool/Navdata/ardrone_navdata_client.h>

typedef enum _MULTICONFIG_STATE_
  {
    MULTICONFIG_IDLE,
    MULTICONFIG_NEEDED,
    MULTICONFIG_GOT_DRONE_VERSION,
    MULTICONFIG_GOT_IDS_LIST,
    MULTICONFIG_GOT_CURRENT_IDS,
    MULTICONFIG_GOT_NAVDATA,
    MULTICONFIG_IN_PROGRESS_VERSION,
    MULTICONFIG_IN_PROGRESS_LIST,
    MULTICONFIG_IN_PROGRESS_IDS,
    MULTICONFIG_IN_PROGRESS_NAVDATA,
    MULTICONFIG_REQUEST_NAVDATA,
  } MULTICONFIG_STATE;

typedef enum _NAVDATA_REQUEST_STATE_
  {
    NAVDATA_REQUEST_IDLE,
    NAVDATA_REQUEST_NEEDED,
    NAVDATA_REQUEST_IN_PROGRESS,
    NAVDATA_REQUEST_DONE,
  } NAVDATA_REQUEST_STATE;

#ifdef __cplusplus
extern "C"{
#endif
	
C_RESULT ardrone_general_navdata_init( void* data );
C_RESULT ardrone_general_navdata_process( const navdata_unpacked_t* const navdata );
C_RESULT ardrone_general_navdata_release( void );

extern int configWasDone;
	
#ifdef __cplusplus
}
#endif

#endif //! _ARDRONE_NAVDATA_GENERAL_H_

