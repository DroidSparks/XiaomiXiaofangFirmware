/****************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 * (c) Copyright 2002, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ****************************************************************************

    Module Name:
	rt_profile.c
 
    Abstract:
 
    Revision History:
    Who          When          What
    ---------    ----------    ----------------------------------------------
 */
 
#include "rt_config.h"

#ifdef RTMP_RBUS_SUPPORT
#if defined (CONFIG_RA_HW_NAT)  || defined (CONFIG_RA_HW_NAT_MODULE)
#include "../../../../../../net/nat/hw_nat/ra_nat.h"
#include "../../../../../../net/nat/hw_nat/frame_engine.h"
#endif
#endif /* RTMP_RBUS_SUPPORT */


#ifdef SYSTEM_LOG_SUPPORT
/* for wireless system event message */
char const *pWirelessSysEventText[IW_SYS_EVENT_TYPE_NUM] = {    
	/* system status event */
    "had associated successfully",							/* IW_ASSOC_EVENT_FLAG */
    "had disassociated",									/* IW_DISASSOC_EVENT_FLAG */
    "had deauthenticated",									/* IW_DEAUTH_EVENT_FLAG */
    "had been aged-out and disassociated",					/* IW_AGEOUT_EVENT_FLAG */
    "occurred CounterMeasures attack",						/* IW_COUNTER_MEASURES_EVENT_FLAG */	
    "occurred replay counter different in Key Handshaking",	/* IW_REPLAY_COUNTER_DIFF_EVENT_FLAG */
    "occurred RSNIE different in Key Handshaking",			/* IW_RSNIE_DIFF_EVENT_FLAG */
    "occurred MIC different in Key Handshaking",			/* IW_MIC_DIFF_EVENT_FLAG */
    "occurred ICV error in RX",								/* IW_ICV_ERROR_EVENT_FLAG */
    "occurred MIC error in RX",								/* IW_MIC_ERROR_EVENT_FLAG */
	"Group Key Handshaking timeout",						/* IW_GROUP_HS_TIMEOUT_EVENT_FLAG */ 
	"Pairwise Key Handshaking timeout",						/* IW_PAIRWISE_HS_TIMEOUT_EVENT_FLAG */ 
	"RSN IE sanity check failure",							/* IW_RSNIE_SANITY_FAIL_EVENT_FLAG */ 
	"set key done in WPA/WPAPSK",							/* IW_SET_KEY_DONE_WPA1_EVENT_FLAG */ 
	"set key done in WPA2/WPA2PSK",                         /* IW_SET_KEY_DONE_WPA2_EVENT_FLAG */ 
	"connects with our wireless client",                    /* IW_STA_LINKUP_EVENT_FLAG */ 
	"disconnects with our wireless client",                 /* IW_STA_LINKDOWN_EVENT_FLAG */
	"scan completed",										/* IW_SCAN_COMPLETED_EVENT_FLAG */
	"scan terminate!! Busy!! Enqueue fail!!",				/* IW_SCAN_ENQUEUE_FAIL_EVENT_FLAG */
	"channel switch to ",									/* IW_CHANNEL_CHANGE_EVENT_FLAG */
	"wireless mode is not support",							/* IW_STA_MODE_EVENT_FLAG */
	"blacklisted in MAC filter list",						/* IW_MAC_FILTER_LIST_EVENT_FLAG */
	"Authentication rejected because of challenge failure",	/* IW_AUTH_REJECT_CHALLENGE_FAILURE */
	"Scanning",												/* IW_SCANNING_EVENT_FLAG */
	"Start a new IBSS",										/* IW_START_IBSS_FLAG */
	"Join the IBSS",										/* IW_JOIN_IBSS_FLAG */
	"Shared WEP fail",										/* IW_SHARED_WEP_FAIL*/
	};

#ifdef IDS_SUPPORT
/* for wireless IDS_spoof_attack event message */
char const *pWirelessSpoofEventText[IW_SPOOF_EVENT_TYPE_NUM] = {   	
    "detected conflict SSID",								/* IW_CONFLICT_SSID_EVENT_FLAG */
    "detected spoofed association response",				/* IW_SPOOF_ASSOC_RESP_EVENT_FLAG */
    "detected spoofed reassociation responses",				/* IW_SPOOF_REASSOC_RESP_EVENT_FLAG */
    "detected spoofed probe response",						/* IW_SPOOF_PROBE_RESP_EVENT_FLAG */
    "detected spoofed beacon",								/* IW_SPOOF_BEACON_EVENT_FLAG */
    "detected spoofed disassociation",						/* IW_SPOOF_DISASSOC_EVENT_FLAG */
    "detected spoofed authentication",						/* IW_SPOOF_AUTH_EVENT_FLAG */
    "detected spoofed deauthentication",					/* IW_SPOOF_DEAUTH_EVENT_FLAG */
    "detected spoofed unknown management frame",			/* IW_SPOOF_UNKNOWN_MGMT_EVENT_FLAG */
	"detected replay attack"								/* IW_REPLAY_ATTACK_EVENT_FLAG */	
	};

/* for wireless IDS_flooding_attack event message */
char const *pWirelessFloodEventText[IW_FLOOD_EVENT_TYPE_NUM] = {   	
	"detected authentication flooding",						/* IW_FLOOD_AUTH_EVENT_FLAG */
    "detected association request flooding",				/* IW_FLOOD_ASSOC_REQ_EVENT_FLAG */
    "detected reassociation request flooding",				/* IW_FLOOD_REASSOC_REQ_EVENT_FLAG */
    "detected probe request flooding",						/* IW_FLOOD_PROBE_REQ_EVENT_FLAG */
    "detected disassociation flooding",						/* IW_FLOOD_DISASSOC_EVENT_FLAG */
    "detected deauthentication flooding",					/* IW_FLOOD_DEAUTH_EVENT_FLAG */
    "detected 802.1x eap-request flooding"					/* IW_FLOOD_EAP_REQ_EVENT_FLAG */	
	};
#endif /* IDS_SUPPORT */

