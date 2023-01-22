#include "CoordTransformationApplication.h"
#include "CoordVec.hpp"
#include "definitions.h"
#include "CoordTransformationIO.h"
#include <memory>

using namespace std;

#include <vector>
#include <string>
#include <variant>
using namespace Gtk;

int main(int argc, char *argv[])
{
    auto application = CoordTransformationApplication::create(argc, argv);
    return application->run();
    return 0;
}


