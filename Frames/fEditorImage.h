//---------------------------------------------------------------------------
#ifndef fEditorImageH
#define fEditorImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnPopup.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Buttons.hpp>
#include "LMDDckSite.hpp"
#include "Project/ImageDocuments.h"
#include "Messaging/Event.h"
#include "Graphics/Image.h"
#include "Graphics/GraphicsMode.h"
#include "CanvasTool.h"
#include "fMultiImageView.h"
#include "fToolbarShape.h"
#include "fToolbar.h"
#include "Forms/fColors.h"
//---------------------------------------------------------------------------
class TfrmEditorImage : public TFrame
{
__published:    // IDE-managed Components
    TPanel *panToolOptions;
    TPanel *panContainer;
    TActionList *tbrActions;
    TImageList *tbrImages;
    TAction *actSelect;
    TAction *actPencil;
    TAction *actFill;
    TAction *actSprayBrush;
    TAction *actEraser;
    TAction *actLine;
    TAction *actShape;
    TPopupActionBar *popTools;
    TMenuItem *mnuSelect;
    TMenuItem *mnuText;
    TMenuItem *mnuBrush;
    TMenuItem *mnuLine;
    TMenuItem *mnuShapes;
    TMenuItem *mnuDropper;
    TMenuItem *mnuSprayBrush;
    TMenuItem *mnuFill;
    TAction *actGridPixel;
    TAction *actGridCharacter;
    TPanel *panToolbar;
    TToolBar *tbrShiftRotates;
    TToolButton *btnRotateLeft;
    TToolButton *btnRotateRight;
    TToolButton *btnRotateDown;
    TToolButton *btnRotateUp;
    TToolButton *btnRotateLeft90;
    TToolButton *btnRotateRight90;
    TToolButton *btnFlipHorizontal;
    TToolButton *btnFlipVertical;
    TToolBar *tbrTools;
    TToolButton *btnSelect;
    TToolButton *btnText;
    TToolButton *btnPencil;
    TToolButton *btnLine;
    TToolButton *btnShape;
    TToolButton *btnDropper;
    TToolButton *btnSprayBrush;
    TToolButton *btnFill;
    TAction *actText;
    TAction *actDropper;
    TPanel *panSplitter1;
    TPanel *panSplitter2;
    TPanel *panSplitter3;
    TToolBar *tbrMono;
    TToolButton *btnMonoOff;
    TToolButton *btnMonoOn;
    TPanel *panSplitter4;
    TToolBar *tbrGrids;
    TToolButton *btnGridCharacter;
    TToolButton *btnGridPixel;
    TStatusBar *barStatus;
    TAction *actRotateLeft;
    TAction *actRotateRight;
    TAction *actRotateUp;
    TAction *actRotateDown;
    TAction *actFlipVertical;
    TAction *actFlipHorizontal;
    TAction *actRotateLeft90;
    TAction *actRotateRight90;
    TAction *actMonoOn;
    TAction *actMonoOff;
    TScrollBox *sbxView;
    TAction *actBrush;
    TToolButton *btnBrush;
    TToolButton *btnEraser;
    TMenuItem *mnuEraser;
    TButton *btnTool;
    TPanel *panEditorContainer;
    TPanel *panViewFrame;
    TImage *imgEditor;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TPanel *Panel1;
    TPanel *panFrameView;
    TMultiImageViewFrame *fFrameView;
    TPopupMenu *popFrames;
    TMenuItem *popAddFrame;
    TMenuItem *popInsertFrame;
    TMenuItem *popRemoveFrame;
    TToolBar *tbrAnimate;
    TToolButton *btnAnimatePlay;
    TToolButton *btnAnimateStop;
    TAction *actAnimatePlay;
    TAction *actAnimateStop;
    TAction *actToggleAnimation;
    TTimer *tmrAnimate;
    TAction *actUndo;
    TAction *actRedo;
    TPanel *Panel2;
    TfrmToolbarShape *toolbarShape;
    TMenuItem *mnuPencil;
    void __fastcall actSelectExecute(TObject *Sender);
    void __fastcall actPencilExecute(TObject *Sender);
    void __fastcall actBrushExecute(TObject *Sender);
    void __fastcall actFillExecute(TObject *Sender);
    void __fastcall actSprayBrushExecute(TObject *Sender);
    void __fastcall actEraserExecute(TObject *Sender);
    void __fastcall actLineExecute(TObject *Sender);
    void __fastcall actShapeExecute(TObject *Sender);
    void __fastcall actGridPixelExecute(TObject *Sender);
    void __fastcall actTextExecute(TObject *Sender);
    void __fastcall actDropperExecute(TObject *Sender);
    void __fastcall FrameEndDock(TObject *Sender, TObject *Target, int X, int Y);
    void __fastcall actRotateLeftExecute(TObject *Sender);
    void __fastcall actRotateRightExecute(TObject *Sender);
    void __fastcall actRotateUpExecute(TObject *Sender);
    void __fastcall actRotateDownExecute(TObject *Sender);
    void __fastcall actFlipVerticalExecute(TObject *Sender);
    void __fastcall actFlipHorizontalExecute(TObject *Sender);
    void __fastcall actRotateLeft90Execute(TObject *Sender);
    void __fastcall actRotateRight90Execute(TObject *Sender);
    void __fastcall actMonoOnExecute(TObject *Sender);
    void __fastcall actMonoOffExecute(TObject *Sender);
    void __fastcall panEditorContainerClick(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);
    void __fastcall sbxViewResize(TObject *Sender);
    void __fastcall sbxViewMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall popAddFrameClick(TObject *Sender);
    void __fastcall popInsertFrameClick(TObject *Sender);
    void __fastcall popRemoveFrameClick(TObject *Sender);
    void __fastcall actAnimatePlayExecute(TObject *Sender);
    void __fastcall actAnimateStopExecute(TObject *Sender);
    void __fastcall actToggleAnimationExecute(TObject *Sender);
    void __fastcall tmrAnimateTimer(TObject *Sender);
    void __fastcall actUndoExecute(TObject *Sender);
    void __fastcall actRedoExecute(TObject *Sender);
    void __fastcall imgEditorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgEditorMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgEditorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall fFrameViewTimer1Timer(TObject *Sender);
private:    // User declarations
    typedef std::vector<std::unique_ptr<Agdx::Image>> ImageList;
    typedef std::map<int, std::unique_ptr<CanvasTool>> CanvasToolMap;

