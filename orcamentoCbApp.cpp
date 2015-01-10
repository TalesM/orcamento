/***************************************************************
 * Name:      orcamentoCbApp.cpp
 * Purpose:   Code for Application Class
 * Author:    TalesM (tales.miranda88@gmail.com)
 * Created:   2015-01-10
 * Copyright: TalesM (talesm.github.io)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "orcamentoCbApp.h"

//(*AppHeaders
#include "orcamentoCbMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(orcamentoCbApp);

bool orcamentoCbApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	orcamentoCbFrame* Frame = new orcamentoCbFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
