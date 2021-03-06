#pragma once
#include "Include/FTPluginCore.h"
#include "Include/FTPluginQuoteInterface.h"
#include "Protocol/ProtoDataStruct_Quote.h"
#include "TimerWnd.h"
#include "MsgHandler.h"
#include "JsonCpp/json.h"

class CPluginQuoteServer;

class CPluginPlatesetIDs : public CTimerWndInterface, public CMsgHandlerEventInterface
{
public:
	CPluginPlatesetIDs();
	virtual ~CPluginPlatesetIDs();

	void Init(CPluginQuoteServer* pQuoteServer, IFTQuoteData*  pQuoteData);
	void Uninit();	
	void SetQuoteReqData(int nCmdID, const Json::Value &jsnVal, SOCKET sock);
	void NotifyQueryPlatesetIDs(INT nCSResult, DWORD dwCookie);

	void NotifySocketClosed(SOCKET sock);

protected:	
	//CTimerWndInterface
	virtual void OnTimeEvent(UINT nEventID);

	//CMsgHandlerEventInterface
	virtual void OnMsgEvent(int nEvent,WPARAM wParam,LPARAM lParam);

protected:
	//tomodify 1
	struct	StockDataReq
	{
		SOCKET	sock;
		DWORD	dwReqTick;
		INT64	nStockID;
		DWORD nReqCookie;
		PlatesetIDs_Req req;
	};
	typedef std::vector<StockDataReq*>	VT_STOCK_DATA_REQ;
	typedef PlatesetIDsAckBody	QuoteAckDataBody;	

protected:	
	void HandleTimeoutReq();
	void ReplyAllReadyReq();
	void ReplyStockDataReq(StockDataReq *pReq, const QuoteAckDataBody &data);
	void ReplyDataReqError(StockDataReq *pReq, int nErrCode, LPCWSTR pErrDesc);

	void SetTimerHandleTimeout(bool bStartOrStop);

	void ReleaseAllReqData();

private:
	INT64 DoCalReqPlatesetID(StockMktType eMkt, PlateClass eClass);
	void DoClearReqInfo(SOCKET socket);

protected:
	CPluginQuoteServer* m_pQuoteServer;
	IFTQuoteData* m_pQuoteData;
	CTimerMsgWndEx m_TimerWnd;
	CMsgHandler m_MsgHandler;
	BOOL m_bStartTimerHandleTimeout;

	VT_STOCK_DATA_REQ m_vtReqData;
};