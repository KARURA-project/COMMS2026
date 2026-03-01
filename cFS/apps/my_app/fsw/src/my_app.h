/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * @file
 *
 * Main header file for the Sample application
 */

#ifndef MY_APP_H
#define MY_APP_H

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_config.h"

#include "my_app_mission_cfg.h"
#include "my_app_platform_cfg.h"

#include "my_app_perfids.h"
#include "my_app_msgids.h"
#include "my_app_msg.h"

/************************************************************************
** Type Definitions
*************************************************************************/

/*
** Global Data
*/
typedef struct
{
    /*
    ** Command interface counters...
    */
    uint8 CmdCounter;
    uint8 ErrCounter;

    /*
    ** Housekeeping telemetry packet...
    */
    MY_APP_HkTlm_t HkTlm;

    /*
    ** Run Status variable used in the main processing loop
    */
    uint32 RunStatus;

    /*
    ** Operational data (not reported in housekeeping)...
    */
    CFE_SB_PipeId_t CommandPipe;

    CFE_TBL_Handle_t TblHandles[MY_APP_NUMBER_OF_TABLES];
} MY_APP_Data_t;

/*
** Global data structure
*/
extern MY_APP_Data_t MY_APP_Data;

/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (MY_APP_Main), these
**       functions are not called from any other source module.
*/
void         MY_APP_Main(void);
CFE_Status_t MY_APP_Init(void);

#endif /* MY_APP_H */