#ifdef WSC_INCLUDED
/* for WSC wireless event message */
char const *pWirelessWscEventText[IW_WSC_EVENT_TYPE_NUM] = {   	
	"PBC Session Overlap",									/* IW_WSC_PBC_SESSION_OVERLAP */
	"This WPS Registrar supports PBC",						/* IW_WSC_REGISTRAR_SUPPORT_PBC */
	"This WPS Registrar supports PIN",						/* IW_WSC_REGISTRAR_SUPPORT_PIN */
	"WPS status success",									/* IW_WSC_STATUS_SUCCESS */
	"WPS status fail",										/* IW_WSC_STATUS_FAIL */
	"WPS 2 mins time out!",									/* IW_WSC_2MINS_TIMEOUT */
	"WPS Send EAPOL_Start!",								/* IW_WSC_SEND_EAPOL_START */
	"WPS Send WscStart!",									/* IW_WSC_SEND_WSC_START */
	"WPS Send M1!",											/* IW_WSC_SEND_M1 */
	"WPS Send M2!",											/* IW_WSC_SEND_M2 */
	"WPS Send M3!",											/* IW_WSC_SEND_M3 */
	"WPS Send M4!",											/* IW_WSC_SEND_M4 */
	"WPS Send M5!",											/* IW_WSC_SEND_M5 */
	"WPS Send M6!",											/* IW_WSC_SEND_M6 */
	"WPS Send M7!",											/* IW_WSC_SEND_M7 */
	"WPS Send M8!",											/* IW_WSC_SEND_M8 */
	"WPS Send WscDone!",									/* IW_WSC_SEND_DONE */
	"WPS Send WscAck!",										/* IW_WSC_SEND_ACK */
	"WPS Send WscNack!",									/* IW_WSC_SEND_NACK */
	"WPS Receive WscStart!",								/* IW_WSC_RECEIVE_WSC_START */
	"WPS Receive M1!",										/* IW_WSC_RECEIVE_M1 */
	"WPS Receive M2!",										/* IW_WSC_RECEIVE_M2 */
	"WPS Receive M3!",										/* IW_WSC_RECEIVE_M3 */
	"WPS Receive M4!",										/* IW_WSC_RECEIVE_M4 */
	"WPS Receive M5!",										/* IW_WSC_RECEIVE_M5 */
	"WPS Receive M6!",										/* IW_WSC_RECEIVE_M6 */
	"WPS Receive M7!",										/* IW_WSC_RECEIVE_M7 */
	"WPS Receive M8!",										/* IW_WSC_RECEIVE_M8 */
	"WPS Receive WscDone!",									/* IW_WSC_RECEIVE_DONE */
	"WPS Receive WscAck!",									/* IW_WSC_RECEIVE_ACK */
	"WPS Receive WscNack!",									/* IW_WSC_RECEIVE_NACK */
	"Not only one candidate found"							/* IW_WSC_MANY_CANDIDATE */
	};
#endif /* WSC_INCLUDED */

#ifdef CONFIG_STA_SUPPORT
#ifdef IWSC_SUPPORT
// for IWSC wireless event messagechar 
const *pWirelessIWscEventText[IW_IWSC_EVENT_TYPE_NUM] = {
	"IWSC - T1 mins time out!",									/* IW_IWSC_T1_TIMER_TIMEOUT */
	"IWSC - T2 mins time out!",									/* IW_IWSC_T2_TIMER_TIMEOUT */
	"IWSC - Become Registrar",									/* IW_IWSC_BECOME_REGISTRAR */
	"IWSC - Become Enrollee",									/* IW_IWSC_BECOME_ENROLLEE */
	"IWSC - Entry time out",									/* IW_IWSC_ENTRY_TIMER_TIMEOUT */
	};
#endif /* IWSC_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */
#endif /* SYSTEM_LOG_SUPPORT */


NDIS_STATUS	RTMPReadParametersHook(
	IN	PRTMP_ADAPTER pAd)
{
	PSTRING					src = NULL;
	RTMP_OS_FD				srcf;
	RTMP_OS_FS_INFO			osFSInfo;
	INT 						retval = NDIS_STATUS_FAILURE;
	PSTRING					buffer;

#ifdef HOSTAPD_SUPPORT
	int i;
#endif /*HOSTAPD_SUPPORT */

/*	buffer = kmalloc(MAX_INI_BUFFER_SIZE, MEM_ALLOC_FLAG); */
	os_alloc_mem(pAd, (UCHAR **)&buffer, MAX_INI_BUFFER_SIZE);
	if(buffer == NULL)
		return NDIS_STATUS_FAILURE;
	memset(buffer, 0x00, MAX_INI_BUFFER_SIZE);
			
#ifdef RTMP_RBUS_SUPPORT
	if (pAd->infType == RTMP_DEV_INF_RBUS)
	{
#ifdef CONFIG_AP_SUPPORT
		IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
		{
			src = AP_PROFILE_PATH_RBUS;
		}
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
		IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
		{
			src = STA_PROFILE_PATH_RBUS;
		}
#endif /* CONFIG_STA_SUPPORT */
#ifdef MULTIPLE_CARD_SUPPORT
		src = pAd->MC_FileName;
#endif /* MULTIPLE_CARD_SUPPORT */
	}
	else
#endif /* RTMP_RBUS_SUPPORT */
	{	
#ifdef CONFIG_AP_SUPPORT
		IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
		{
			src = AP_PROFILE_PATH;
		}
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
		IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
		{
			src = STA_PROFILE_PATH;
		}
#endif /* CONFIG_STA_SUPPORT */
#ifdef MULTIPLE_CARD_SUPPORT
		src = (PSTRING)pAd->MC_FileName;
#endif /* MULTIPLE_CARD_SUPPORT */
	}

	if (src && *src)
	{
		RtmpOSFSInfoChange(&osFSInfo, TRUE);
		srcf = RtmpOSFileOpen(src, O_RDONLY, 0);
		if (IS_FILE_OPEN_ERR(srcf)) 
		{
			DBGPRINT(RT_DEBUG_ERROR, ("Open file \"%s\" failed!\n", src));
		}
		else 
		{
			retval =RtmpOSFileRead(srcf, buffer, MAX_INI_BUFFER_SIZE);
			if (retval > 0)
			{
				RTMPSetProfileParameters(pAd, buffer);
				retval = NDIS_STATUS_SUCCESS;
			}
			else
				DBGPRINT(RT_DEBUG_ERROR, ("Read file \"%s\" failed(errCode=%d)!\n", src, retval));

			retval = RtmpOSFileClose(srcf);
			if ( retval != 0)
			{
				retval = NDIS_STATUS_FAILURE;
				DBGPRINT(RT_DEBUG_ERROR, ("Close file \"%s\" failed(errCode=%d)!\n", src, retval));
			}
		}
		
		RtmpOSFSInfoChange(&osFSInfo, FALSE);
	}

#ifdef HOSTAPD_SUPPORT
		for (i = 0; i < pAd->ApCfg.BssidNum; i++)
		{
			pAd->ApCfg.MBSSID[i].Hostapd=FALSE;
			DBGPRINT(RT_DEBUG_TRACE, ("Reset ra%d hostapd support=FLASE", i));
			
		}
#endif /*HOSTAPD_SUPPORT */

#ifdef SINGLE_SKU_V2
	RTMPSetSingleSKUParameters(pAd);
#endif /* SINGLE_SKU_V2 */

/*	kfree(buffer); */
	os_free_mem(NULL, buffer);
	
	return (retval);

}


