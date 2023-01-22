#pragma once

#include "gtkmm-3.0/gtkmm/application.h"

#include <filesystem>

class CoordTransformationWindow;

class CoordTransformationApplication : public Gtk::Application {

  public:
    static std::unique_ptr<CoordTransformationApplication> create(int argc, char *argv[]);

  public:
    ~CoordTransformationApplication();

  protected:
    CoordTransformationApplication(int argc, char *argv[]);


  protected:
      void on_activate() override;
      void on_startup() override;
      // int on_handle_local_options (const Glib::RefPtr< Glib::VariantDict >& options);

  
  private:

      void createWindow();

      std::unique_ptr<CoordTransformationWindow> mWindow{nullptr};
};