    typedef void (__closure *wndProcPtr)(Messages::TMessage& Message);

    std::vector<int>            m_Messages;

    ImageDocument*              m_ImageDocument;    // the image document we are editing
    ImageList                   m_Frames;           // the image documents frames as bitmap images
    std::map<String, TAction*>  m_ActionMap;        // a map of actions; used by generic messaging to handle zoom in/out/reset, undo/redo
    float                       m_Magnification;    // the magnification of the main view
    int                         m_SelectedFrame;    // the frame we are editing
    CanvasToolMap               m_CanvasToolMap;    // a map to all the canvas paint tools
    int                         m_CanvasTool;       // the selected canvas paint tool
    TfrmToolbar*                m_Toolbar;          // the current tools toolbar
    std::unique_ptr<TfrmColors> m_Colors;           // colour picker window
    const Agdx::GraphicsMode&   m_GraphicsMode;     // the graphics mode used by the project
    bool                        m_WndProcHooked;
    wndProcPtr                  m_OldWndProc;

    void            __fastcall  SetDocument(Document* document);
    void            __fastcall  OnEvent(const Event& event);
    bool            __fastcall  IsActive() const;
    void            __fastcall  DrawGrids();
    void            __fastcall  RefreshView();
    void            __fastcall  RefreshFramesView();
    void            __fastcall  OnFrameSelected(TObject *Sender);
    TPoint          __fastcall  ToImagePt(int X, int Y);
    void            __fastcall  ChangeToolbar(TfrmToolbar* toolbar);
    void            __fastcall  FrameEnter(TObject *Sender);
    void            __fastcall  FrameExit(TObject *Sender);

public:        // User declarations
                    __fastcall  TfrmEditorImage(TComponent* Owner);
                    __fastcall ~TfrmEditorImage();
     static  TFrame* __fastcall Create(Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorImage(owner);
                                    editor->SetDocument(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }

    __property  ImageDocument*  Image = { read = m_ImageDocument, write = m_ImageDocument };
};
//---------------------------------------------------------------------------
#endif
