default:
	g++ emulator/src/*.cpp emulator/src/imgui/*.cpp -I emulator/src/include -I emulator/src/imgui/include -o emulator/bin/fab-8 -lsfml-graphics -lsfml-window -lsfml-system -lGL