#ifdef SYSTEM_LOG_SUPPORT
/*
	========================================================================
	
	Routine Description:
		Send log message through wireless event

		Support standard iw_event with IWEVCUSTOM. It is used below.

		iwreq_data.data.flags is used to store event_flag that is defined by user. 
		iwreq_data.data.length is the length of the event log.

		The format of the event log is composed of the entry's MAC address and
		the desired log message (refer to pWirelessEventText).

			ex: 11:22:33:44:55:66 has associated successfully

		p.s. The requirement of Wireless Extension is v15 or newer. 

	========================================================================
*/
VOID RtmpDrvSendWirelessEvent(
	IN	VOID					*pAdSrc,
	IN	USHORT					Event_flag,
	IN	PUCHAR 					pAddr,
	IN  UCHAR					BssIdx,
	IN	CHAR					Rssi)
{
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)pAdSrc;
	PSTRING	pBuf = NULL, pBufPtr = NULL;
	USHORT	event, type, BufLen;	
	UCHAR	event_table_len = 0;

	if (pAd->CommonCfg.bWirelessEvent == FALSE)
		return;

	type = Event_flag & 0xFF00;	
	event = Event_flag & 0x00FF;

	switch (type)
	{
		case IW_SYS_EVENT_FLAG_START:
			event_table_len = IW_SYS_EVENT_TYPE_NUM;
			break;
#ifdef IDS_SUPPORT
		case IW_SPOOF_EVENT_FLAG_START:
			event_table_len = IW_SPOOF_EVENT_TYPE_NUM;
			break;

		case IW_FLOOD_EVENT_FLAG_START:
			event_table_len = IW_FLOOD_EVENT_TYPE_NUM;
			break;
#endif /* IDS_SUPPORT */ 			
#ifdef WSC_INCLUDED
		case IW_WSC_EVENT_FLAG_START:
			event_table_len = IW_WSC_EVENT_TYPE_NUM;
			break;
#endif /* WSC_INCLUDED */
#ifdef CONFIG_STA_SUPPORT
#ifdef IWSC_SUPPORT
		case IW_IWSC_EVENT_FLAG_START:
			event_table_len = IW_IWSC_EVENT_TYPE_NUM;
			break;
#endif /* IWSC_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */
	}
	
	if (event_table_len == 0)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s : The type(%0x02x) is not valid.\n", __FUNCTION__, type));			       		       		
		return;
	}
	
	if (event >= event_table_len)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s : The event(%0x02x) is not valid.\n", __FUNCTION__, event));			       		       		
		return;
	}	
 
	/*Allocate memory and copy the msg. */
/*	if((pBuf = kmalloc(IW_CUSTOM_MAX_LEN, GFP_ATOMIC)) != NULL) */
	os_alloc_mem(NULL, (UCHAR **)&pBuf, IW_CUSTOM_MAX_LEN);
	if(pBuf != NULL)
	{
		/*Prepare the payload */
		memset(pBuf, 0, IW_CUSTOM_MAX_LEN);

		pBufPtr = pBuf;		

		if (pAddr)
			pBufPtr += sprintf(pBufPtr, "(RT2860) STA(%02x:%02x:%02x:%02x:%02x:%02x) ", PRINT_MAC(pAddr));				
		else if (BssIdx < MAX_MBSSID_NUM(pAd))
			pBufPtr += sprintf(pBufPtr, "(RT2860) BSS(ra%d) ", BssIdx);
		else
			pBufPtr += sprintf(pBufPtr, "(RT2860) ");

		if (type == IW_SYS_EVENT_FLAG_START)
        {
			pBufPtr += sprintf(pBufPtr, "%s", pWirelessSysEventText[event]);
		    
            if (Event_flag == IW_CHANNEL_CHANGE_EVENT_FLAG)
		  	{
			 	pBufPtr += sprintf(pBufPtr, "%3d", Rssi);
			}			
		}
#ifdef IDS_SUPPORT		
		else if (type == IW_SPOOF_EVENT_FLAG_START)
			pBufPtr += sprintf(pBufPtr, "%s (RSSI=%d)", pWirelessSpoofEventText[event], Rssi);
		else if (type == IW_FLOOD_EVENT_FLAG_START)
			pBufPtr += sprintf(pBufPtr, "%s", pWirelessFloodEventText[event]);
#endif /* IDS_SUPPORT */		
#ifdef WSC_INCLUDED
		else if (type == IW_WSC_EVENT_FLAG_START)
			pBufPtr += sprintf(pBufPtr, "%s", pWirelessWscEventText[event]);
#endif /* WSC_INCLUDED */
#ifdef CONFIG_STA_SUPPORT
#ifdef IWSC_SUPPORT
		else if (type == IW_IWSC_EVENT_FLAG_START)
			pBufPtr += sprintf(pBufPtr, "%s", pWirelessIWscEventText[event]);
#endif /* IWSC_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */
		else
			pBufPtr += sprintf(pBufPtr, "%s", "unknown event");
		
		pBufPtr[pBufPtr - pBuf] = '\0';
		BufLen = pBufPtr - pBuf;
		
		RtmpOSWrielessEventSend(pAd->net_dev, RT_WLAN_EVENT_CUSTOM, Event_flag, NULL, (PUCHAR)pBuf, BufLen);
		/*DBGPRINT(RT_DEBUG_TRACE, ("%s : %s\n", __FUNCTION__, pBuf)); */
	
/*		kfree(pBuf); */
		os_free_mem(NULL, pBuf);
	}
	else
		DBGPRINT(RT_DEBUG_ERROR, ("%s : Can't allocate memory for wireless event.\n", __FUNCTION__));			       		       				
}
#endif /* SYSTEM_LOG_SUPPORT */


void RTMP_IndicateMediaState(
	IN	PRTMP_ADAPTER		pAd,
	IN  NDIS_MEDIA_STATE	media_state)
{	
	pAd->IndicateMediaState = media_state;

#ifdef SYSTEM_LOG_SUPPORT
		if (pAd->IndicateMediaState == NdisMediaStateConnected)
		{
			RTMPSendWirelessEvent(pAd, IW_STA_LINKUP_EVENT_FLAG, pAd->MacTab.Content[BSSID_WCID].Addr, BSS0, 0);
		}
		else
		{							
			RTMPSendWirelessEvent(pAd, IW_STA_LINKDOWN_EVENT_FLAG, pAd->MacTab.Content[BSSID_WCID].Addr, BSS0, 0); 		
		}	
#endif /* SYSTEM_LOG_SUPPORT */
}


