Projekt "Tests" wymaga do uruchomienia podlinkowania biblioteki Google Test Framework.


Aby zmieniæ AI (lub wybraæ grê cz³owiek vs cz³owiek) nale¿y poczyniæ zmiany w pliku
src/Controller/LogicHandler.cpp w metodzie LogicHandler::init(). 
Mo¿na tam równie¿ ustawiæ, który gracz zaczyna (poprzez odkomentowanie funkcji std::Swap(...)).


W pliku main.cpp mo¿emy ustawiæ, aby wykonywa³a siê funkcja testAI(...). Polecane jest wtedy
ustawienie obu graczy na któreœ z AI. Po przeprowadzeniu wszystkich gier statystyki zostan¹
wypisane na ekranie gry.