#include "FloorRobotsGUI.h"

const unsigned int FRAME_PERIOD_MSEC = 50;

/* GUI elements need unique IDs (within the appropriate
 *  scope).  Setting the first one to MT_RFB_ID_HIGHEST + (something)
 *  makes sure that we don't clobber any of the IDs that
 *  come from MADTraC */
enum
{
    ID_MENU_POP_ROBOT = MT_RFB_ID_HIGHEST + 10,
};

/**********************************************************************
 * GUI Frame Class
 *********************************************************************/

FloorRobotsFrame::FloorRobotsFrame(wxFrame* parent,
                                   wxWindowID id,
                                   const wxString& title, 
                                   const wxPoint& pos, 
                                   const wxSize& size,     
                                   long style)
  : MT_RobotFrameBase(parent, id, title, pos, size, style),
    m_pFloorRobotsControlFrame(NULL)
{
}

FloorRobotsFrame::~FloorRobotsFrame()
{
}

/* Gets called when the user quits the application.
 * Use this to gracefully stop any processes. */
void FloorRobotsFrame::doUserQuit()
{
    /* make sure we call the base class method when we're done */
	MT_RobotFrameBase::doUserQuit();
}

/* Gets called when the application is being initialized.  Use this to
 * initialize any data, set up the command line parser, add
 * preferences, etc. (stuff that happens before the user is given
 * control of the application) */
void FloorRobotsFrame::initUserData()
{
    /* make sure we do whatever the base class wanted to do */
    MT_RobotFrameBase::initUserData();

    /* set the frame period for the timer */
    setTimer(FRAME_PERIOD_MSEC);
}

/* Gets called when the user tries to connect to a new robot.
 * Use this to attach the right kind of class to the robot. */
MT_RobotBase* FloorRobotsFrame::getNewRobot(const char* config, const char* name)
{
    /* TEMPORARY: return a null pointer */
    return NULL;
}

/* Gets called when the user clicks the 'start tracking' button.
 * Use this to initialize the tracker */
void FloorRobotsFrame::initTracker()
{

    /* m_pTracker should be NULL initially - if it's not, then
     * this function has already been called and we should just
     * ignore this request */
	if(m_pTracker)
	{
		return;
	}

    /* TEMPORARY: just return */
    return;

    /* eventually: set m_pTracker with a pointer to a new instance
     * of the tracker class */
        
    /* note - do NOT call MT_TrackerBase::initTracker, which is
     * a placeholder function that sets m_pTracker to NULL! */

    /* not sure if we need to do this again */
	setTimer(FRAME_PERIOD_MSEC);
}

/* Gets called when this window has focus and a user presses a key. */
bool FloorRobotsFrame::doKeyboardCallback(wxKeyEvent& event)
{
    /* there is a bunch of built-in functionality that we can
     * inherit from MT - e.g., 'q' -> quit, 'p' -> pause -
     * but we need the ability to override those keys, so we're
     * going to return true/false depending on if we want
     * to skip the base functionality */

    /* by default, we *do* want to do the base functionality */
	bool result = MT_DO_BASE_KEY;

    /* tells us what key was pressed
     *   (it's also possible to get the x,y coordinates of the
     *     mouse and if any modifier keys (shift, ctrl, etc)
     *     were pressed) */
   	char k = event.GetKeyCode();

    /* just as an example */
	switch(k)
	{
	case 'g':
        fprintf(stdout, "You pressed 'g'!\n");
		break;
	}

    /* give the base class a chance to handle the key */
	bool tresult = MT_RobotFrameBase::doKeyboardCallback(event);

    /* the return value tells the underlying event system
     *  how to handle this event */
	return result && tresult;
}


/* Gets called when this window has focus and the user does
 * anything with the mouse (moves it, clicks, etc) */
bool FloorRobotsFrame::doMouseCallback(wxMouseEvent& event, double viewport_x, double viewport_y)
{
    /* this is handled in the same way that the keyboard callback is
     * handled; see doKeyboardCallback */

	bool result = MT_DO_BASE_MOUSE;

    /* TEMPORARY: just examples */
    fprintf(stdout, "Mouse at %f, %f\n", viewport_x, viewport_y);

    /* right click -
     *   RightUp means the user has released the button
     *   RightDown means the user has clicked down on the button
     *   Up is almost always what the user is expecting.  Use
     *   Down for dragging behaviors */
    if(event.RightUp())
    {
        /* show a popup menu */
        wxMenu popup;
        popup.Append(ID_MENU_POP_ROBOT, /* needs a unique GUI ID */
                     wxString("Popup!"));
        /* connect the event handler -
         *   means "when I click the GUI element with this ID, call
         *   this function */
        wxFrame::Connect(ID_MENU_POP_ROBOT,
                         wxEVT_COMMAND_MENU_SELECTED,
                         wxCommandEventHandler(FloorRobotsFrame::onPopupClicked));
        /* actually show the popup */
        wxFrame::PopupMenu(&popup);
        /* make sure we skip the base functionality, because we've already
         * done something! */
        result = MT_SKIP_BASE_MOUSE;
    }
    
    bool tresult = result && MT_RobotFrameBase::doMouseCallback(event, viewport_x, viewport_y);
        
    return tresult && result;
}