void tbtt_tasklet(unsigned long data)
{
#ifdef CONFIG_AP_SUPPORT
#ifdef WORKQUEUE_BH
	struct work_struct *work = (struct work_struct *)data;
	POS_COOKIE pObj = container_of(work, struct os_cookie, tbtt_task);
	RTMP_ADAPTER *pAd = (RTMP_ADAPTER *)pObj->pAd_va;
#else
		PRTMP_ADAPTER pAd = (RTMP_ADAPTER *)data;
#endif /* WORKQUEUE_BH */

#ifdef RTMP_MAC_PCI
	if (pAd->OpMode == OPMODE_AP)
	{
#ifdef AP_QLOAD_SUPPORT
		/* update channel utilization */
		QBSS_LoadUpdate(pAd, 0);
#endif /* AP_QLOAD_SUPPORT */

#ifdef DOT11K_RRM_SUPPORT
		RRM_QuietUpdata(pAd);
#endif /* DOT11K_RRM_SUPPORT */
	}
#endif /* RTMP_MAC_PCI */

#ifdef P2P_SUPPORT
	if (P2P_INF_ON(pAd) && P2P_GO_ON(pAd))																											  
#else
	if (pAd->OpMode == OPMODE_AP)
#endif /* P2P_SUPPORT */
	{
		/* step 7 - if DTIM, then move backlogged bcast/mcast frames from PSQ to TXQ whenever DtimCount==0 */
#ifdef RTMP_MAC_USB   
		if ((pAd->ApCfg.DtimCount + 1) == pAd->ApCfg.DtimPeriod)
#endif /* RTMP_MAC_USB */
#ifdef RTMP_MAC_PCI
		/* 
			NOTE:
			This updated BEACON frame will be sent at "next" TBTT instead of at cureent TBTT. The reason is
			because ASIC already fetch the BEACON content down to TX FIFO before driver can make any
			modification. To compenstate this effect, the actual time to deilver PSQ frames will be
			at the time that we wrapping around DtimCount from 0 to DtimPeriod-1
		*/
		if (pAd->ApCfg.DtimCount == 0)
#endif /* RTMP_MAC_PCI */
		{
			PQUEUE_ENTRY    pEntry;
			BOOLEAN			bPS = FALSE;
			UINT 			count = 0;
			unsigned long 		IrqFlags;

/*			NdisAcquireSpinLock(&pAd->MacTabLock); */
/*			NdisAcquireSpinLock(&pAd->TxSwQueueLock); */
			
			RTMP_IRQ_LOCK(&pAd->irq_lock, IrqFlags);
			while (pAd->MacTab.McastPsQueue.Head)
			{
				bPS = TRUE;
				if (pAd->TxSwQueue[QID_AC_BE].Number <= (pAd->TxSwQMaxLen + MAX_PACKETS_IN_MCAST_PS_QUEUE))
				{
					pEntry = RemoveHeadQueue(&pAd->MacTab.McastPsQueue);
					/*if(pAd->MacTab.McastPsQueue.Number) */
					if (count)
					{
						RTMP_SET_PACKET_MOREDATA(pEntry, TRUE);
					}
					InsertHeadQueue(&pAd->TxSwQueue[QID_AC_BE], pEntry);
					count++;
				}
				else
				{
					break;
				}
			}
			RTMP_IRQ_UNLOCK(&pAd->irq_lock, IrqFlags);
			
#ifdef RELEASE_EXCLUDE
			DBGPRINT(RT_DEBUG_INFO, ("DTIM=%d/%d, tx mcast/bcast out...\n",pAd->ApCfg.DtimCount,pAd->ApCfg.DtimPeriod));
#endif /* RELEASE_EXCLUDE */			
			
/*			NdisReleaseSpinLock(&pAd->TxSwQueueLock); */
/*			NdisReleaseSpinLock(&pAd->MacTabLock); */
			if (pAd->MacTab.McastPsQueue.Number == 0)
			{			
		                UINT bss_index;

                		/* clear MCAST/BCAST backlog bit for all BSS */
				for(bss_index=BSS0; bss_index<pAd->ApCfg.BssidNum; bss_index++)
					WLAN_MR_TIM_BCMC_CLEAR(bss_index);
			}
			pAd->MacTab.PsQIdleCount = 0;

			/* Dequeue outgoing framea from TxSwQueue0..3 queue and process it */
			if (bPS == TRUE) 
			{
				RTMPDeQueuePacket(pAd, FALSE, NUM_OF_TX_RING, /*MAX_TX_IN_TBTT*/MAX_PACKETS_IN_MCAST_PS_QUEUE);
			}
		}
	}
#endif /* CONFIG_AP_SUPPORT */
}


