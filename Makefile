# VGE's Makefile

VERSION			= 0.1

LIB_SDL			= -I/usr/include/SDL -lSDL -lSDL_image
LIB_OPENGL		= -lGL -lGLEW
LIB_OPENAL		= -lopenal `freealut-config --libs`
LIB_OGG_VORBIS	= -logg -lvorbis -lvorbisfile
LIB_SIGCPP		= `pkg-config --cflags --libs sigc++-2.0`

LIBS			= $(LIB_SDL) $(LIB_OPENGL) $(LIB_OPENAL) $(LIB_OGG_VORBIS) $(LIB_SIGCPP)

INSTALL_SH		= ./install.sh
UNINSTALL_SH	= ./uninstall.sh

CXX				= g++
CXXFLAGS		= -Wall
HEADER_DIR		= -I include
OBJS_DIR		= objs
SRC_DIR			= src
GUI_DIR			= widgets
INTERFACES_DIR	= interfaces
PROJECT_DIR		= vge

GAME			= game
EDITOR			= editor

OBJECTS			= \
\
$(OBJS_DIR)/i-ruotable.o \
$(OBJS_DIR)/i-resizable.o \
$(OBJS_DIR)/i-scalable.o \
$(OBJS_DIR)/i-colorable.o \
$(OBJS_DIR)/i-clickable.o \
$(OBJS_DIR)/i-image.o \
$(OBJS_DIR)/i-animation.o \
$(OBJS_DIR)/i-programmable.o \
$(OBJS_DIR)/i-margins.o \
$(OBJS_DIR)/i-orientable.o \
$(OBJS_DIR)/i-origin.o \
$(OBJS_DIR)/i-range.o \
\
$(OBJS_DIR)/utf8.o \
$(OBJS_DIR)/xml.o \
$(OBJS_DIR)/color.o \
$(OBJS_DIR)/global.o \
$(OBJS_DIR)/designer.o \
$(OBJS_DIR)/input-manager.o \
$(OBJS_DIR)/mixer.o \
$(OBJS_DIR)/bounding-area.o \
$(OBJS_DIR)/entity.o \
$(OBJS_DIR)/entity-maker.o \
$(OBJS_DIR)/image.o \
$(OBJS_DIR)/image-maker.o \
$(OBJS_DIR)/sprite.o \
$(OBJS_DIR)/sprite-maker.o \
$(OBJS_DIR)/object.o \
$(OBJS_DIR)/object-maker.o \
$(OBJS_DIR)/character.o \
$(OBJS_DIR)/character-maker.o \
$(OBJS_DIR)/player.o \
$(OBJS_DIR)/player-maker.o \
$(OBJS_DIR)/particle-system.o \
$(OBJS_DIR)/particle-system-maker.o \
$(OBJS_DIR)/maker.o \
$(OBJS_DIR)/scene.o \
$(OBJS_DIR)/scene-maker.o \
$(OBJS_DIR)/viewer.o \
$(OBJS_DIR)/engine.o \
\
$(OBJS_DIR)/box.o \
$(OBJS_DIR)/font.o \
$(OBJS_DIR)/widget.o \
$(OBJS_DIR)/widget-maker.o \
$(OBJS_DIR)/frame.o \
$(OBJS_DIR)/label.o \
$(OBJS_DIR)/text-entry.o \
$(OBJS_DIR)/text-box.o \
$(OBJS_DIR)/container.o \
$(OBJS_DIR)/window.o \
$(OBJS_DIR)/message-box.o \
$(OBJS_DIR)/button.o \
$(OBJS_DIR)/text-button.o \
$(OBJS_DIR)/image-button.o \
$(OBJS_DIR)/slider.o \
$(OBJS_DIR)/progress-bar.o


all : $(OBJECTS) $(GAME) $(EDITOR)


$(GAME) : $(OBJECTS) $(OBJS_DIR)/game.o
	$(CXX) $(CXXFLAGS) $(HEADER_DIR) $(LIBS) $(OBJECTS) $(OBJS_DIR)/game.o -o $(GAME)

$(OBJS_DIR)/game.o : $(SRC_DIR)/game.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/game.cpp -o $(OBJS_DIR)/game.o

$(EDITOR) : $(OBJECTS) $(OBJS_DIR)/editor.o
	$(CXX) $(CXXFLAGS) $(HEADER_DIR) $(LIBS) $(OBJECTS) $(OBJS_DIR)/editor.o -o $(EDITOR)

$(OBJS_DIR)/editor.o : $(SRC_DIR)/editor.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/editor.cpp -o $(OBJS_DIR)/editor.o


