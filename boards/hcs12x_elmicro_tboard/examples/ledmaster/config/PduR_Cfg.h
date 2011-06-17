/*
* Configuration of module: PduR (PduR_Cfg.h)
*
* Created by:              
* Copyright:               
*
* Configured for (MCU):    HCS12
*
* Module vendor:           ArcCore
* Generator version:       3.0.8
*
* Generated by Arctic Studio (http://arccore.com) 
*           on Fri Jun 17 23:12:14 CEST 2011
*/


#if !(((PDUR_SW_MAJOR_VERSION == 2) && (PDUR_SW_MINOR_VERSION == 0)) )
#error PduR: Configuration file expected BSW module version to be 2.0.*
#endif



#ifndef PDUR_CFG_H_
#define PDUR_CFG_H_

// Module support
#define PDUR_CANIF_SUPPORT 			STD_ON
#define PDUR_CANTP_SUPPORT			STD_OFF
#define PDUR_FRIF_SUPPORT			STD_OFF  /* Not supported */
#define PDUR_FRTP_SUPPORT			STD_OFF  /* Not supported */
#define PDUR_LINIF_SUPPORT			STD_OFF
#define PDUR_LINTP_SUPPORT			STD_OFF  /* Not supported */
#define PDUR_COM_SUPPORT			STD_ON
#define PDUR_DCM_SUPPORT			STD_OFF
#define PDUR_IPDUM_SUPPORT			STD_OFF  /* Not supported */
#define PDUR_SOAD_SUPPORT 			STD_OFF

#define PDUR_DEV_ERROR_DETECT		STD_OFF
#define PDUR_VERSION_INFO_API		STD_OFF


// Zero cost operation mode
#define PDUR_ZERO_COST_OPERATION	STD_ON
#define PDUR_SINGLE_IF				CAN_IF
#define PDUR_SINGLE_TP				CAN_TP


// Gateway operation
#define PDUR_GATEWAY_OPERATION				STD_ON
#define PDUR_MEMORY_SIZE					10 /* Not used */
#define PDUR_SB_TX_BUFFER_SUPPORT			STD_ON
#define PDUR_FIFO_TX_BUFFER_SUPPORT			STD_OFF

/**
 * The maximum numbers of Tx buffers.
 */
#define PDUR_MAX_TX_BUFFER_NUMBER			10 /* Not used */


// Multicast
#define PDUR_MULTICAST_TOIF_SUPPORT			STD_ON
#define PDUR_MULTICAST_FROMIF_SUPPORT		STD_ON
#define PDUR_MULTICAST_TOTP_SUPPORT			STD_ON
#define PDUR_MULTICAST_FROMTP_SUPPORT		STD_ON

// Minimum routing
/* Minimum routing not supported.
#define PDUR_MINIMUM_ROUTING_UP_MODULE		COM
#define PDUR_MINIMUM_ROUTING_LO_MODULE		CAN_IF
#define PDUR_MINIMUM_ROUTING_UP_RXPDUID		((PduIdType)100)
#define PDUR_MINIMUM_ROUTING_LO_RXPDUID 	((PduIdType)255)
#define PDUR_MINIMUM_ROUTING_UP_TXPDUID 	((PduIdType)255)
#define PDUR_MINIMUM_ROUTING_LO_TXPDUID 	((PduIdType)255)
*/

// Zero cost operation support active.
#if PDUR_CANIF_SUPPORT == STD_ON
#define PduR_CanIfRxIndication Com_RxIndication
#define PduR_CanIfTxConfirmation Com_TxConfirmation
#else
#define PduR_CanIfRxIndication(... )
#define PduR_CanIfTxConfirmation(...)
#endif

#if PDUR_CANTP_SUPPORT == STD_ON
#define PduR_CanTpProvideRxBuffer Dcm_ProvideRxBuffer
#define PduR_CanTpRxIndication Dcm_RxIndication
#define PduR_CanTpProvideTxBuffer Dcm_ProvideTxBuffer
#define PduR_CanTpTxConfirmation Dcm_TxConfirmation
#else
#define PduR_CanTpProvideRxBuffer(...)
#define PduR_CanTpRxIndication(...)
#define PduR_CanTpProvideTxBuffer(...)
#define PduR_CanTpTxConfirmation(...)
#endif

#if PDUR_LINIF_SUPPORT == STD_ON 
#define PduR_LinIfRxIndication Com_RxIndication
#define PduR_LinIfTxConfirmation Com_TxConfirmation
#define PduR_LinIfTriggerTransmit Com_TriggerTransmit
#else
#define PduR_LinIfRxIndication(...)
#define PduR_LinIfTxConfirmation(...)
#define PduR_LinIfTriggerTransmit(...)
#endif

#if PDUR_SOAD_SUPPORT == STD_ON
#define PduR_SoAdTpProvideRxBuffer Dcm_ProvideRxBuffer
#define PduR_SoAdTpRxIndication Dcm_RxIndication
#define PduR_SoAdTpProvideTxBuffer Dcm_ProvideTxBuffer
#define PduR_SoAdTpTxConfirmation Dcm_TxConfirmation
#else
#define PduR_SoAdProvideRxBuffer(...)
#define PduR_SoAdRxIndication(...)
#define PduR_SoAdProvideTxBuffer(...)
#define PduR_SoAdTxConfirmation(...)
#endif

#if PDUR_COM_SUPPORT == STD_ON
#define PduR_ComTransmit CanIf_Transmit
#else
#define PduR_ComTransmit(... )	(E_OK)
#endif

#if PDUR_DCM_SUPPORT == STD_ON
#define PduR_DcmTransmit CanTp_Transmit
#else
#define PduR_DcmTransmit(... )	(E_OK)
#endif


#endif
