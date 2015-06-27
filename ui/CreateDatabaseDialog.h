#ifndef CREATEDATABASEDIALOG_H
#define CREATEDATABASEDIALOG_H
#include "wxcrafter.h"

class CreateDatabaseDialog : public CreateDatabaseDialogBase
{
public:
    CreateDatabaseDialog(wxWindow* parent);
    virtual ~CreateDatabaseDialog();
    
    wxString getLocation(){
        return flLocation->GetPath();
    }

    wxDateTime getStart(){
        return dtStart->GetValue();
    }
};
#endif // CREATEDATABASEDIALOG_H
