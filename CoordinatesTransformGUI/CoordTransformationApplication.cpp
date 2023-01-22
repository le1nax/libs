#include "CoordTransformationApplication.h"

#include "CoordTransformationWindow.h"


#include <glibmm/miscutils.h>

// #include <Log.h>

// #include "CustomLogToFile.h"

using namespace std;
namespace fs = filesystem;
using namespace Gtk;
using namespace sigc;
// using namespace fsd::Logging;

CoordTransformationApplication::CoordTransformationApplication(int argc, char *argv[])
  : Application(argc, argv, APPLICATION_ID)
{
    Glib::set_application_name(PROJECT_NAME);
    // Log::defaultComponentName = PROJECT_NAME;
    // LogPort::activateLocalMode();
    // add_main_option_entry(Gio::Application::OptionType::OPTION_TYPE_BOOL,
    //                       "verbose",
    //                       'v',
    //                       "Outputs all messages in to the terminal");
    // add_main_option_entry(Gio::Application::OptionType::OPTION_TYPE_FILENAME,
    //                       "logFile",
    //                       'l',
    //                       "Appends all messages to the file inputed. If the path does not exist it will be created, if the path is a directory the messages will be logged to path/log.log");
}

CoordTransformationApplication::~CoordTransformationApplication()
{
    
}

void CoordTransformationApplication::on_startup()
{
    //Call the base class's implementation:
    Gtk::Application::on_startup();
}

void CoordTransformationApplication::on_activate()
{
    createWindow();
}

void CoordTransformationApplication::createWindow()
{
    mWindow = make_unique<CoordTransformationWindow>();
    mWindow->maximize();
    add_window(*mWindow);
    mWindow->show();
}

std::unique_ptr<CoordTransformationApplication> CoordTransformationApplication::create(int argc, 
                                                                                       char *argv[]
                                                                                       )
{
    return std::unique_ptr<CoordTransformationApplication>{new CoordTransformationApplication(argc, argv)};
}