void announce_802_3_packet(
	IN VOID *pAdSrc,
	IN PNDIS_PACKET pPacket,
	IN UCHAR OpMode)
{
	RTMP_ADAPTER *pAd = (RTMP_ADAPTER *)pAdSrc;
	PNDIS_PACKET pRxPkt = pPacket;

	ASSERT(pPacket);
	MEM_DBG_PKT_FREE_INC(pPacket);

#ifdef DOT11V_WNM_SUPPORT
#ifdef CONFIG_STA_SUPPORT
	/* drop the match DMS flow data*/
	if(RxDMSHandle(pAd, pPacket) == NDIS_STATUS_FAILURE)
		return;
#endif /* CONFIG_STA_SUPPORT */
#endif /* DOT11V_WNM_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
#ifdef APCLI_SUPPORT
#ifdef P2P_SUPPORT
	if (OpMode == OPMODE_AP)
#else
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
#endif /* P2P_SUPPORT */
	{
		if (RTMP_MATPktRxNeedConvert(pAd, RtmpOsPktNetDevGet(pRxPkt)))
			RTMP_MATEngineRxHandle(pAd, pRxPkt, 0);
	}
#endif /* APCLI_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef ETH_CONVERT_SUPPORT
#ifdef P2P_SUPPORT
		if (OpMode == OPMODE_STA)
#else
		IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
#endif /* P2P_SUPPORT */
		{
			if (RTMP_MATPktRxNeedConvert(pAd, RtmpOsPktNetDevGet(pRxPkt)) &&
				(pAd->EthConvert.ECMode & ETH_CONVERT_MODE_DONGLE))
				RTMP_MATEngineRxHandle(pAd, pRxPkt, 0);
		}
#endif /* ETH_CONVERT_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

    /* Push up the protocol stack */
#ifdef CONFIG_AP_SUPPORT
#ifdef PLATFORM_BL2348
{
	extern int (*pToUpperLayerPktSent)(PNDIS_PACKET *pSkb);
	RtmpOsPktProtocolAssign(pRxPkt);
	pToUpperLayerPktSent(pRxPkt);
	return;
}
#endif /* PLATFORM_BL2348 */
#endif /* CONFIG_AP_SUPPORT */

#ifdef IKANOS_VX_1X0
{
	IKANOS_DataFrameRx(pAd, pRxPkt);
	return;
}
#endif /* IKANOS_VX_1X0 */

#ifdef INF_PPA_SUPPORT
	if (ppa_hook_directpath_send_fn && pAd->PPAEnable==TRUE ) 
	{
		RtmpOsPktInfPpaSend(pRxPkt);
		pRxPkt=NULL;
		return;
	}	  	
#endif /* INF_PPA_SUPPORT */

#ifdef RTMP_RBUS_SUPPORT
	if (pAd->infType == RTMP_DEV_INF_RBUS)
	{
#ifdef CONFIG_RT2880_BRIDGING_ONLY
		PACKET_CB_ASSIGN(pRxPkt, 22) = 0xa8;
#endif

#if defined(CONFIG_RA_CLASSIFIER)||defined(CONFIG_RA_CLASSIFIER_MODULE)
		if(ra_classifier_hook_rx!= NULL)
		{
			unsigned int flags;
			
			RTMP_IRQ_LOCK(&pAd->page_lock, flags);
			ra_classifier_hook_rx(pRxPkt, classifier_cur_cycle);
			RTMP_IRQ_UNLOCK(&pAd->page_lock, flags);
		}
#endif /* CONFIG_RA_CLASSIFIER */

#if !defined(CONFIG_RA_NAT_NONE)
#if defined (CONFIG_RA_HW_NAT)  || defined (CONFIG_RA_HW_NAT_MODULE)
		RtmpOsPktNatMagicTag(pRxPkt);
#endif

		/* bruce+
		  * ra_sw_nat_hook_rx return 1 --> continue
		  * ra_sw_nat_hook_rx return 0 --> FWD & without netif_rx
		 */
		if (ra_sw_nat_hook_rx!= NULL)
		{
			unsigned int flags;
			
			RtmpOsPktProtocolAssign(pRxPkt);

			RTMP_IRQ_LOCK(&pAd->page_lock, flags);
			if(ra_sw_nat_hook_rx(pRxPkt)) 
			{
				RtmpOsPktRcvHandle(pRxPkt);
			}
			RTMP_IRQ_UNLOCK(&pAd->page_lock, flags);
		}
#else
		{
#if defined (CONFIG_RA_HW_NAT)  || defined (CONFIG_RA_HW_NAT_MODULE)
			RtmpOsPktNatNone(pRxPkt);
#endif /* CONFIG_RA_HW_NAT */
		}
#endif /* CONFIG_RA_NAT_NONE */
	}
#endif /* RTMP_RBUS_SUPPORT */

	
#ifdef CONFIG_AP_SUPPORT
#ifdef BG_FT_SUPPORT
		if (BG_FTPH_PacketFromApHandle(pRxPkt) == 0)
			return;
#endif /* BG_FT_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */

//+++Add by shiang for debug
if (0) {
		hex_dump("announce_802_3_packet", GET_OS_PKT_DATAPTR(pRxPkt), GET_OS_PKT_LEN(pRxPkt));
}
//---Add by shiang for debug

		RtmpOsPktProtocolAssign(pRxPkt);
		RtmpOsPktRcvHandle(pRxPkt);
}


#ifdef CONFIG_STA_SUPPORT
void STA_MonPktSend(
	IN RTMP_ADAPTER *pAd,
	IN RX_BLK *pRxBlk)
{
	PNET_DEV pNetDev;
	PNDIS_PACKET pRxPacket;
	PHEADER_802_11 pHeader;
	USHORT DataSize;
	UINT32 MaxRssi;
	UCHAR L2PAD, PHYMODE, BW, ShortGI, MCS, AMPDU, STBC, RSSI1;
	UCHAR BssMonitorFlag11n, Channel, CentralChannel;
	UCHAR *pData, *pDevName;


	/* sanity check */
    ASSERT(pRxBlk->pRxPacket);
    if (pRxBlk->DataSize < 10)
    {
        DBGPRINT(RT_DEBUG_ERROR, ("%s : Size is too small! (%d)\n", __FUNCTION__, pRxBlk->DataSize));
		goto err_free_sk_buff;
    }

    if (pRxBlk->DataSize + sizeof(wlan_ng_prism2_header) > RX_BUFFER_AGGRESIZE)
    {
        DBGPRINT(RT_DEBUG_ERROR, ("%s : Size is too large! (%d)\n", __FUNCTION__, pRxBlk->DataSize + sizeof(wlan_ng_prism2_header)));
		goto err_free_sk_buff;
    }

	/* init */
#ifdef MT7601
	if ( IS_MT7601(pAd) )
		MaxRssi = ConvertToRssi(pAd, pRxBlk->pRxWI->RxWISNR2, RSSI_0, pRxBlk->pRxWI->RxWISNR1, pRxBlk->pRxWI->RxWIBW);
	else
#endif /* MT7601 */
	MaxRssi = RTMPMaxRssi(pAd,
						ConvertToRssi(pAd, pRxBlk->pRxWI->RxWIRSSI0, RSSI_0, 0, 0),
						ConvertToRssi(pAd, pRxBlk->pRxWI->RxWIRSSI1, RSSI_1, 0, 0),
						ConvertToRssi(pAd, pRxBlk->pRxWI->RxWIRSSI2, RSSI_2, 0, 0));

	pNetDev = get_netdev_from_bssid(pAd, BSS0); 
	pRxPacket = pRxBlk->pRxPacket;
	pHeader = pRxBlk->pHeader;
	pData = pRxBlk->pData;
	DataSize = pRxBlk->DataSize;
	L2PAD = pRxBlk->pRxInfo->L2PAD;
	PHYMODE = pRxBlk->pRxWI->RxWIPhyMode;
	BW = pRxBlk->pRxWI->RxWIBW;
	ShortGI = pRxBlk->pRxWI->RxWISGI;
	MCS = pRxBlk->pRxWI->RxWIMCS;
	AMPDU = pRxBlk->pRxInfo->AMPDU;
	STBC = pRxBlk->pRxWI->RxWISTBC;
	RSSI1 = pRxBlk->pRxWI->RxWIRSSI1;
	BssMonitorFlag11n = 0;
#ifdef MONITOR_FLAG_11N_SNIFFER_SUPPORT
	BssMonitorFlag11n = (pAd->StaCfg.BssMonitorFlag & MONITOR_FLAG_11N_SNIFFER);
#endif /* MONITOR_FLAG_11N_SNIFFER_SUPPORT */
	pDevName = (UCHAR *)RtmpOsGetNetDevName(pAd->net_dev);
	Channel = pAd->CommonCfg.Channel;
	CentralChannel = pAd->CommonCfg.CentralChannel;

	/* pass the packet */
	send_monitor_packets(pNetDev, pRxPacket, pHeader, pData, DataSize,
						L2PAD, PHYMODE, BW, ShortGI, MCS, AMPDU, STBC, RSSI1,
						BssMonitorFlag11n, pDevName, Channel, CentralChannel,
						MaxRssi);
	return;

err_free_sk_buff:
	RELEASE_NDIS_PACKET(pAd, pRxBlk->pRxPacket, NDIS_STATUS_FAILURE);	
	return;
}
#endif /* CONFIG_STA_SUPPORT */


