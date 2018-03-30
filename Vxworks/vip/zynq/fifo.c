/*******************************************************************************
�ļ����ƣ�fifo.c
��    �ߣ����� QQ516409354     
��    ����P1.0       
��    �ڣ�2014/2/20
�ļ�������
        ʹ��ringbufferʵ�ֵ�FIFO
�����б�
        ��
�޸���ʷ��
   <�汾>  <��    ��>  <�� ��>  <�Ķ����ݺ�ԭ��>
   ----------------------------------------------------
    1.0    2014/2/20   ����  �����Ĺ������
	1.1    2015/1/29   ����  1������FIFO_Clear()����
	                           2���Ż�FIFO�ṹ���Ա����
*******************************************************************************/

#include <string.h>
#include "fifo.h"


/********************************************************************//**
 * @brief       FIFO��ʼ��
 * @param[in]   pFIFO: FIFOָ��
 * @param[in]	pBuff: FIFO�л���
 * @param[in]	elementBytes:FIFOÿ��Ԫ�ص��ֽ���
 * @param[in]	depth: FIFO���
 * @return      None
 *********************************************************************/
void FIFO_Init(FIFO_Type *pFIFO, void *pBuff, unsigned int elementBytes, unsigned int depth)
{
	pFIFO->Buff = pBuff;
	pFIFO->ElementBytes = elementBytes;
	pFIFO->Depth = depth;
	pFIFO->Head = 0;
	pFIFO->Tail = 0;
	pFIFO->Counter = 0;
}

/********************************************************************//**
 * @brief       �ж�FIFO�Ƿ�Ϊ��
 * @param[in]   pFIFO: FIFOָ��
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char FIFO_IsEmpty(FIFO_Type *pFIFO)
{
	return (pFIFO->Counter == 0);
}

/********************************************************************//**
 * @brief       �ж�FIFO�Ƿ�����
 * @param[in]   pFIFO: FIFOָ��
 * @return      TRUE or FALSE
 *********************************************************************/
unsigned char FIFO_IsFull(FIFO_Type *pFIFO)
{
	return (pFIFO->Counter == pFIFO->Depth);
}

/********************************************************************//**
 * @brief       ��FIFO���һ��Ԫ��
 * @param[in]   pFIFO: FIFOָ��
 * @param[in]	pValue: Ҫ��ӵ�Ԫ��
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char FIFO_AddOne(FIFO_Type *pFIFO, void *pValue)
{
	unsigned char *p;

	if (FIFO_IsFull(pFIFO))
	{
		return 0;
	}

	p = (unsigned char *)pFIFO->Buff;
	memcpy(p + pFIFO->Tail * pFIFO->ElementBytes, (unsigned char *)pValue, pFIFO->ElementBytes);
	
	pFIFO->Tail ++;
	if (pFIFO->Tail >= pFIFO->Depth)
	{
		pFIFO->Tail = 0;
	}
	pFIFO->Counter ++;
	return 1;
}

/********************************************************************//**
 * @brief       ��FIFO��Ӷ��Ԫ��
 * @param[in]   pFIFO: FIFOָ��
 * @param[in]	pValues: Ҫ��ӵ�Ԫ��ָ��
 * @param[in]	bytesToAdd: Ҫ���Ԫ�صĳ���
 * @return      ʵ����ӵ�Ԫ�ظ���
 *********************************************************************/
unsigned int FIFO_Add(FIFO_Type *pFIFO, void *pValues, unsigned int bytesToAdd)
{
	unsigned char *p;
	unsigned int cnt = 0;

	p = (unsigned char *)pValues;
	while(bytesToAdd --)
	{
		if (FIFO_AddOne(pFIFO, p))
		{
			p += pFIFO->ElementBytes;
			cnt++;
		}
		else
		{
			break;
		}
	}

	return cnt;
}

/********************************************************************//**
 * @brief       ��FIFO��ȡһ��Ԫ��
 * @param[in]   pFIFO: FIFOָ��
 * @param[in]	pValue: ���Ҫ��ȡ��Ԫ��ָ��
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char FIFO_GetOne(FIFO_Type *pFIFO, void *pValue)
{
	unsigned char *p;
	if (FIFO_IsEmpty(pFIFO))
	{
		return 0;
	}

	p = (unsigned char *)pFIFO->Buff;
	memcpy(pValue, p + pFIFO->Head * pFIFO->ElementBytes, pFIFO->ElementBytes);

	pFIFO->Head ++;
	if (pFIFO->Head >= pFIFO->Depth)
	{
		pFIFO->Head = 0;
	}
	pFIFO->Counter --;

	return 1;
}

/********************************************************************//**
 * @brief       ��FIFO��ȡ���Ԫ��
 * @param[in]   pFIFO: FIFOָ��
 * @param[out]	pValues: ���Ҫ��ȡ��Ԫ��ָ��
 * @param[in]	bytesToRead: Ҫ��ȡ��Ԫ�س���
 * @return      ʵ�ʶ�ȡ��Ԫ�ظ���
 *********************************************************************/
unsigned int FIFO_Get(FIFO_Type *pFIFO, void *pValues, unsigned int bytesToRead)
{
	unsigned int cnt = 0;
	unsigned char *p;

    p = (unsigned char *)pValues;
	while(bytesToRead--)
	{
		if (FIFO_GetOne(pFIFO, p))
		{
			p += pFIFO->ElementBytes;
			cnt++;
		}
		else
		{
			break;
		}
	}

	return cnt;
}

/********************************************************************//**
 * @brief       ���FIFO
 * @param[in]   pFIFO: FIFOָ��
 * @return      None
 *********************************************************************/
void FIFO_Clear(FIFO_Type *pFIFO)
{
	pFIFO->Counter = 0;
	pFIFO->Head = 0;
	pFIFO->Tail = 0;
}