$(OBJS_DIR)/i-ruotable.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-ruotable.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-ruotable.cpp -o $(OBJS_DIR)/i-ruotable.o

$(OBJS_DIR)/i-resizable.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-resizable.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-resizable.cpp -o $(OBJS_DIR)/i-resizable.o

$(OBJS_DIR)/i-scalable.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-scalable.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-scalable.cpp -o $(OBJS_DIR)/i-scalable.o

$(OBJS_DIR)/i-colorable.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-colorable.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-colorable.cpp -o $(OBJS_DIR)/i-colorable.o

$(OBJS_DIR)/i-clickable.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-clickable.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-clickable.cpp -o $(OBJS_DIR)/i-clickable.o

$(OBJS_DIR)/i-image.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-image.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-image.cpp -o $(OBJS_DIR)/i-image.o

$(OBJS_DIR)/i-animation.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-animation.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-animation.cpp -o $(OBJS_DIR)/i-animation.o

$(OBJS_DIR)/i-programmable.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-programmable.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-programmable.cpp -o $(OBJS_DIR)/i-programmable.o

$(OBJS_DIR)/i-margins.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-margins.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-margins.cpp -o $(OBJS_DIR)/i-margins.o

$(OBJS_DIR)/i-orientable.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-orientable.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-orientable.cpp -o $(OBJS_DIR)/i-orientable.o

$(OBJS_DIR)/i-origin.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-origin.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-origin.cpp -o $(OBJS_DIR)/i-origin.o

$(OBJS_DIR)/i-range.o : $(SRC_DIR)/$(INTERFACES_DIR)/i-range.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(INTERFACES_DIR)/i-range.cpp -o $(OBJS_DIR)/i-range.o










$(OBJS_DIR)/utf8.o : $(SRC_DIR)/utf8.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/utf8.cpp -o $(OBJS_DIR)/utf8.o

$(OBJS_DIR)/xml.o : $(SRC_DIR)/xml.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/xml.cpp -o $(OBJS_DIR)/xml.o

$(OBJS_DIR)/color.o : $(SRC_DIR)/color.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/color.cpp -o $(OBJS_DIR)/color.o

$(OBJS_DIR)/global.o : $(SRC_DIR)/global.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/global.cpp -o $(OBJS_DIR)/global.o

$(OBJS_DIR)/designer.o : $(SRC_DIR)/designer.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/designer.cpp -o $(OBJS_DIR)/designer.o

$(OBJS_DIR)/input-manager.o : $(SRC_DIR)/input-manager.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/input-manager.cpp -o $(OBJS_DIR)/input-manager.o

$(OBJS_DIR)/mixer.o : $(SRC_DIR)/mixer.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/mixer.cpp -o $(OBJS_DIR)/mixer.o

$(OBJS_DIR)/bounding-area.o : $(SRC_DIR)/bounding-area.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/bounding-area.cpp -o $(OBJS_DIR)/bounding-area.o

$(OBJS_DIR)/entity.o : $(SRC_DIR)/entity.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/entity.cpp -o $(OBJS_DIR)/entity.o

$(OBJS_DIR)/entity-maker.o : $(SRC_DIR)/entity-maker.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/entity-maker.cpp -o $(OBJS_DIR)/entity-maker.o

$(OBJS_DIR)/image.o : $(SRC_DIR)/image.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/image.cpp -o $(OBJS_DIR)/image.o

$(OBJS_DIR)/image-maker.o : $(SRC_DIR)/image-maker.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/image-maker.cpp -o $(OBJS_DIR)/image-maker.o

$(OBJS_DIR)/sprite.o : $(SRC_DIR)/sprite.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/sprite.cpp -o $(OBJS_DIR)/sprite.o

$(OBJS_DIR)/sprite-maker.o : $(SRC_DIR)/sprite-maker.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/sprite-maker.cpp -o $(OBJS_DIR)/sprite-maker.o

$(OBJS_DIR)/object.o : $(SRC_DIR)/object.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/object.cpp -o $(OBJS_DIR)/object.o

$(OBJS_DIR)/object-maker.o : $(SRC_DIR)/object-maker.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/object-maker.cpp -o $(OBJS_DIR)/object-maker.o

$(OBJS_DIR)/character.o : $(SRC_DIR)/character.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/character.cpp -o $(OBJS_DIR)/character.o

$(OBJS_DIR)/character-maker.o : $(SRC_DIR)/character-maker.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/character-maker.cpp -o $(OBJS_DIR)/character-maker.o

