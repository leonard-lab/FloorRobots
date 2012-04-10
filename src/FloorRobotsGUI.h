#ifndef FLOORROBOTSGUI_H
#define FLOORROBOTSGUI_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <wx/tglbtn.h>

/* Include necessary MADTraC headers */
#include "MT_Core.h"
#include "MT_GUI.h"
#include "MT_Tracking.h"
#include "MT_Robot.h"

/**********************************************************************
 * GUI Frame Class
 *********************************************************************/

class FloorRobotsControlFrame;

class FloorRobotsFrame : public MT_RobotFrameBase
{
protected:
    FloorRobotsControlFrame* m_pFloorRobotsControlFrame;

public:
    FloorRobotsFrame(wxFrame* parent,
                     wxWindowID id = wxID_ANY,
                     const wxString& title = wxT("Floor Robots GUI"), 
                     const wxPoint& pos = wxDefaultPosition, 
                     const wxSize& size = wxSize(640,480),     
                     long style = MT_FIXED_SIZE_FRAME);

    virtual ~FloorRobotsFrame();

	void doUserQuit();

    void doRobotTimedEvents();

    void initTracker();
    void initUserData();

    MT_RobotBase* getNewRobot(const char* config, const char* name);

	bool doKeyboardCallback(wxKeyEvent &event);
	bool doMouseCallback(wxMouseEvent& event, double viewport_x, double viewport_y);
    
    MT_ControlFrameBase* createControlDialog();

    void onPopupClicked(wxCommandEvent& event);
};


/**********************************************************************
 * Control Frame Class
 *********************************************************************/

class FloorRobotsControlFrame: public MT_RobotControlFrameBase
{
	friend class MT_ControlFrameBase;
	friend class MT_FrameBase;
	friend class MT_RobotFrameBase;
    friend class FloorRobotsFrame;

private:
    FloorRobotsFrame* m_pFloorRobotsFrame;

    wxToggleButton* m_pControlActiveButton;
    wxToggleButton* m_pIPCActiveButton;    

public:

	FloorRobotsControlFrame(FloorRobotsFrame* parent,
                       const int Buttons = MT_TCF_DEFAULT_BUTTONS,
                       const wxPoint& pos = wxDefaultPosition, 
                       const wxSize& size = wxSize(150,300));
	virtual ~FloorRobotsControlFrame(){};

	virtual unsigned int createButtons(wxBoxSizer* pSizer, wxPanel* pPanel);

    virtual void onControlActiveButtonClicked(wxCommandEvent& WXUNUSED(event));
    virtual void onIPCActiveButtonClicked(wxCommandEvent& WXUNUSED(event));

    void setControlActive(bool value);
    void setIPCActive(bool value);    

	virtual void enableButtons();
	virtual void enableControlButton();

};


/**********************************************************************
 * GUI App Class
 *********************************************************************/

class FloorRobotsApp
: public MT_AppBase
{
public:
    MT_FrameWithInit* createMainFrame()
    {
        return new FloorRobotsFrame(NULL);
    };
};


#endif /* FLOORROBOTSGUI_H */
