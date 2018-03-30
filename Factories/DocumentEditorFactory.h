//---------------------------------------------------------------------------
#ifndef DocumentEditorFactoryH
#define DocumentEditorFactoryH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
typedef TFrame* (__fastcall *CreateDocumentEditorFn)(Document*, TComponent*);
//---------------------------------------------------------------------------
class DocumentEditorFactory
{
private:
    typedef std::map<String, CreateDocumentEditorFn> EditorMap;
    typedef std::map<String, CreateDocumentEditorFn>::iterator EditorMapIt;
    static EditorMap   m_Editors;

public:
    static  void    __fastcall  Register(const String& documentFolder, CreateDocumentEditorFn pfnCreate);
    static  TFrame* __fastcall  Create(Document* document, TComponent* owner);
};
//---------------------------------------------------------------------------
#endif
