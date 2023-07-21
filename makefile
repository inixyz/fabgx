default:
	g++ emulator/src/*.cpp -I emulator/src/include -o emulator/bin/fab-8 -lsfml-graphics -lsfml-window -lsfml-system