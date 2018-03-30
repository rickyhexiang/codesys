#ifndef	__FIFO_H_
#define	__FIFO_H_

#pragma pack(4)
typedef struct FIFO_Type_STRU
{
	unsigned int			Depth;			// Fifo���
	volatile unsigned int	Head;			// HeadΪ��ʼԪ��
	volatile unsigned int	Tail;			// Tail-1Ϊ���һ��Ԫ��
	volatile unsigned int	Counter;		// Ԫ�ظ���
	unsigned int			ElementBytes;	// ÿ��Ԫ�ص��ֽ���element
	void					*Buff;			// ������
}FIFO_Type;
#pragma pack()

/********************************************************************//**
 * @brief       FIFO��ʼ��
 * @param[in]   pFIFO: FIFOָ��
 * @param[in]	pBuff: FIFO�л���
 * @param[in]	elementBytes:FIFOÿ��Ԫ�ص��ֽ���
 * @param[in]	depth: FIFO���
 * @return      None
 *********************************************************************/
void FIFO_Init(FIFO_Type *pFIFO, void *pBuff, unsigned int elementBytes, unsigned int depth);

/********************************************************************//**
 * @brief       ��FIFO���һ��Ԫ��
 * @param[in]   pFIFO: FIFOָ��
 * @param[in]	pValue: Ҫ��ӵ�Ԫ��
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char FIFO_AddOne(FIFO_Type *pFIFO, void *pValue);

/********************************************************************//**
 * @brief       ��FIFO��Ӷ��Ԫ��
 * @param[in]   pFIFO: FIFOָ��
 * @param[in]	pValues: Ҫ��ӵ�Ԫ��ָ��
 * @param[in]	bytesToAdd: Ҫ���Ԫ�صĳ���
 * @return      ʵ����ӵ�Ԫ�ظ���
 *********************************************************************/
unsigned int FIFO_Add(FIFO_Type *pFIFO, void *pValues, unsigned int bytesToAdd);

/********************************************************************//**
 * @brief       ��FIFO��ȡһ��Ԫ��
 * @param[in]   pFIFO: FIFOָ��
 * @param[in]	pValue: ���Ҫ��ȡ��Ԫ��ָ��
 * @return      1-TRUE or 0-FALSE
 *********************************************************************/
unsigned char FIFO_GetOne(FIFO_Type *pFIFO, void *pValue);

/********************************************************************//**
 * @brief       ��FIFO��ȡ���Ԫ��
 * @param[in]   pFIFO: FIFOָ��
 * @param[out]	pValues: ���Ҫ��ȡ��Ԫ��ָ��
 * @param[in]	bytesToRead: Ҫ��ȡ��Ԫ�س���
 * @return      ʵ�ʶ�ȡ��Ԫ�ظ���
 *********************************************************************/
unsigned int FIFO_Get(FIFO_Type *pFIFO, void *pValues, unsigned int bytesToRead);


/********************************************************************//**
 * @brief       ���FIFO
 * @param[in]   pFIFO: FIFOָ��
 * @return      None
 *********************************************************************/
void FIFO_Clear(FIFO_Type *pFIFO);


#endif