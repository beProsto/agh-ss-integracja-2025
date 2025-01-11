# Integracja - starter pack

Wystawianie sieci WiFi i komunikacja z ESP za pomocą WebSocket

## Backend

Dodaj rozszerzenie PlatformIO IDE do Visual Studio Code.
Zbuduj projekt i wgraj kod na płytkę ESP.
Pamiętaj, aby zmienić nazwę SSID sieci WiFi, aby uniknąć konfliktów z innymi zespołami!

## Frontend

Odpal `python simple_web_server.py` i sprawdź stronkę tutaj: [http://localhost:8000/frontend/](http://localhost:8000/frontend/)

Przykładowy serwer WebSocket znajdziesz w pliku `ws_test_server.py`.

Przy testowaniu na ESP koniecznie zmień wartość zmiennej ROBOT_IP na adres IP Twojej płytki ESP.


## Known issues

- Podczas naszych testów zdarzały sie problemy z zasięgiem. Jednym z rozwiązań może byc modyfikacja kodu tak aby ESP łączył sie do istniejącej sieci wifi, a nie sam ją wystawiał.
