#ifndef CONTROLLER_LOGICHANDLER_H_INCLUDED
#define CONTROLLER_LOGICHANDLER_H_INCLUDED

namespace Controller {
    
    class LogicHandler {
        public:
            LogicHandler();
            ~LogicHandler();

            LogicHandler(const LogicHandler&) = delete;
            LogicHandler& operator=(const LogicHandler&) = delete;

            bool init();
            bool run();

        private:

    };

}


#endif