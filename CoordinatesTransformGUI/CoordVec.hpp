#include "gtkmm/box.h"
#include "gtkmm/grid.h"
#include "gtkmm/label.h"
#include "definitions.h"

#include <Vec.h>
#include <memory>
#include "CoordTransformationIO.h"
#include "SpinBoxInput.hpp"
#include "customEntryBox.hpp"
#include "LLH.h"
#include "UTM.h"
#include "UTMREF.h"
#include "LocalRef.h"
#include "LocalCoordinates.h"
#include <sigc++/signal.h>

constexpr int CoordVecSize =  3;

template<typename T>
class CoordVec :  public virtual Gtk::Grid{

    public:

        using value_type=T;
        explicit CoordVec(CoordTrafoIO& io, T coords, CoordType type) : Gtk::Grid(), mCoordType{type}, mCoordinates{coords}, mParent{io} 
        {   
            init();
        }
   
        // CoordVec(const CoordVec& vec) = delete;
        // CoordVec& operator=(const CoordVec& vec) = delete;

        // CoordVec(CoordVec&& vec) = delete;
        // CoordVec& operator=(CoordVec&& vec) = delete;

        // virtual ~CoordVec()  = default;

        const T getCoordinates() {
            return mCoordinates;
        }
        const CoordType getCoordType() {
            return mCoordType;
        }

         Gtk::Label* getLabel() const {
            return mLabel;
        }

    protected:
        const CoordType mCoordType = CoordType::eUTM;
        T mCoordinates;
    
    private:
        Gtk::Label* mLabel = Gtk::make_managed<Gtk::Label>();
        CoordTrafoIO& mParent;
        std::vector<SpinBoxInput<T, double>*> mCoordBoxes;
        std::vector<Gtk::Label*> mCoordLabels;
        std::vector<customEntryBox<T>*> mEntries;
        std::vector<Gtk::Label*> mEntryLabels;

