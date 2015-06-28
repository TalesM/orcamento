/***************************************************************
 * Name:      orcamentoApp.cpp
 * Purpose:   Code for Application Class
 * Author:    TalesM (tales.miranda88@gmail.com)
 * Created:   2015-01-10
 * Copyright: TalesM (talesm.github.io)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "orcamentoApp.h"

//(*AppHeaders
#include "ui/OrcamentoMainFrame.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(orcamentoApp);

bool orcamentoApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	OrcamentoMainFrame* Frame = new OrcamentoMainFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
