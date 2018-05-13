//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fMain.h"
#include "ProjectManager.h"
//#include "Graphics/Palette.h"
//#include "Graphics/GraphicsMode.h"
#include "Project/MachineConfig.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
// ---------------------------------------------------------------------------
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
: TForm(Owner)
, m_FormView(fvNone)
, m_WelcomeDialog(std::unique_ptr<TfrmWelcomeDialog>(new TfrmWelcomeDialog(this)))
, m_IDEDialog(std::unique_ptr<TfrmIDE>(new TfrmIDE(this)))
, m_ImportDialog(nullptr)
{
    m_WelcomeDialog->OnDone  = OnWelcomeDone;
    m_IDEDialog->OnFormClose = OnIDEClose;
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    Application->OnMessage = AppMessage;
    theProjectManager.Initialise(m_IDEDialog->tvProject);
    // TODO: decide if we can load a project right now or load the welcome dialog
    // create the welcome screen
    if (!appSettings.WelcomeSkipOnStartup)
    {
        ShowWelcomeDialog();
    }
    else
    {
        ShowIDE();
        if (appSettings.LoadLastProject && appSettings.LastProject.Trim() != "")
        {
            theProjectManager.Open(appSettings.LastProject);
        }
    }

    // TODO: Remove: Used to generate initial JSON config files
    //auto pw = std::make_unique<PaletteWriter>();
    //auto pw = std::make_unique<GraphicsModeWriter>();
    //auto pw = std::make_unique<MachineConfigWriter>();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormActivate(TObject *Sender)
{
    static bool atStartup = true;
    if (atStartup && appSettings.WelcomeSkipOnStartup)
    {
        // We skipped the Welcome dialog; so finish off the main form setup
        m_IDEDialog->OnActivate();
    }
    atStartup = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    SaveSettings();
    if (m_FormView == fvGameIDE)
    {
        theProjectManager.Close();
        OnIDEClose(Sender);
        CanClose = appSettings.WelcomeSkipOnClose;
    }
    else if (m_FormView == fvImportDialog)
    {
        OnImportDone(nullptr);
        CanClose = false;
    }
    else
    {
        CanClose = true;
    }
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
    m_FormView = fvNone;
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::AppMessage(tagMSG &Msg, bool &Handled)
{
    if (Msg.message == WM_DPICHANGED)
    {
        // adjust toolbars
        int a = 0;
    }
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::OnIDEClose(TObject *Sender)
{
    if (!appSettings.WelcomeSkipOnClose)
    {
        // show the welcome screen
        ShowWelcomeDialog();
    }
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::OnWelcomeDone(TObject *Sender)
{
    // show the IDE
    if (Sender)
    {
        ShowIDE();
    }
    else
    {
        if (m_ImportDialog == nullptr)
        {
            m_ImportDialog = std::make_unique<TfrmImportDialog>(new TfrmImportDialog(this));
            m_ImportDialog->OnDone = OnImportDone;
        }
        ShowImportDialog();
    }
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::OnImportDone(TObject *Sender)
{
    m_ImportDialog->Visible = false;
    m_ImportDialog->Parent = nullptr;
    if (Sender)
    {
        // show the IDE
        SaveSettings();
        ShowIDE();
    }
    else
    {
        SaveSettings();
        ShowWelcomeDialog();
    }
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowWelcomeDialog()
{
    m_IDEDialog->Visible = false;
    m_IDEDialog->Parent = nullptr;
    m_WelcomeDialog->Parent = this;
    m_WelcomeDialog->Visible = true;
    m_WelcomeDialog->Initialise();
    m_FormView  = fvWelcomeDialog;
    BorderIcons = TBorderIcons() << biMinimize << biSystemMenu;
    AutoSize = true;
    BorderStyle = bsSingle;
    Menu = nullptr;
    TPoint pt = appSettings.WelcomePosition;
    Left   = pt.X;
    Top    = pt.Y;
    Width  = m_WelcomeDialog->Width;
    Height = m_WelcomeDialog->Height;
    WindowState = wsNormal;
    if (Left == 0 && Top == 0)
    {
        Position = poScreenCenter;
    }
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowImportDialog()
{
    m_IDEDialog->Visible = false;
    m_IDEDialog->Parent = nullptr;
    m_WelcomeDialog->Visible = false;
    m_WelcomeDialog->Parent = this;
    m_ImportDialog->Parent = this;
    m_ImportDialog->Visible = true;
    m_ImportDialog->Initialise();
    m_FormView  = fvImportDialog;
    BorderIcons = TBorderIcons() << biMinimize << biSystemMenu;
    AutoSize = true;
    BorderStyle = bsSingle;
    Menu = nullptr;
    TPoint pt = appSettings.WelcomePosition;
    Left   += (m_WelcomeDialog->Width - m_ImportDialog->Width) / 2;
    Top    += (m_WelcomeDialog->Height - m_ImportDialog->Height) / 2;
    Width  = m_ImportDialog->Width;
    Height = m_ImportDialog->Height;
    WindowState = wsNormal;
    if (Left == 0 && Top == 0)
    {
        Position = poScreenCenter;
    }
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowIDE()
{
    m_ImportDialog = nullptr;
    appSettings.WelcomePosition = TPoint(Left, Top);
    m_WelcomeDialog->Visible = false;
    m_WelcomeDialog->Parent = nullptr;
    m_IDEDialog->Parent = this;
    m_IDEDialog->Visible = true;
    m_IDEDialog->OnActivate();
    m_FormView = fvNone;
    AutoSize = false;
    BorderIcons = TBorderIcons() << biMaximize << biMinimize << biSystemMenu;
    BorderStyle = bsSizeable;
    // start the IDE up
    WindowState = wsNormal;
    Application->ProcessMessages();
    Left        = appSettings.WindowPosition.X;
    Top         = appSettings.WindowPosition.Y;
    Width       = appSettings.WindowSize.Width;
    Height      = appSettings.WindowSize.Height;
    WindowState = appSettings.WindowState;
    m_FormView  = fvGameIDE;
}
// ---------------------------------------------------------------------------
void __fastcall TfrmMain::SaveSettings()
{
    if (m_FormView == fvGameIDE)
    {
        appSettings.WindowState = WindowState;
        if (WindowState == wsNormal)
        {
            appSettings.WindowPosition = TPoint(Left, Top);
            appSettings.WindowSize     = TSize(Width, Height);
        }
    }
    else if (m_FormView == fvWelcomeDialog)
    {
        TPoint pt(Left, Top);
        appSettings.WelcomePosition = pt;
    }
    else if (m_FormView == fvImportDialog)
    {
        TPoint pt(Left, Top);
        pt.X -= (m_WelcomeDialog->Width - m_ImportDialog->Width) / 2;
        pt.Y -= (m_WelcomeDialog->Height - m_ImportDialog->Height) / 2;
        appSettings.WelcomePosition = pt;
    }
}
//---------------------------------------------------------------------------

