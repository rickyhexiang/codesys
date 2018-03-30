/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/






#include "IoDrvSpiIO.c"




/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */

#define CMPID_IoDrvSpiIO		0x2002		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CIoDrvSpiIO	    0x2002		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_IIoDrvSpiIO		0x2002		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */










RTS_HANDLE CDECL CIoDrvSpiIO::IIoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	hIoDrvSpiIO = IoDrvCreate(hIIoDrv,ClassId,iId,pResult);
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(ICmpIoDrv *)this, ITFID_ICmpIoDrv, NULL);
	Release();
	return h;
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvDelete(RTS_HANDLE hIIoDrv)
{
	RTS_RESULT Result = IoDrvDelete(hIoDrvSpiIO,hIIoDrv);
	DeleteInstance((IBase *)(ICmpIoDrv *)this);
	return Result;
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvGetInfo(IoDrvInfo **ppIoDrv)
{
	return IoDrvGetInfo(hIoDrvSpiIO,ppIoDrv);
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvGetModuleDiagnosis(IoConfigConnector *pConnector)
{
	return IoDrvGetModuleDiagnosis(hIoDrvSpiIO,pConnector);
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvIdentify(IoConfigConnector *pConnector)
{
	return IoDrvIdentify(hIoDrvSpiIO,pConnector);
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvReadInputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvReadInputs(hIoDrvSpiIO,pConnectorMapList,nCount);
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return IoDrvScanModules(hIoDrvSpiIO,pConnector,ppConnectorList,pnCount);
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvStartBusCycle(IoConfigConnector *pConnector)
{
	return IoDrvStartBusCycle(hIoDrvSpiIO,pConnector);
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount)
{
	return IoDrvUpdateConfiguration(hIoDrvSpiIO,pConnectorList,nCount);
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount)
{
	return IoDrvUpdateMapping(hIoDrvSpiIO,pTaskMapList,nCount);
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvWatchdogTrigger(IoConfigConnector *pConnector)
{
	return IoDrvWatchdogTrigger(hIoDrvSpiIO,pConnector);
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvWriteOutputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvWriteOutputs(hIoDrvSpiIO,pConnectorMapList,nCount);
}





RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvReadParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvReadParameter(hIoDrvSpiIO,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}

RTS_RESULT CDECL CIoDrvSpiIO::IIoDrvWriteParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvWriteParameter(hIoDrvSpiIO,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}