$(OBJS_DIR)/player.o : $(SRC_DIR)/player.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/player.cpp -o $(OBJS_DIR)/player.o

$(OBJS_DIR)/player-maker.o : $(SRC_DIR)/player-maker.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/player-maker.cpp -o $(OBJS_DIR)/player-maker.o

$(OBJS_DIR)/particle-system.o : $(SRC_DIR)/particle-system.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/particle-system.cpp -o $(OBJS_DIR)/particle-system.o

$(OBJS_DIR)/particle-system-maker.o : $(SRC_DIR)/particle-system-maker.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/particle-system-maker.cpp -o $(OBJS_DIR)/particle-system-maker.o

$(OBJS_DIR)/maker.o : $(SRC_DIR)/maker.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/maker.cpp -o $(OBJS_DIR)/maker.o

$(OBJS_DIR)/scene.o : $(SRC_DIR)/scene.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/scene.cpp -o $(OBJS_DIR)/scene.o

$(OBJS_DIR)/scene-maker.o : $(SRC_DIR)/scene-maker.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/scene-maker.cpp -o $(OBJS_DIR)/scene-maker.o

$(OBJS_DIR)/viewer.o : $(SRC_DIR)/viewer.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/viewer.cpp -o $(OBJS_DIR)/viewer.o

$(OBJS_DIR)/engine.o : $(SRC_DIR)/engine.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/engine.cpp -o $(OBJS_DIR)/engine.o


$(OBJS_DIR)/box.o : $(SRC_DIR)/$(GUI_DIR)/box.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/box.cpp -o $(OBJS_DIR)/box.o

$(OBJS_DIR)/font.o : $(SRC_DIR)/$(GUI_DIR)/font.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/font.cpp -o $(OBJS_DIR)/font.o

$(OBJS_DIR)/widget.o : $(SRC_DIR)/$(GUI_DIR)/widget.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/widget.cpp -o $(OBJS_DIR)/widget.o

$(OBJS_DIR)/widget-maker.o : $(SRC_DIR)/$(GUI_DIR)/widget-maker.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/widget-maker.cpp -o $(OBJS_DIR)/widget-maker.o

$(OBJS_DIR)/frame.o : $(SRC_DIR)/$(GUI_DIR)/frame.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/frame.cpp -o $(OBJS_DIR)/frame.o

$(OBJS_DIR)/label.o : $(SRC_DIR)/$(GUI_DIR)/label.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/label.cpp -o $(OBJS_DIR)/label.o

$(OBJS_DIR)/text-entry.o : $(SRC_DIR)/$(GUI_DIR)/text-entry.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/text-entry.cpp -o $(OBJS_DIR)/text-entry.o

$(OBJS_DIR)/text-box.o : $(SRC_DIR)/$(GUI_DIR)/text-box.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/text-box.cpp -o $(OBJS_DIR)/text-box.o

$(OBJS_DIR)/container.o : $(SRC_DIR)/$(GUI_DIR)/container.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/container.cpp -o $(OBJS_DIR)/container.o

$(OBJS_DIR)/window.o : $(SRC_DIR)/$(GUI_DIR)/window.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/window.cpp -o $(OBJS_DIR)/window.o

$(OBJS_DIR)/message-box.o : $(SRC_DIR)/$(GUI_DIR)/message-box.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/message-box.cpp -o $(OBJS_DIR)/message-box.o

$(OBJS_DIR)/button.o : $(SRC_DIR)/$(GUI_DIR)/button.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/button.cpp -o $(OBJS_DIR)/button.o

$(OBJS_DIR)/text-button.o : $(SRC_DIR)/$(GUI_DIR)/text-button.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/text-button.cpp -o $(OBJS_DIR)/text-button.o

$(OBJS_DIR)/image-button.o : $(SRC_DIR)/$(GUI_DIR)/image-button.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/image-button.cpp -o $(OBJS_DIR)/image-button.o

$(OBJS_DIR)/slider.o : $(SRC_DIR)/$(GUI_DIR)/slider.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/slider.cpp -o $(OBJS_DIR)/slider.o

$(OBJS_DIR)/progress-bar.o : $(SRC_DIR)/$(GUI_DIR)/progress-bar.cpp
	$(CXX) -c $(CXXFLAGS) $(HEADER_DIR) $(SRC_DIR)/$(GUI_DIR)/progress-bar.cpp -o $(OBJS_DIR)/progress-bar.o

install:
	$(INSTALL_SH)

uninstall:
	$(UNINSTALL_SH)

clean:
	rm -f $(OBJS_DIR)/*.o
	rm -f $(EDITOR) $(GAME)