extern NDIS_SPIN_LOCK TimerSemLock;

VOID	RTMPFreeAdapter(
	IN	VOID		*pAdSrc)
{
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)pAdSrc;
	POS_COOKIE os_cookie;
	int index;	

	os_cookie=(POS_COOKIE)pAd->OS_Cookie;

	if (pAd->BeaconBuf)
		os_free_mem(NULL, pAd->BeaconBuf);


	NdisFreeSpinLock(&pAd->MgmtRingLock);
	
#ifdef RTMP_MAC_PCI 
	NdisFreeSpinLock(&pAd->RxRingLock);
#if defined(RT3090) || defined(RT3592) || defined(RT3390) || defined(RT3593)
	NdisFreeSpinLock(&pAd->McuCmdLock);
#endif /* defined(RT3090) || defined(RT3592) || defined(RT3390) || defined(RT3593) */

#if defined(RT3290) || defined(RT65xx) || defined(MT7601)
	NdisFreeSpinLock(&pAd->WlanEnLock);
#endif /* defined(RT3290) || defined(RT65xx) || defined(MT7601) */

#endif /* RTMP_MAC_PCI */

	for (index =0 ; index < NUM_OF_TX_RING; index++)
	{
		NdisFreeSpinLock(&pAd->TxSwQueueLock[index]);
		NdisFreeSpinLock(&pAd->DeQueueLock[index]);
		pAd->DeQueueRunning[index] = FALSE;
	}
	
	NdisFreeSpinLock(&pAd->irq_lock);

#ifdef RTMP_MAC_PCI
	NdisFreeSpinLock(&pAd->LockInterrupt);
#endif /* RTMP_MAC_PCI */

#ifdef SPECIFIC_BCN_BUF_SUPPORT
	NdisFreeSpinLock(&pAd->ShrMemLock);
#endif /* SPECIFIC_BCN_BUF_SUPPORT */

#ifdef UAPSD_SUPPORT
	NdisFreeSpinLock(&pAd->UAPSDEOSPLock); /* OS_ABL_SUPPORT */
#endif /* UAPSD_SUPPORT */

#ifdef DOT11_N_SUPPORT
	NdisFreeSpinLock(&pAd->mpdu_blk_pool.lock);
#endif /* DOT11_N_SUPPORT */

	if (pAd->iw_stats)
	{
		os_free_mem(NULL, pAd->iw_stats);
		pAd->iw_stats = NULL;
	}
	if (pAd->stats)
	{
		os_free_mem(NULL, pAd->stats);
		pAd->stats = NULL;
	}

	NdisFreeSpinLock(&TimerSemLock);

#ifdef RALINK_ATE
#ifdef RTMP_MAC_USB
	RTMP_OS_ATMOIC_DESTROY(&pAd->BulkOutRemained);
	RTMP_OS_ATMOIC_DESTROY(&pAd->BulkInRemained);
#endif /* RTMP_MAC_USB */
#endif /* RALINK_ATE */

	RTMP_OS_FREE_TIMER(pAd);
	RTMP_OS_FREE_LOCK(pAd);
	RTMP_OS_FREE_TASKLET(pAd);
	RTMP_OS_FREE_TASK(pAd);
	RTMP_OS_FREE_SEM(pAd);
	RTMP_OS_FREE_ATOMIC(pAd);

	RtmpOsVfree(pAd); /* pci_free_consistent(os_cookie->pci_dev,sizeof(RTMP_ADAPTER),pAd,os_cookie->pAd_pa); */
	if (os_cookie)
		os_free_mem(NULL, os_cookie);
}


int	RTMPSendPackets(
	IN NDIS_HANDLE dev_hnd,
	IN PPNDIS_PACKET ppPacketArray,
	IN UINT NumberOfPackets,
	IN UINT32 PktTotalLen,
	IN RTMP_NET_ETH_CONVERT_DEV_SEARCH Func)
{
	RTMP_ADAPTER *pAd = (RTMP_ADAPTER *)dev_hnd;
	PNDIS_PACKET pPacket = ppPacketArray[0];


	INC_COUNTER64(pAd->WlanCounters.TransmitCountFrmOs);

	if (pPacket == NULL)
		goto done;

	/* RT2870STA does this in RTMPSendPackets() */
#ifdef RALINK_ATE
	if (ATE_ON(pAd))
	{
		RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_RESOURCES);
		return 0;
	}
#endif /* RALINK_ATE */

#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		/* Drop send request since we are in monitor mode */
		if (MONITOR_ON(pAd))
		{
			RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
			return 0;
		}
	}
#endif /* CONFIG_STA_SUPPORT */

        /* EapolStart size is 18 */
	if (PktTotalLen < 14)
	{
		/*printk("bad packet size: %d\n", pkt->len); */
		hex_dump("bad packet", GET_OS_PKT_DATAPTR(pPacket), PktTotalLen);
		RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
		return 0;
	}

#ifdef RTMP_RBUS_SUPPORT
	if (pAd->infType == RTMP_DEV_INF_RBUS)
	{
#if !defined(CONFIG_RA_NAT_NONE)
/* bruce+
 */
	if(ra_sw_nat_hook_tx!= NULL)
	{
		unsigned long flags;

		RTMP_INT_LOCK(&pAd->page_lock, flags);
		ra_sw_nat_hook_tx(pPacket);
		RTMP_INT_UNLOCK(&pAd->page_lock, flags);
	}
#endif
	}
#endif /* RTMP_RBUS_SUPPORT */

#if 0
/*	if ((pkt->data[0] & 0x1) == 0) */
	{
		/*hex_dump(__FUNCTION__, pkt->data, pkt->len); */
		printk("pPacket = %x\n", pPacket);
	}
#endif

	RTMP_SET_PACKET_5VT(pPacket, 0);
