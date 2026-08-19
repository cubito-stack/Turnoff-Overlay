#define TESLA_INIT_IMPL // Solo definir en el archivo principal
#include <tesla.hpp>    // Libtesla Header

class GuiTest : public tsl::Gui {
public:
    GuiTest(u8 arg1, u8 arg2, bool arg3) { }

    virtual tsl::elm::Element* createUI() override {
        auto frame = new tsl::elm::OverlayFrame("Turn Off Overlay", "v0.1");
        auto list = new tsl::elm::List();

        list->addItem(new tsl::elm::CategoryHeader("Options"));

        // Apagar consola (Shutdown)
        auto *clickableListItem = new tsl::elm::ListItem("Turn off", "Save your data before");
        clickableListItem->setClickListener([](u64 keys) {
            if (keys & HidNpadButton_A) {
                spsmShutdown(false); // false = Shutdown
                return true;
            }
            return false;
        });
        list->addItem(clickableListItem);

        // Reiniciar consola (Restart)
        auto *clickableListItem2 = new tsl::elm::ListItem("Restart", "Save your progress");
        clickableListItem2->setClickListener([](u64 keys) {
            if (keys & HidNpadButton_A) {
                spsmShutdown(true); // true = Restart
                return true;
            }
            return false;
        });
        list->addItem(clickableListItem2);

        frame->setContent(list);
        return frame;
    }

    virtual void update() override {}

    virtual bool handleInput(u64 keysDown, u64 keysHeld, const HidTouchState &touchPos, HidAnalogStickState joyStickPosLeft, HidAnalogStickState joyStickPosRight) override {
        return false;
    }
};

class OverlayTest : public tsl::Overlay {
public:
    // Inicializar servicios necesarios
    virtual void initServices() override {
        spsmInitialize(); 
    }

    // Limpiar servicios al salir
    virtual void exitServices() override {
        spsmExit();
    }

    virtual void onShow() override {}
    virtual void onHide() override {}

    virtual std::unique_ptr<tsl::Gui> loadInitialGui() override {
        return initially<GuiTest>(1, 2, true);
    }
};

int main(int argc, char **argv) {
    return tsl::loop<OverlayTest>(argc, argv);
}
