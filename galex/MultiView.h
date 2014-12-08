#ifndef MVIEW_H_
#define MVIEW_H_

#include <TEveManager.h>

#include <TEveViewer.h>
#include <TGLViewer.h>

#include <TEveScene.h>

#include <TEveProjectionManager.h>
#include <TEveProjectionAxes.h>

#include <TEveBrowser.h>
#include <TEveWindow.h>

// MultiView
//
// Structure encapsulating standard views: 3D, r-phi and rho-z.
// Includes scenes and projection managers.
//
// Should be used in compiled mode.

class MultiView
{
public:
   TEveProjectionManager *fRPhiMgr;
   TEveProjectionManager *fRhoZMgr;

   TEveViewer            *f3DView;
   TEveViewer            *fRPhiView;
   TEveViewer            *fRhoZView;

   TEveScene             *fRPhiGeomScene;
   TEveScene             *fRhoZGeomScene;
   TEveScene             *fRPhiEventScene;
   TEveScene             *fRhoZEventScene;

   //---------------------------------------------------------------------------

   MultiView();
   
   void SetDepth(Float_t d);
   
   //---------------------------------------------------------------------------

   void ImportGeomRPhi(TEveElement* el);
   
   void ImportGeomRhoZ(TEveElement* el);
   
   void ImportEventRPhi(TEveElement* el);

   void ImportEventRhoZ(TEveElement* el);
   
   //---------------------------------------------------------------------------

   void DestroyEventRPhi();
   void DestroyEventRhoZ();
   
   ~MultiView();
};
#endif