/*	MiniportMMRequest(pAd, pkt->data, pkt->len); */
#ifdef CONFIG_5VT_ENHANCE
    if (*(int*)(GET_OS_PKT_CB(pPacket)) == BRIDGE_TAG) {
		RTMP_SET_PACKET_5VT(pPacket, 1);
    }
#endif

#ifdef CONFIG_AP_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
		APSendPackets((NDIS_HANDLE)pAd, (PPNDIS_PACKET) &pPacket, 1);
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
#ifdef P2P_SUPPORT
		if (RTMP_GET_PACKET_OPMODE(pPacket))
		{
			APSendPackets((NDIS_HANDLE)pAd, (PPNDIS_PACKET) &pPacket, 1);
			goto done;
		}
#endif /* P2P_SUPPORT */
#ifdef ETH_CONVERT_SUPPORT
		UCHAR *pData = GET_OS_PKT_DATAPTR(pPacket);

		/* Don't move this checking into STASendPackets(), becasue the net_device is OS-depeneded. */
		if ((pAd->EthConvert.ECMode & ETH_CONVERT_MODE_CLONE) 
			 && (!pAd->EthConvert.CloneMacVaild)
		 	&& (pAd->EthConvert.macAutoLearn)
		 	&& (!(pData[6] & 0x1)))
		{
			VOID *pNetDev = Func(pAd->net_dev, pData);

			if (!pNetDev) {
				NdisMoveMemory(&pAd->EthConvert.EthCloneMac[0], &pData[6], MAC_ADDR_LEN);
				pAd->EthConvert.CloneMacVaild = TRUE;
#ifdef RELEASE_EXCLUDE
				DBGPRINT(RT_DEBUG_INFO, ("Incming Mac=%02x:%02x:%02x:%02x:%02x:%02x, NewMAC=%02x:%02x:%02x:%02x:%02x:%02x!\n",
					pData[6], pData[7] , pData[8] , pData[9] , pData[10], pData[11],   
					pAd->EthConvert.EthCloneMac[0], pAd->EthConvert.EthCloneMac[1], pAd->EthConvert.EthCloneMac[2],
					pAd->EthConvert.EthCloneMac[3], pAd->EthConvert.EthCloneMac[4], pAd->EthConvert.EthCloneMac[5]));
#endif /* RELEASE_EXCLUDE */				
			}
		}

		if ((pAd->EthConvert.ECMode == ETH_CONVERT_MODE_CLONE)
			&& (NdisEqualMemory(pAd->CurrentAddress, &pData[6], MAC_ADDR_LEN) == FALSE))
		{
			/* Drop pkt since we are in pure clone mode and the src is not the cloned mac address. */
			RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
			goto done;
		}
#endif /* ETH_CONVERT_SUPPORT */

		STASendPackets((NDIS_HANDLE)pAd, (PPNDIS_PACKET) &pPacket, 1);
	}

#endif /* CONFIG_STA_SUPPORT */

done:
	return 0;
}


PNET_DEV get_netdev_from_bssid(
	IN	PRTMP_ADAPTER	pAd,
	IN	UCHAR			FromWhichBSSID)
{
	PNET_DEV dev_p = NULL;
#ifdef CONFIG_AP_SUPPORT
	UCHAR infRealIdx;
#endif /* CONFIG_AP_SUPPORT */

	do
	{
#ifdef CONFIG_STA_SUPPORT
#ifdef P2P_SUPPORT
		if(FromWhichBSSID >= MIN_NET_DEVICE_FOR_P2P_GO)
		{
			dev_p = pAd->ApCfg.MBSSID[BSS0].MSSIDDev;
			break;
		}
#endif /* P2P_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */
#ifdef MESH_SUPPORT
	if(FromWhichBSSID >= MIN_NET_DEVICE_FOR_MESH)
	{
		dev_p = pAd->MeshTab.dev;
			break;
	} 
#endif /* MESH_SUPPORT */
#ifdef CONFIG_AP_SUPPORT
		infRealIdx = FromWhichBSSID & (NET_DEVICE_REAL_IDX_MASK);
#ifdef APCLI_SUPPORT
		if(FromWhichBSSID >= MIN_NET_DEVICE_FOR_APCLI)
		{
			dev_p = (infRealIdx >= MAX_APCLI_NUM ? NULL : pAd->ApCfg.ApCliTab[infRealIdx].dev);
			break;
		} 
#endif /* APCLI_SUPPORT */
#ifdef WDS_SUPPORT
		if(FromWhichBSSID >= MIN_NET_DEVICE_FOR_WDS)
		{
			dev_p = ((infRealIdx >= MAX_WDS_ENTRY) ? NULL : pAd->WdsTab.WdsEntry[infRealIdx].dev);
			break;
		}
#endif /* WDS_SUPPORT */

		if ((FromWhichBSSID > 0) &&
			(FromWhichBSSID < pAd->ApCfg.BssidNum) &&
				(FromWhichBSSID < MAX_MBSSID_NUM(pAd)) &&
				(FromWhichBSSID < HW_BEACON_MAX_NUM))
    		{
    	    		dev_p = pAd->ApCfg.MBSSID[FromWhichBSSID].MSSIDDev;
    		}
		else
#endif /* CONFIG_AP_SUPPORT */
		{
			dev_p = pAd->net_dev;
		}

#if 0
#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		dev_p = pAd->net_dev;
	}
#endif /* CONFIG_STA_SUPPORT */
#endif
	} while (FALSE);

	ASSERT(dev_p);
	return dev_p; /* return one of MBSS */
}


