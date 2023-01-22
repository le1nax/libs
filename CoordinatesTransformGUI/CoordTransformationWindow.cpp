#include "CoordTransformationWindow.h"

#include <gtkmm/messagedialog.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/recentmanager.h>
#include <gtkmm/recentchooserdialog.h>
#include <gtkmm/messagedialog.h>
#include <glibmm/miscutils.h>


#include "CoordTransformationIO.h"
#include "CoordVec.hpp"
#include "SpinBoxInput.hpp"



static inline constexpr auto npos = std::string::npos;
using namespace Gtk;
using namespace std;
using namespace fsd::Logging;
using namespace fsd::IO;
using namespace fsd::Math;
using sigc::mem_fun;

namespace fs = std::filesystem;

CoordTransformationWindow::CoordTransformationWindow()
{
    initMainLayout();
}

void CoordTransformationWindow::initMainLayout(){
    io_overlay = make_unique<CoordTrafoIO>();
    io_overlay->set_visible();
    add(*io_overlay);
}

CoordTransformationWindow::~CoordTransformationWindow(){}
