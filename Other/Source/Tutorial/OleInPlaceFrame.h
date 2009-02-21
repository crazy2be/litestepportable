#include "Tracer.h"

class OleInPlaceFrame : public IOleInPlaceFrame {
  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID FAR* ppvObj) {
  	MUST_BE_IMPLEMENTED("QueryInterface")
  }
  
  ULONG STDMETHODCALLTYPE AddRef() { return 1; }
  
  ULONG STDMETHODCALLTYPE Release() { return 1; }
  
  HRESULT STDMETHODCALLTYPE GetWindow( HWND FAR* lphwnd) {
  	*lphwnd = todo_hwnd;
  	return S_OK;
  }
  
  HRESULT STDMETHODCALLTYPE ContextSensitiveHelp( BOOL fEnterMode) { MUST_BE_IMPLEMENTED("ContextSensitiveHelp") }
  
  HRESULT STDMETHODCALLTYPE GetBorder( LPRECT lprectBorder) { MUST_BE_IMPLEMENTED("GetBorder") }
  
  HRESULT STDMETHODCALLTYPE RequestBorderSpace( LPCBORDERWIDTHS pborderwidths) { MUST_BE_IMPLEMENTED("RequestBorderSpace") }
  
  HRESULT STDMETHODCALLTYPE SetBorderSpace( LPCBORDERWIDTHS pborderwidths) { MUST_BE_IMPLEMENTED("SetBorderSpace") }
  
  HRESULT STDMETHODCALLTYPE SetActiveObject( IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName) { return S_OK; }
  
  HRESULT STDMETHODCALLTYPE InsertMenus( HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths) { MUST_BE_IMPLEMENTED("InsertMenus") }
  
  HRESULT STDMETHODCALLTYPE SetMenu( HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject) { return(S_OK); }
  
  HRESULT STDMETHODCALLTYPE RemoveMenus( HMENU hmenuShared) { MUST_BE_IMPLEMENTED("RemoveMenus") }
  
  HRESULT STDMETHODCALLTYPE SetStatusText( LPCOLESTR pszStatusText) { return S_OK; }
  
  HRESULT STDMETHODCALLTYPE EnableModeless( BOOL fEnable) { return S_OK; }
  
  HRESULT STDMETHODCALLTYPE TranslateAccelerator( LPMSG lpmsg, WORD wID) {
    TraceFunc("OleInPlaceFrame::TranslateAccelerator");
  	MUST_BE_IMPLEMENTED("TranslateAccelerator")
  }
};