#ifdef CONFIG_AP_SUPPORT
/*
========================================================================
Routine Description:
	Driver pre-Ioctl for AP.

Arguments:
	pAdSrc			- WLAN control block pointer
	pCB				- the IOCTL parameters

Return Value:
	NDIS_STATUS_SUCCESS	- IOCTL OK
	Otherwise			- IOCTL fail

Note:
========================================================================
*/
INT RTMP_AP_IoctlPrepare(
	IN	RTMP_ADAPTER			*pAd,
	IN	VOID					*pCB)
{
	RT_CMD_AP_IOCTL_CONFIG *pConfig = (RT_CMD_AP_IOCTL_CONFIG *)pCB;
	POS_COOKIE pObj;
	USHORT index;
	INT	Status = NDIS_STATUS_SUCCESS;
#ifdef CONFIG_APSTA_MIXED_SUPPORT
	INT cmd = 0xff;
#endif /* CONFIG_APSTA_MIXED_SUPPORT */


	pObj = (POS_COOKIE) pAd->OS_Cookie;
	
    if((pConfig->priv_flags == INT_MAIN) && !RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
		if (pConfig->pCmdData == NULL)
			return Status;
		
		if (RtPrivIoctlSetVal() == pConfig->CmdId_RTPRIV_IOCTL_SET)
		{
			if (TRUE
#ifdef CONFIG_APSTA_MIXED_SUPPORT
				&& (strstr(pConfig->pCmdData, "OpMode") == NULL)
#endif /* CONFIG_APSTA_MIXED_SUPPORT */
#ifdef SINGLE_SKU
				&& (strstr(pConfig->pCmdData, "ModuleTxpower") == NULL)
#endif /* SINGLE_SKU */
				)

			{
				return -ENETDOWN;
			}
		}
		else
			return -ENETDOWN;
    }

    /* determine this ioctl command is comming from which interface. */
    if (pConfig->priv_flags == INT_MAIN)
    {
		pObj->ioctl_if_type = INT_MAIN;
        pObj->ioctl_if = MAIN_MBSSID;
/*        DBGPRINT(RT_DEBUG_INFO, ("rt28xx_ioctl I/F(ra%d)(flags=%d): cmd = 0x%08x\n", pObj->ioctl_if, RT_DEV_PRIV_FLAGS_GET(net_dev), cmd)); */
    }
    else if (pConfig->priv_flags == INT_MBSSID)
    {
		pObj->ioctl_if_type = INT_MBSSID;
/*    	if (!RTMPEqualMemory(net_dev->name, pAd->net_dev->name, 3))  // for multi-physical card, no MBSSID */
		if (strcmp(pConfig->name, RtmpOsGetNetDevName(pAd->net_dev)) != 0) /* sample */
    	{
	        for (index = 1; index < pAd->ApCfg.BssidNum; index++)
	    	{
	    	    if (pAd->ApCfg.MBSSID[index].MSSIDDev == pConfig->net_dev)
	    	    {
	    	        pObj->ioctl_if = index;
	    	        
/*	    	        DBGPRINT(RT_DEBUG_INFO, ("rt28xx_ioctl I/F(ra%d)(flags=%d): cmd = 0x%08x\n", index, RT_DEV_PRIV_FLAGS_GET(net_dev), cmd)); */
	    	        break;
	    	    }
	    	}
	        /* Interface not found! */
	        if(index == pAd->ApCfg.BssidNum)
	        {
/*	        	DBGPRINT(RT_DEBUG_ERROR, ("rt28xx_ioctl can not find I/F\n")); */
	            return -ENETDOWN;
	        }
	    }
	    else    /* ioctl command from I/F(ra0) */
	    {
/*			GET_PAD_FROM_NET_DEV(pAd, net_dev); */
    	    pObj->ioctl_if = MAIN_MBSSID;
/*	        DBGPRINT(RT_DEBUG_ERROR, ("rt28xx_ioctl can not find I/F and use default: cmd = 0x%08x\n", cmd)); */
	    }
        MBSS_MR_APIDX_SANITY_CHECK(pAd, pObj->ioctl_if);
    }
#ifdef WDS_SUPPORT
	else if (pConfig->priv_flags == INT_WDS)
	{
		pObj->ioctl_if_type = INT_WDS;
		for(index = 0; index < MAX_WDS_ENTRY; index++)
		{
			if (pAd->WdsTab.WdsEntry[index].dev == pConfig->net_dev)
			{
				pObj->ioctl_if = index;

#if 0
#ifdef RELEASE_EXCLUDE 
				DBGPRINT(RT_DEBUG_INFO, ("rt28xx_ioctl I/F(wds%d)(flags=%x): cmd = 0x%08x\n", pObj->ioctl_if, cmd)); 
#endif /* RELEASE_EXCLUDE */ 
#endif
				break;
			}
			
			if(index == MAX_WDS_ENTRY)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("rt28xx_ioctl can not find wds I/F\n"));
				return -ENETDOWN;
			}
		}
	}
#endif /* WDS_SUPPORT */
#ifdef APCLI_SUPPORT
	else if (pConfig->priv_flags == INT_APCLI)
	{
		pObj->ioctl_if_type = INT_APCLI;
		for (index = 0; index < MAX_APCLI_NUM; index++)
		{
			if (pAd->ApCfg.ApCliTab[index].dev == pConfig->net_dev)
			{
				pObj->ioctl_if = index;

#if 0
#ifdef RELEASE_EXCLUDE 
				DBGPRINT(RT_DEBUG_INFO, ("rt28xx_ioctl I/F(apcli%d)(flags=%x): cmd = 0x%08x\n", pObj->ioctl_if, RT_DEV_PRIV_FLAGS_GET(net_dev), cmd)); 
#endif /* RELEASE_EXCLUDE */ 
#endif
				break;
			}

			if(index == MAX_APCLI_NUM)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("rt28xx_ioctl can not find Apcli I/F\n"));
				return -ENETDOWN;
			}
		}
		APCLI_MR_APIDX_SANITY_CHECK(pObj->ioctl_if);
	}
#endif /* APCLI_SUPPORT */
#ifdef MESH_SUPPORT
	else if (pConfig->priv_flags == INT_MESH)
	{
		pObj->ioctl_if_type = INT_MESH;
		pObj->ioctl_if = 0;
	}
#endif /* MESH_SUPPORT */
#ifdef P2P_SUPPORT
	else if (pConfig->priv_flags == INT_P2P)
	{
		pObj->ioctl_if_type = INT_P2P;
		pObj->ioctl_if = MAIN_MBSSID;
	}
#endif /* P2P_SUPPORT */
    else
    {
/*    	DBGPRINT(RT_DEBUG_WARN, ("IOCTL is not supported in WDS interface\n")); */
    	return -EOPNOTSUPP;
    }

	pConfig->apidx = pObj->ioctl_if;
	return Status;
}


VOID AP_E2PROM_IOCTL_PostCtrl(
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq,
	IN	PSTRING					msg)
{
	wrq->u.data.length = strlen(msg);
	if (copy_to_user(wrq->u.data.pointer, msg, wrq->u.data.length))
	{
		DBGPRINT(RT_DEBUG_TRACE, ("%s: copy_to_user() fail\n", __FUNCTION__));			
	}
}


VOID IAPP_L2_UpdatePostCtrl(
	IN PRTMP_ADAPTER	pAd,
    IN UINT8 *mac_p,
    IN INT  bssid)
{
}
#endif /* CONFIG_AP_SUPPORT */


//#ifdef WDS_SUPPORT
VOID AP_WDS_KeyNameMakeUp(
	IN	STRING						*pKey,
	IN	UINT32						KeyMaxSize,
	IN	INT							KeyId)
{
	snprintf(pKey, KeyMaxSize, "Wds%dKey", KeyId);
}
//#endif /* WDS_SUPPORT */