        Gtk::Box* label_layout = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL);
        Gtk::Box* box_layout = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL);

        void init()
        {
            set_vexpand(false);
            set_hexpand(false);
            set_row_spacing(30);
            set_column_spacing(30);
            set_valign(Gtk::Align::ALIGN_CENTER);
            set_halign(Gtk::Align::ALIGN_START);
            initCoordVec();
            connectBoxes();
            show_all_children();
        }

        void initCoordVec()
        {
            switch (mCoordType)
            {
            case CoordType::eLOCAL:
                mLabel->set_text("LOCAL: ");
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("Latitude as a float in degee") );
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("Logitude as float in degree"));
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("h_AMSL in meter"));
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("Referenz Latitude as a float in degee ") );
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("Referenz Logitude as float in degree"));
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("Heading offset Δψ in radians"));
                setBoxes(numberOfLocalCoordinateinputs);
                break;       
            case CoordType::eUTM:
                mLabel->set_text("UTM: ");
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("east"));
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("north"));
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("h_AMSL in meter"));
                setBoxes(numberOfUTMinputs-numberOfUTMzoneinputs);
                break;
            case CoordType::eUTMREF:
                mLabel->set_text("UTMREF: ");
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("east"));
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("north"));
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("h_AMSL in meter"));
                setBoxes(numberOfUTMREFinputs-numberOfUTMREFzoneinputs);
                break;
            case CoordType::eLLH:
                mLabel->set_text("LLH: ");
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("Latitude as a float in degee"));
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("Logitude as float in degree"));
                mCoordLabels.emplace_back(Gtk::make_managed<Gtk::Label>("h_AMSL in meter"));
                setBoxes(numberOfLLHinputs);
                break;
            }
        } 

        void connectBoxes()
        {
            for(auto& box: mCoordBoxes)
            {
                box->signal_value_changed().connect(sigc::bind(
                                                          sigc::mem_fun(mParent, &CoordTrafoIO::inputChanged<T>),
                                                          box->mParentVec.getCoordType(), box->mParentVec.getCoordinates())
                                                         );
            }
        }

        void addEntryBoxes(uint8_t numberOfEntries)
        {
            for(uint8_t i= 0; i<numberOfEntries; i++){
                    label_layout->pack_start(*mEntryLabels.at(i));
                    box_layout->pack_start(*mEntries.at(i));
                }
        }

        void setBoxes(uint8_t numberOfInputs)
        {
            if(mCoordType == CoordType::eUTM){
                mEntryLabels.emplace_back(Gtk::make_managed<Gtk::Label>("Zone"));
                mEntries.emplace_back(Gtk::make_managed<customEntryBox<T>>(*this));
                addEntryBoxes(numberOfUTMzoneinputs);
            } 
                else if(mCoordType == CoordType::eUTMREF){
                    mEntryLabels.emplace_back(Gtk::make_managed<Gtk::Label>("Zone"));
                    mEntries.emplace_back(Gtk::make_managed<customEntryBox<T>>(*this));
                    mEntryLabels.emplace_back(Gtk::make_managed<Gtk::Label>("Grid Identifier"));
                    mEntries.emplace_back(Gtk::make_managed<customEntryBox<T>>(*this));
                    addEntryBoxes(numberOfUTMREFzoneinputs);
                }
            label_layout->set_halign(Gtk::Align::ALIGN_END);
            label_layout->set_halign(Gtk::Align::ALIGN_END);

            for(uint8_t i= 0; i<numberOfInputs; i++){
                    SpinBoxInput<T, double>* box = Gtk::make_managed<SpinBoxInput<T, double>>(*this);
                    mCoordBoxes.emplace_back(box);
                    label_layout->pack_start(*mCoordLabels.at(i));
                    box_layout->pack_start(*box);
                }
            attach(*label_layout, 0, 0);
            attach(*box_layout, 1, 0);
        }

        // void setValue()

    public:
        template<typename Y>
        void onCoordsChanged(CoordType inputType, Y coords)
    {              
        switch (inputType)
        {
            case CoordType::eLOCAL:
                switch (mCoordType)
            {     
                case CoordType::eUTM:
                    Local2UTM(coords);
                    break;
                case CoordType::eLOCAL:
                    break;
                case CoordType::eUTMREF:
                    Local2UTMREF(coords);
                    break;
                case CoordType::eLLH:
                    Local2LLH(coords);
                break;
            }
            break;       
            case CoordType::eUTM:
                switch (mCoordType)
                {
                case CoordType::eLOCAL:
                    UTM2Local(coords);
                    break;
                case CoordType::eUTM:
                    break;
                case CoordType::eUTMREF:
                    UTM2UTMREF(coords);
                    break;
                case CoordType::eLLH:
                    UTM2LLH(coords);
                break;
                }
            break;
            case CoordType::eUTMREF:
                switch (mCoordType)
                {   
                case CoordType::eLOCAL:
                    UTMREF2UTM(coords);
                    break;
                case CoordType::eUTMREF:
                    break;        
                case CoordType::eUTM:
                    UTMREF2UTM(coords);
                    break;
                case CoordType::eLLH:
                    UTMREF2LLH(coords);
                break;
                }
            break;
            case CoordType::eLLH:
                switch (mCoordType)
                {   
                case CoordType::eLOCAL:
                    LLH2Local(coords);
                    break;
                case CoordType::eLLH:
                    break;        
                case CoordType::eUTM:
                    LLH2UTM(coords);
                    break;
                case CoordType::eUTMREF:
                    LLH2UTMREF(coords);
                    break;
                }
            break;
        }
    }
    

template<typename Z>
void LLH2UTM(Z coords){
    fsd::Coord::UTM utm = fsd::Coord::UTM(coords);
    std::cout << "LLH2UTM" << utm << std::endl;
}
template<typename Y>
void LLH2UTMREF(Y coords){
    std::cout << "LLH2UTMREF" << std::endl;
}
template<typename Y>
void LLH2Local(Y coords){
    std::cout << "LLH2Local" << std::endl;
}
template<typename Y>
void Local2UTM(Y coords){
    std::cout << "Local2UTM" << std::endl;
}
template<typename Y>
void Local2UTMREF(Y coords){
    std::cout << "Local2UTMREF" << std::endl;
}
template<typename Y>
void Local2LLH(Y coords){
    std::cout << "Local2LLH" << std::endl;
}
template<typename Y>
void UTM2UTMREF(Y coords){
    std::cout << "UTM2UTMREF" << std::endl;
}
template<typename Y>
void UTM2Local(Y coords){
    std::cout << "UTM2Local" << std::endl;
}
template<typename Y>
void UTM2LLH(Y coords){
    std::cout << "UTM2LLH" << std::endl;
}
template<typename Y>
void UTMREF2UTM(Y coords){
    std::cout << "UTMREF2UTM" << std::endl;
}
template<typename Y>
void UTMREF2Local(Y coords){
    std::cout << "UTMREF2Local" << std::endl;
}
template<typename Y>
void UTMREF2LLH(Y coords){

    std::cout << "UTMREF2LLH" << std::endl;
}

};
        

