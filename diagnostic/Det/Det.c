/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/








/*
 * Development Error Tracer driver
 *
 * Specification: Autosar v2.0.1, Final
 *
 */

#include "Std_Types.h"
#include "Det.h"
#include "Cpu.h"
#include "stdio.h"

#define DEBUG_LVL 1
#include "Trace.h"

typedef enum
{
  DET_UNINITIALIZED = 0,
  DET_INITIALIZED,
  DET_STARTED
} Det_StateType;

static Det_StateType _detState = DET_UNINITIALIZED;

#if ( DET_USE_RAMLOG == STD_ON )
// TODO Put this in a section that is not initialised after a reset
uint32 Det_RamlogIndex = 0;
Det_EntryType Det_RamLog[DET_RAMLOG_SIZE];
#endif

#if ( DET_ENABLE_CALLBACKS == STD_ON )
detCbk_t detCbk_List[DET_NUMBER_OF_CALLBACKS];

uint8 Det_AddCbk(detCbk_t detCbk)
{
  if (_detState != DET_UNINITIALIZED)
  {
    for (uint32 i=0; i<DET_NUMBER_OF_CALLBACKS; i++)
    {
      if (NULL==detCbk_List[i])
      {
        detCbk_List[i]=detCbk;
        return i;
      }
    }
  }

  Det_ReportError(DET_MODULE_ID, 0, DET_CALLBACK_API, DET_E_CBK_REGISTRATION_FAILED);
  return (0xFF); // Return 0xff to indicate that the registration failed
}

void Det_RemoveCbk(uint8 detCbkIndex)
{
  // Validate the index
  if (detCbkIndex >= DET_NUMBER_OF_CALLBACKS)
    Det_ReportError(DET_MODULE_ID, 0, DET_CALLBACK_API, DET_E_INDEX_OUT_OF_RANGE);

  detCbk_List[detCbkIndex]=NULL;
}
#endif


void Det_Init(void)
{
#if ( DET_ENABLE_CALLBACKS == STD_ON )
  for (uint32 i=0; i<DET_NUMBER_OF_CALLBACKS; i++)
  {
    detCbk_List[i]=NULL;
  }
#endif

#if ( DET_USE_RAMLOG == STD_ON )
  for(uint32 i=0; i < DET_RAMLOG_SIZE; i++)
  {
    Det_RamLog[i].moduleId = 0;
    Det_RamLog[i].instanceId = 0;
    Det_RamLog[i].apiId = 0;
    Det_RamLog[i].errorId = 0;
  }
  Det_RamlogIndex = 0;
#endif

  _detState = DET_INITIALIZED;
}

#if DET_DEINIT_API == STD_ON
void Det_DeInit( void )
{
  _detState = DET_UNINITIALIZED;
}
#endif

void Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
  if (_detState == DET_STARTED) // No action is taken if the module is not started
  {
#if ( DET_ENABLE_CALLBACKS == STD_ON )
  long old1;
  Irq_Save(old1);
  for (uint32 i=0; i<DET_NUMBER_OF_CALLBACKS; i++)
  {
    if (NULL!=detCbk_List[i])
    {
      (*detCbk_List[i])(ModuleId, InstanceId, ApiId, ErrorId);
    }
  }
  Irq_Restore(old1);
#endif

#if ( DET_USE_RAMLOG == STD_ON )
  long old2;
  Irq_Save(old2);
  if (Det_RamlogIndex < DET_RAMLOG_SIZE)
  {
    Det_RamLog[Det_RamlogIndex].moduleId = ModuleId;
    Det_RamLog[Det_RamlogIndex].instanceId = InstanceId;
    Det_RamLog[Det_RamlogIndex].apiId = ApiId;
    Det_RamLog[Det_RamlogIndex].errorId = ErrorId;
    Det_RamlogIndex++;
#if ( DET_WRAP_RAMLOG == STD_ON )
    if (Det_RamlogIndex == DET_RAMLOG_SIZE)
      Det_RamlogIndex = 0;
#endif
  }
  Irq_Restore(old2);
#endif

#if ( DET_USE_STDERR == STD_ON )
  simple_printf("Det Error: ModuleId=%d, InstanceId=%d, ApiId=%d, ErrorId=%d\n", ModuleId, InstanceId, ApiId, ErrorId);
  //fprintf(stderr, "Det Error: ModuleId=%d, InstanceId=%d, ApiId=%d, ErrorId=%d\n", ModuleId, InstanceId, ApiId, ErrorId);
#endif
  }
}

void Det_Start(void)
{
  _detState = DET_STARTED;
}