/* just an example - our popu event handler */
void FloorRobotsFrame::onPopupClicked(wxCommandEvent& event)
{
    fprintf(stdout, "You clicked the popup!\n");
}

/* gets called when the application is being initialized, lets us
 * create a custom control dialog (the smaller window with the buttons
 * on it) */
MT_ControlFrameBase* FloorRobotsFrame::createControlDialog()
{
    /* all we're doing here is creating a new window and then casting it
     * to various pointers that need it that way.  There shouldn't
     * be any need to modify this.  */
    m_pFloorRobotsControlFrame = new FloorRobotsControlFrame(this);
	m_pRobotControlFrame = (MT_RobotControlFrameBase *) m_pFloorRobotsControlFrame;
	m_pTrackerControlFrame = (MT_TrackerControlFrameBase *) m_pRobotControlFrame; 
	return (MT_ControlFrameBase*) m_pRobotControlFrame;
}

/**********************************************************************
 * Control Frame Class
 *********************************************************************/

/* GUI IDs for the control frame - note these will be used in a different
 * scope than the ones for the other frame, so it's ok to duplicate those
 * values */
enum
{
    ID_CONTROL_ACTIVE_BUTTON = MT_RCF_ID_HIGHEST + 10,
    ID_IPC_ACTIVE_BUTTON
};

FloorRobotsControlFrame::FloorRobotsControlFrame(FloorRobotsFrame* parent,
                                                 const int Buttons,
                                                 const wxPoint& pos, 
                                                 const wxSize& size)
    : MT_RobotControlFrameBase(parent, Buttons, pos, size),
      m_pFloorRobotsFrame(parent),
      m_pControlActiveButton(NULL),
      m_pIPCActiveButton(NULL)
{
}

/* gets called when we're creating the window - lets us inject our own
 * buttons */
unsigned int FloorRobotsControlFrame::createButtons(wxBoxSizer* pSizer, wxPanel* pPanel)
{
    unsigned int nbuttons = MT_RobotControlFrameBase::createButtons(pSizer, pPanel);

    /* create new buttons */
    m_pControlActiveButton = new wxToggleButton(pPanel,
                                                ID_CONTROL_ACTIVE_BUTTON,
                                                wxT("Activate Control"));
    m_pIPCActiveButton = new wxToggleButton(pPanel,
                                            ID_IPC_ACTIVE_BUTTON,
                                            wxT("Enable IPC"));

    /* this is just standard wx GUI layout stuff */
    pSizer->Add(m_pControlActiveButton, 0, wxALL | wxCENTER, 10);
    pSizer->Add(m_pIPCActiveButton, 0, wxALL | wxCENTER, 10);

    /* Set initial status of the buttons */
    m_pControlActiveButton->Disable();
    m_pControlActiveButton->SetValue(false);
    m_pIPCActiveButton->Enable();
    m_pIPCActiveButton->SetValue(false);

    /* connect the event handlers */
    wxFrame::Connect(ID_CONTROL_ACTIVE_BUTTON,
                     wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,
                     wxCommandEventHandler(FloorRobotsControlFrame::onControlActiveButtonClicked));
    wxFrame::Connect(ID_IPC_ACTIVE_BUTTON,
                     wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,
                     wxCommandEventHandler(FloorRobotsControlFrame::onIPCActiveButtonClicked));

    /* use by MT_ControlFrameBase to size the window appropriately */
    return nbuttons + 2;
}

void FloorRobotsControlFrame::onControlActiveButtonClicked(wxCommandEvent& WXUNUSED(event))
{
}

void FloorRobotsControlFrame::setControlActive(bool value)
{
}

void FloorRobotsControlFrame::onIPCActiveButtonClicked(wxCommandEvent& WXUNUSED(event))
{
}

void FloorRobotsControlFrame::setIPCActive(bool value)
{
    m_pIPCActiveButton->SetValue(value);
    if(value)
    {
        m_pIPCActiveButton->SetLabel(wxT("Disable IPC"));
    }
    else
    {
        m_pIPCActiveButton->SetLabel(wxT("Enable IPC"));        
    }
}

void FloorRobotsControlFrame::enableButtons()
{
    if(m_pIPCActiveButton)
    {
        m_pIPCActiveButton->Enable();
    }
    MT_RobotControlFrameBase::enableButtons();
}

void FloorRobotsControlFrame::enableControlButton()
{
    if(m_pControlActiveButton)
    {
        m_pControlActiveButton->Enable();
    }
}

/**********************************************************************
 * GUI App Class
 *********************************************************************/

IMPLEMENT_APP(FloorRobotsApp)
