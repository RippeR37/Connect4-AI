Projekt "Tests" wymaga do uruchomienia podlinkowania biblioteki Google Test Framework.


Aby zmieni� AI (lub wybra� gr� cz�owiek vs cz�owiek) nale�y poczyni� zmiany w pliku
src/Controller/LogicHandler.cpp w metodzie LogicHandler::init(). 
Mo�na tam r�wnie� ustawi�, kt�ry gracz zaczyna (poprzez odkomentowanie funkcji std::Swap(...)).


W pliku main.cpp mo�emy ustawi�, aby wykonywa�a si� funkcja testAI(...). Polecane jest wtedy
ustawienie obu graczy na kt�re� z AI. Po przeprowadzeniu wszystkich gier statystyki zostan�
wypisane na ekranie gry.